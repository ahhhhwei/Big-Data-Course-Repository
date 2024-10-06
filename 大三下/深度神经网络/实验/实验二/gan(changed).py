import argparse
import os
import numpy as np
import torchvision.transforms as transforms
from torchvision.utils import save_image
from torchvision import datasets
from torch.autograd import Variable
import torch.nn as nn
import torch
import matplotlib.pyplot as plt


parser = argparse.ArgumentParser()
parser.add_argument("--n_epochs", type=int, default=100, help="训练轮次")
parser.add_argument("--batch_size", type=int, default=16, help="单个训练批次大小")
parser.add_argument("--lr", type=float, default=0.0001, help="学习率")
parser.add_argument("--latent_dim", type=int, default=100, help="潜空间向量维度")
parser.add_argument("--img_size", type=int, default=128, help="图片尺寸")
parser.add_argument("--channels", type=int, default=3, help="图片通道")
parser.add_argument("--n_g_feature", type=int, default=128, help="G模型通道量")
parser.add_argument("--n_d_feature", type=int, default=128, help="G模型通道量")
parser.add_argument("--sample_interval", type=int, default=1000, help="每训练n次保存结果")
parser.add_argument("--save_dir", type=str, default="GAN_20240523/result", help="存放训练结果的地址")
opt = parser.parse_args()
print(opt)

os.makedirs(opt.save_dir, exist_ok=True)#创建存放训练结果的文件夹
cuda = True if torch.cuda.is_available() else False

g_losses = []
d_losses = []

# 生成器
class Generator(nn.Module):
    def __init__(self):
        super(Generator, self).__init__()

        n_g_feature = opt.n_g_feature
        def block(in_feat, out_feat, is_first=False):
            if is_first:
                layers = [
                    nn.ConvTranspose2d(in_feat, out_feat, kernel_size=4, bias=False),
                    nn.BatchNorm2d(out_feat),
                    nn.ReLU()
                ]
            else:
                layers = [
                    nn.ConvTranspose2d(in_feat, out_feat, kernel_size=4, stride=2, padding=1, bias=False),
                    nn.BatchNorm2d(out_feat),
                    nn.ReLU()
                ]
            return layers
        
        self.model = nn.Sequential(
            *block(opt.latent_dim, 16 * n_g_feature, is_first=True),
            *block(16 * n_g_feature, 8 * n_g_feature),
            *block(8 * n_g_feature, 4 * n_g_feature),
            *block(4 * n_g_feature, 2 * n_g_feature),
            *block(2 * n_g_feature, n_g_feature),
            nn.ConvTranspose2d(n_g_feature, opt.channels, kernel_size=4, stride=2, padding=1),
            nn.Sigmoid()
        )

    def forward(self, z):
        img = self.model(z)
        return img

# 判别器
class Discriminator(nn.Module):
    def __init__(self):
        super(Discriminator, self).__init__()

        def block(in_feat, out_feat, is_first=False):
            if is_first:
                layers = [
                    nn.Conv2d(in_feat, out_feat, kernel_size=4, stride=2, padding=1),
                    nn.LeakyReLU(0.2)
                ]
            else:
                layers = [
                    nn.Conv2d(in_feat, out_feat, kernel_size=4, stride=2, padding=1, bias=False),
                    nn.BatchNorm2d(out_feat),
                    nn.LeakyReLU(0.2),
                ]
            return layers

        n_d_feature = opt.n_d_feature
        self.model = nn.Sequential(
            *block(opt.channels, n_d_feature, is_first=True),
            *block(n_d_feature, 2 * n_d_feature),
            *block(2 * n_d_feature, 4 * n_d_feature),
            *block(4 * n_d_feature, 8 * n_d_feature),
            *block(8 * n_d_feature, 16 * n_d_feature),
            nn.Conv2d(16 * n_d_feature, 1, kernel_size=4)
        )


    def forward(self, img):
        out = self.model(img)
        return out

# 损失函数
adversarial_loss = torch.nn.BCEWithLogitsLoss()

# 够级生成器与判别器
generator = Generator()
discriminator = Discriminator()

# cuda加速
if cuda:
    generator.cuda()
    discriminator.cuda()
    adversarial_loss.cuda()

def weights_init_normal(m):
    if type(m) in [nn.ConvTranspose2d, nn.Conv2d]:
        torch.nn.init.xavier_normal_(m.weight)
    elif type(m) == nn.BatchNorm2d:
        torch.nn.init.normal_(m.weight, 1.0, 0.02)
        torch.nn.init.constant_(m.bias, 0)

# 初始化权重
generator.apply(weights_init_normal)
discriminator.apply(weights_init_normal)

# 装载数据
dataloader = torch.utils.data.DataLoader(
    datasets.ImageFolder(
        "GAN_20240523/flower_photos",
        transform=transforms.Compose([
                transforms.Resize((opt.img_size,opt.img_size)),
                transforms.ToTensor()
                ])
        ),
        batch_size=opt.batch_size,
        shuffle=True
)
# dataloader = torch.utils.data.DataLoader(
#    datasets.QMNIST(
#        "/home/vision/GAN_20240523",
#        transform=transforms.Compose([
#                transforms.Resize((opt.img_size,opt.img_size)),
#                transforms.ToTensor()
#                ])
#        ),
#        batch_size=opt.batch_size,
#        shuffle=True
#)

# 优化器
optimizer_G = torch.optim.Adam(generator.parameters(), lr=opt.lr, betas=(0.5, 0.999))
optimizer_D = torch.optim.Adam(discriminator.parameters(), lr=opt.lr, betas=(0.5, 0.999))

Tensor = torch.cuda.FloatTensor if cuda else torch.FloatTensor

# 训练循环开始前初始化绘图
plt.figure(figsize=(10, 5))

# 开始训练
for epoch in range(opt.n_epochs):
    for i, (imgs, _) in enumerate(dataloader):

        valid = Variable(Tensor(imgs.shape[0]).fill_(1.0), requires_grad=False)
        fake = Variable(Tensor(imgs.shape[0]).fill_(0.0), requires_grad=False)

        # 构造输入
        real_imgs = Variable(imgs.type(Tensor))

        # -----------------
        #  训练生成器
        # -----------------

        optimizer_G.zero_grad()

        # 生成随机噪声
        z = Variable(Tensor(np.random.normal(0, 1, (imgs.shape[0], opt.latent_dim,1,1))))

        # 生成一批图像
        gen_imgs = generator(z)

        # 衡量生成器欺骗鉴别器的能力
        g_loss = adversarial_loss(discriminator(gen_imgs).view(-1), valid)

        g_loss.backward()
        optimizer_G.step()

        # ---------------------
        #  训练鉴别器
        # ---------------------

        optimizer_D.zero_grad()

        # 衡量鉴别器鉴别图像的能力
        real_loss = adversarial_loss(discriminator(real_imgs).view(-1), valid)
        fake_loss = adversarial_loss(discriminator(gen_imgs.detach()).view(-1), fake)
        d_loss = (real_loss + fake_loss) / 2

        d_loss.backward()
        optimizer_D.step()

        print(
            "[Epoch %d/%d] [Batch %d/%d] [D loss: %f] [G loss: %f]"
            % (epoch, opt.n_epochs, i, len(dataloader), d_loss.item(), g_loss.item())
        )

        batches_done = epoch * len(dataloader) + i
        if batches_done % opt.sample_interval == 0:
            save_image(gen_imgs.data[:16], opt.save_dir+"/%d.png" % batches_done, nrow=4, normalize=True)

        # 记录每轮结束的Loss
        g_losses.append(g_loss.item())
        d_losses.append(d_loss.item())

        # 特定轮次的操作，如模型保存提示
        if epoch in [1, 10, 30, 60, 90]:
            print(f"Model state recorded at epoch {epoch}.")

    # 每个epoch结束时更新Loss曲线
    plt.clf()  # 清除当前图表以便重新绘制
    plt.plot(g_losses, label="Generator Loss")
    plt.plot(d_losses, label="Discriminator Loss")
    
    # 标记特定轮次
    epochs_to_mark = [1, 10, 30, 60, 90]
    current_epoch_index = epoch
    for marked_epoch in epochs_to_mark:
        if marked_epoch <= current_epoch_index:
            plt.axvline(x=marked_epoch, color='r', linestyle='--', alpha=0.5)
    
    plt.title("Training Loss Progression")
    plt.xlabel("Epochs")
    plt.ylabel("Loss")
    plt.legend()
    plt.grid(True)

plt.savefig("final_loss_curve.png")



