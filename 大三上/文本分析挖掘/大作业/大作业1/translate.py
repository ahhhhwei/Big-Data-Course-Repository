import mindspore.common.dtype as mstype
import mindspore.dataset.text as text
import mindspore.dataset.transforms.c_transforms as C
import mindspore.nn as nn
from mindspore import Model, context
from mindspore.train.callback import Callback
from mindspore.train.serialization import load_checkpoint, save_checkpoint
from mindspore.common.tensor import Tensor
from mindspore.train.serialization import load_checkpoint
import mindspore.dataset as ds
import jieba

# 设置运行环境和设备
context.set_context(mode=context.GRAPH_MODE, device_target="CPU")

# 定义超参数和数据集文件路径
max_vocab = 5000
batch_size = 32
learning_rate = 0.001
epochs = 10
data_file = "./data.txt"

# 构建数据集
data_set = ds.TextFileDataset(data_file, shuffle=True)


# 分词操作
def tokenize(text):
    return list(jieba.cut(text))

data_set = data_set.map(operations=tokenize)

# 构建词汇表
vocab = text.Vocab.from_dataset(data_set)

# 将文本映射为索引序列
data_set = data_set.map(operations=text.Lookup(vocab), input_columns="text", output_columns="token")

# 划分训练集和验证集
train_data = data_set.shuffle(buffer_size=1000).batch(batch_size, drop_remainder=True)
train_data = train_data.map(operations=C.TypeCast(mstype.int32))
train_data = train_data.repeat(epochs)

# 定义模型
class SimpleTranslationModel(nn.Cell):
    def __init__(self, vocab_size, hidden_size):
        super(SimpleTranslationModel, self).__init__()
        self.embedding = nn.Embedding(vocab_size, hidden_size)
        self.softmax = nn.Softmax()
    
    def construct(self, x):
        output = self.embedding(x)
        output = self.softmax(output)
        return output

# 创建模型实例
model = SimpleTranslationModel(max_vocab, 256)

# 定义损失函数和优化器
loss_fn = nn.SoftmaxCrossEntropyWithLogits(sparse=True)
optimizer = nn.Adam(model.trainable_params(), learning_rate=learning_rate)

# 定义回调函数，保存模型
class SaveCallback(Callback):
    def __init__(self, model):
        self.model = model
    
    def step_end(self, run_context):
        cb_params = run_context.original_args()
        epoch = cb_params.cur_epoch_num
        if epoch % 5 == 0 and epoch > 0:
            save_checkpoint(self.model, f"checkpoint_{epoch}.ckpt")

# 加载预训练模型
load_checkpoint("pretrained.ckpt", model=model)

# 定义模型和数据集
model = Model(model, loss_fn, optimizer, metrics={"acc"})

# 开始训练
model.train(epochs, train_data, callbacks=[SaveCallback(model)])
