import settings
import tensorflow as tf
import gradio as gr
import os
import numpy as np
from tqdm import tqdm
from model import NeuralStyleTransferModel
import utils
from PIL import Image  
import io

js = """
function createGradioAnimation() {
    var container = document.createElement('div');
    container.id = 'gradio-animation';
    container.style.fontSize = '2em';
    container.style.fontWeight = 'bold';
    container.style.textAlign = 'center';
    container.style.marginBottom = '20px';

    var text = '欢迎使用AI艺术照网站';
    for (var i = 0; i < text.length; i++) {
        (function(i){
            setTimeout(function(){
                var letter = document.createElement('span');
                letter.style.opacity = '0';
                letter.style.transition = 'opacity 0.5s';
                letter.innerText = text[i];

                container.appendChild(letter);

                setTimeout(function() {
                    letter.style.opacity = '1';
                }, 50);
            }, i * 250);
        })(i);
    }

    var gradioContainer = document.querySelector('.gradio-container');
    gradioContainer.insertBefore(container, gradioContainer.firstChild);

    return 'Animation created';
}
"""


def image_demo1(输入风格图片, 输入):
    # 创建模型
    model = NeuralStyleTransferModel()
    # 加载内容图片
    输入 = tf.convert_to_tensor(输入)
    content_image = utils.load_images(输入)
    # 风格图片
    输入风格图片 = tf.convert_to_tensor(输入风格图片)
    style_image = utils.load_images(输入风格图片)

    # 计算出目标内容图片的内容特征备用
    target_content_features = model([content_image, ])['content']
    # 计算目标风格图片的风格特征
    target_style_features = model([style_image, ])['style']

    M = settings.WIDTH * settings.HEIGHT
    N = 3


    def _compute_content_loss(noise_features, target_features):
        """
        计算指定层上两个特征之间的内容loss
        :param noise_features: 噪声图片在指定层的特征
        :param target_features: 内容图片在指定层的特征
        """
        content_loss = tf.reduce_sum(tf.square(noise_features - target_features))
        # 计算系数
        x = 2. * M * N
        content_loss = content_loss / x
        return content_loss


    def compute_content_loss(noise_content_features):
        """
        计算并当前图片的内容loss
        :param noise_content_features: 噪声图片的内容特征
        """
        # 初始化内容损失
        content_losses = []
        # 加权计算内容损失
        for (noise_feature, factor), (target_feature, _) in zip(noise_content_features, target_content_features):
            layer_content_loss = _compute_content_loss(noise_feature, target_feature)
            content_losses.append(layer_content_loss * factor)
        return tf.reduce_sum(content_losses)


    def gram_matrix(feature):
        """
        计算给定特征的格拉姆矩阵
        """
        # 先交换维度，把channel维度提到最前面
        x = tf.transpose(feature, perm=[2, 0, 1])
        # reshape，压缩成2d
        x = tf.reshape(x, (x.shape[0], -1))
        # 计算x和x的逆的乘积
        return x @ tf.transpose(x)


    def _compute_style_loss(noise_feature, target_feature):
        """
        计算指定层上两个特征之间的风格loss
        :param noise_feature: 噪声图片在指定层的特征
        :param target_feature: 风格图片在指定层的特征
        """
        noise_gram_matrix = gram_matrix(noise_feature)
        style_gram_matrix = gram_matrix(target_feature)
        style_loss = tf.reduce_sum(tf.square(noise_gram_matrix - style_gram_matrix))
        # 计算系数
        x = 4. * (M ** 2) * (N ** 2)
        return style_loss / x


    def compute_style_loss(noise_style_features):
        """
        计算并返回图片的风格loss
        :param noise_style_features: 噪声图片的风格特征
        """
        style_losses = []
        for (noise_feature, factor), (target_feature, _) in zip(noise_style_features, target_style_features):
            layer_style_loss = _compute_style_loss(noise_feature, target_feature)
            style_losses.append(layer_style_loss * factor)
        return tf.reduce_sum(style_losses)


    def total_loss(noise_features):
        """
        计算总损失
        :param noise_features: 噪声图片特征数据
        """
        content_loss = compute_content_loss(noise_features['content'])
        style_loss = compute_style_loss(noise_features['style'])
        return content_loss * settings.CONTENT_LOSS_FACTOR + style_loss * settings.STYLE_LOSS_FACTOR


    # 使用Adma优化器
    optimizer = tf.keras.optimizers.Adam(settings.LEARNING_RATE)

    # 基于内容图片随机生成一张噪声图片
    noise_image = tf.Variable((content_image + np.random.uniform(-0.2, 0.2, (1, settings.HEIGHT, settings.WIDTH, 3))) / 2)


    # 使用tf.function加速训练
    @tf.function
    def train_one_step():
        """
        一次迭代过程
        """
        # 求loss
        with tf.GradientTape() as tape:
            noise_outputs = model(noise_image)
            loss = total_loss(noise_outputs)
        # 求梯度
        grad = tape.gradient(loss, noise_image)
        # 梯度下降，更新噪声图片
        optimizer.apply_gradients([(grad, noise_image)])
        return loss


    # 创建保存生成图片的文件夹
    if not os.path.exists(settings.OUTPUT_DIR):
        os.mkdir(settings.OUTPUT_DIR)

    # 共训练settings.EPOCHS个epochs
    for epoch in range(settings.EPOCHS):
        # 使用tqdm提示训练进度
        with tqdm(total=settings.STEPS_PER_EPOCH, desc='Epoch {}/{}'.format(epoch + 1, settings.EPOCHS)) as pbar:
            # 每个epoch训练settings.STEPS_PER_EPOCH次
            for step in range(settings.STEPS_PER_EPOCH):
                _loss = train_one_step()
                pbar.set_postfix({'loss': '%.4f' % float(_loss)})
                pbar.update(1)

    image_mean = tf.constant([0.485, 0.456, 0.406])
    image_std = tf.constant([0.299, 0.224, 0.225])
    x = tf.reshape(noise_image, noise_image.shape[1:])
    x = x * image_std + image_mean
    x = x * 255.
    x = tf.cast(x, tf.int32)
    x = tf.clip_by_value(x, 0, 255)
    x = x.numpy()
    return x

demo1_examples=[
    [os.path.join(os.path.dirname(__file__), "images/style_1.jpg")],
    [os.path.join(os.path.dirname(__file__), "images/style_2.jpg")],
    [os.path.join(os.path.dirname(__file__), "images/style_3.jpg")],
    [os.path.join(os.path.dirname(__file__), "images/style_4.jpg")],
    [os.path.join(os.path.dirname(__file__), "images/style_5.jpg")],
    [os.path.join(os.path.dirname(__file__), "images/style_6.jpg")],
]

def image_demo2(输入):
    a = np.dot(输入[..., :3], [0.2989, 0.5870, 0.1140])
    depth = 10.                        # (0-100)  
    grad = np.gradient(a)              #取图像灰度的梯度值  
    grad_x, grad_y =grad               #分别取横纵图像梯度值  
    grad_x = grad_x*depth/100.  
    grad_y = grad_y*depth/100.  
    A = np.sqrt(grad_x**2 + grad_y**2 + 1.)  
    uni_x = grad_x/A  
    uni_y = grad_y/A  
    uni_z = 1./A  
    vec_el = np.pi/2.2                   # 光源的俯视角度，弧度值  
    vec_az = np.pi/4.                    # 光源的方位角度，弧度值  
    dx = np.cos(vec_el)*np.cos(vec_az)   #光源对x 轴的影响  
    dy = np.cos(vec_el)*np.sin(vec_az)   #光源对y 轴的影响  
    dz = np.sin(vec_el)                  #光源对z 轴的影响  
    b = 255*(dx*uni_x + dy*uni_y + dz*uni_z)     #光源归一化  
    b = b.clip(0,255)  
    im = Image.fromarray(b.astype('uint8'))      #重构图像 
    return im

def image_demo3(输入):
    image = Image.fromarray(输入)
    image.save('temp.png')
    # 定义字符画中所使用的字符集合
    ascii_char = list("1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()_+-=[]{}|;':\",./<>?//  ")

    # 将256个灰度值映射到70个字符上
    def get_char(r, g, b, alpha=256):
        length = len(ascii_char)
        gray = int(0.2126 * r + 0.7152 * g + 0.0722 * b)
        if gray >= 240:
            return ' '
        unit = (256.0 + 1) / length
        return ascii_char[int(gray / unit)]

    # 将图片转换为字符画
    def image_to_ascii(image_path, width=100, save_path=None):
        im = Image.open(image_path)
        im = im.resize((width, int(width * im.size[1] / im.size[0])))
        txt = ""
        for i in range(im.size[1]):
            for j in range(im.size[0]):
                txt += get_char(*im.getpixel((j, i)))
            txt += '\n'
        
        if save_path:
            with open(save_path, 'w') as f:
                f.write(txt)
        
        return txt
    ascii_text = image_to_ascii('temp.png', save_path='字符画.txt')
    return '字符画.txt'

demo1 = gr.Interface(
    fn=image_demo1, 
    inputs=["image", "image"], 
    outputs="image", 
    title="照片风格化",
    examples=demo1_examples,
)

demo2 = gr.Interface(
    fn=image_demo2, 
    inputs="image", 
    outputs="image", 
    title="照片素描",
)

demo3 = gr.Interface(
    fn=image_demo3, 
    inputs="image", 
    outputs="file", 
    title="照片字符化", 
    description="请输入如示例一样区分明显的照片",
    examples=[os.path.join(os.path.dirname(__file__), "images/leifeng.jpg")],
)

demo = gr.TabbedInterface(
    [demo1, demo2, demo3], 
    ["照片风格化", "照片素描", "照片字符化"], 
    title = "🤖AI 艺术照相馆",
    css="""
        h2 {
            text-align: center !important;
        }

        footer {
            visibility: hidden;
        }
    """,
    theme=gr.themes.Base(),
)

if __name__ == "__main__":
    demo.launch(
        auth=("ahwei", '520Wjw')
        #share=True
)
