from statistics import mean
import torch
from torch.nn.utils.rnn import pad_sequence,pack_padded_sequence,pack_sequence,pad_packed_sequence
from torch import nn
import torch.nn.functional as F
from torch.utils.data import Dataset,TensorDataset,DataLoader,Subset
import numpy as np
from gensim.models import Word2Vec
import matplotlib.pyplot as plt
import re
import os
from sklearn.metrics import roc_curve, auc, accuracy_score

from insn2vec import RefineAsmCode, GetBinaryFileAllFuncDisasm
import pdb

from multiprocessing import cpu_count
torch.set_num_threads(cpu_count() - 1)

#固定随机数种子，方便重现实验
np.random.seed(0)
torch.manual_seed(0)
torch.cuda.manual_seed_all(0)

class MyDataSet(Dataset):
    def __init__(self, dataList:list):
        #data的元素为(函数1的指令序列，函数2的指令序列，label)，相似label=1，否则为-1
        self.datas = []

        for data in dataList:
            self.datas.append((data[0],data[1],data[2]))

    def __getitem__(self, index):
        return self.datas[index]

    def __len__(self):
        return len(self.datas)

def GetDataFiles(root:str) -> list:
    dataFilePathList = []
    for root,dirs,files in os.walk(root):
        for fileName in files:
            dataFilePathList.append(os.path.join(root, fileName))
            
    return dataFilePathList

g_funcName = []
g_similar_data = []#元素为(函数1的指令序列，函数2的指令序列，label)，相似label=1，否则为-1
g_dissimilar_data = []#元素为(函数1的指令序列，函数2的指令序列，label)，相似label=1，否则为-1

def LoadData():
    #正负样本比例为1:1
    x86_data = dict()
    x64_data = dict()

    for x86file in GetDataFiles("./data\\x86"):
        data = GetBinaryFileAllFuncDisasm(x86file)
        x86_data.update(data.copy())

    for x86file in GetDataFiles("./data\\x64"):
        data = GetBinaryFileAllFuncDisasm(x86file)
        x64_data.update(data.copy())    

    for funcName in x86_data.keys():
        try:#通过函数名给相似的函数加标签
            f1_insnList = x86_data[funcName]
            f2_insnList = x64_data[funcName]
            g_funcName.append(funcName)
            g_similar_data.append((f1_insnList, f2_insnList, 1))
        except:
            continue

    n = len(g_funcName)
    randList = np.random.choice(range(n), n, replace = False).tolist()#不重复采样
    for i in range(n):
        funcName = g_funcName[randList[i]]
        funcName1 = g_funcName[randList[(i+1)%n]]

        if(i%2):
            g_dissimilar_data.append((x86_data[funcName], x64_data[funcName1], -1))
        else:
            g_dissimilar_data.append((x64_data[funcName], x86_data[funcName1], -1))

    print("count of data:%d" % (len(g_similar_data)*2))

    data = []
    data.extend(g_similar_data)
    data.extend(g_dissimilar_data)
    
    #打乱顺序
    for i in reversed(range(1, len(data))):      
        j = np.random.randint(0, i+1)
        data[i], data[j] = data[j], data[i]

    data_set = MyDataSet(data)
    
    #8:1:1 划分数据集
    n8 = int(len(data_set) * 0.8)
    n1 = int(len(data_set) * 0.1)
    train_set = Subset(data_set, range(0, n8))
    validate_set = Subset(data_set, range(n8, n8+n1))
    test_set = Subset(data_set, range(n8+n1, len(data_set)))

    return train_set, validate_set, test_set

class instruction2vec(nn.Module):
    def __init__(self, word2vec_model_path:str):
        super(instruction2vec, self).__init__()
        word2vec = Word2Vec.load(word2vec_model_path)
        self.embedding = nn.Embedding.from_pretrained(torch.from_numpy(word2vec.wv.vectors))
        self.token_size = word2vec.wv.vector_size#维度大小
        self.key_to_index = word2vec.wv.key_to_index.copy()    #dict
        self.index_to_key = word2vec.wv.index_to_key.copy()    #list
        del word2vec

    def keylist_to_tensor(self, keyList:list):
        indexList = [self.key_to_index[token] for token in keyList]
        return self.embedding(torch.LongTensor(indexList))

    def InsnStr2Tensor(self, insnStr:str) -> torch.tensor:
        insnStr = RefineAsmCode(insnStr)
        tokenList = re.findall('\w+|[\+\-\*\:\[\]\,]', insnStr)
        opcode_tensor =  self.keylist_to_tensor(tokenList[0:1])[0]
        op_zero_tensor = torch.zeros(self.token_size)
        insn_tensor = None
        if(1 == len(tokenList)):
            #没有操作数
            insn_tensor = torch.cat((opcode_tensor, op_zero_tensor, op_zero_tensor), dim=0)
        else:
            op_token_list = tokenList[1:]
            if(op_token_list.count(',') == 0):
                #一个操作数
                op1_tensor = self.keylist_to_tensor(op_token_list)
                insn_tensor = torch.cat((opcode_tensor, op1_tensor.mean(dim=0), op_zero_tensor), dim=0)#tensor.mean求均值后变成一维
                
            elif(op_token_list.count(',') == 1):
                #两个操作数
                dot_index = op_token_list.index(',')
                op1_tensor = self.keylist_to_tensor(op_token_list[0:dot_index])
                op2_tensor = self.keylist_to_tensor(op_token_list[dot_index+1:])
                insn_tensor = torch.cat((opcode_tensor, op1_tensor.mean(dim=0), op2_tensor.mean(dim=0)), dim=0)

            elif(op_token_list.count(',') == 2):
                #三个操作数
                dot1_index = op_token_list.index(',')
                dot2_index = op_token_list.index(',', dot1_index+1)
                op1_tensor = self.keylist_to_tensor(op_token_list[0:dot1_index])
                op2_tensor = self.keylist_to_tensor(op_token_list[dot1_index+1:dot2_index])
                op3_tensor = self.keylist_to_tensor(op_token_list[dot2_index+1:])

                op2_tensor = (op2_tensor.mean(dim=0) + op3_tensor.mean(dim=0)) / 2
                insn_tensor = torch.cat((opcode_tensor, op1_tensor.mean(dim=0), op2_tensor), dim=0)
        
        if(None == insn_tensor):
            print("error: None == insn_tensor")
            raise
        
        insn_size = insn_tensor.shape[0]
        if(self.token_size * 3 != insn_size):
            print("error: (token_size)%d != %d(insn_size)" % (self.token_size, insn_size))
            raise

        return insn_tensor  #[len(tokenList), token_size]

    def forward(self, insnStrList:list) -> torch.tensor:
        insnTensorList = [self.InsnStr2Tensor(insnStr) for insnStr in insnStrList]
        return torch.stack(insnTensorList) #[insn_count, token_size]
    
class SiameseNet(nn.Module):
    def __init__(self, hidden_size=60, n_layers=2, bidirectional = False):
        super(SiameseNet, self).__init__()
        self.insn_embedding = instruction2vec("./insn2vec.model")
        input_size = self.insn_embedding.token_size * 3
        #input_size为指令的维度, hidden_size为整个指令序列的维度
        self.lstm = nn.LSTM(input_size, hidden_size, n_layers, batch_first=True, bidirectional = bidirectional)

        self.D = int(bidirectional)+1

        self.w_omega = nn.Parameter(torch.Tensor(hidden_size * self.D, hidden_size * self.D))
        self.b_omega = nn.Parameter(torch.Tensor(hidden_size * self.D))
        self.u_omega = nn.Parameter(torch.Tensor(hidden_size * self.D, 1))

        nn.init.uniform_(self.w_omega, -0.1, 0.1)
        nn.init.uniform_(self.u_omega, -0.1, 0.1)

        #self.full_connect1 = nn.Linear(hidden_size * self.D, hidden_size * self.D)
        #self.full_connect2 = nn.Linear(hidden_size * self.D, hidden_size * self.D)
        #self.activate = nn.ReLU()

    def attention_score(self, x):
        #x:[batch_size, seq_len, hidden_size*D]
        u = torch.tanh(torch.matmul(x, self.w_omega))
        #u:[batch_size, seq_len, hidden_size*D]
        att = torch.matmul(u, self.u_omega)
        #att:[batch_size, seq_len, 1]
        att_score = F.softmax(att, dim=1)#得到每一个step的hidden权重
        #att_score:[batch_size, seq_len, 1]
        scored_x = x*att_score  #类似矩阵倍乘
        return torch.sum(scored_x, dim=1)#加权求和

    def forward_once(self, input:list) -> torch.tensor:
        lengths = []#记录每个指令序列的长度
        out = []
        for insnStrList in input:
            insnVecTensor = self.insn_embedding(insnStrList)#把指令转换到向量
            out.append(insnVecTensor)
            lengths.append(len(insnStrList))

        pad_out = pad_sequence(out, batch_first=True)#填充0使所有handler的seq_len相同
        pack_padded_out = pack_padded_sequence(pad_out, lengths, batch_first=True, enforce_sorted=False)
        packed_out,(hn,_) = self.lstm(pack_padded_out)#input shape:[batch_size, seq_len, input_size]
        #hn:[D*num_layers,batch_size,hidden_size]
        #out:[batch_size, seq_len, hidden_size*D]，此时out有一些零填充
        out,lengths = pad_packed_sequence(packed_out, batch_first=True)
        out = self.attention_score(out)

        #out = self.full_connect1(out)
        #out = self.activate(out)
        #out = self.full_connect2(out)

        return out

    def forward(self, input1, input2):
        #pdb.set_trace()
        out1 = self.forward_once(input1)#out1:[batch_size,hidden_size]
        out2 = self.forward_once(input2)
        out = F.cosine_similarity(out1, out2, dim=1)
        return out
    
def collate_fn(batch):
    input1 = []#元素为insnStrList
    input2 = []
    labels = []
    for insnStrList1, insnStrList2, label in batch:
        input1.append(insnStrList1)
        input2.append(insnStrList2)
        labels.append(label)

    return input1, input2, labels       

def GetDatasetPredictAndLabels(model:SiameseNet, data:MyDataSet)->torch.tensor:
    with torch.no_grad():
        input1, input2, labels = collate_fn(data)
        return model(input1,input2), labels

g_batch_size = 8

g_train_set, g_validate_set, g_test_set = LoadData()#元素为(insnList1,insnList2,label)
g_train_loader = DataLoader(dataset=g_train_set, batch_size=g_batch_size, shuffle=False, collate_fn=collate_fn)

print("size of g_train_set:%d" % len(g_train_set))

model = SiameseNet(bidirectional=True)
optimizer = torch.optim.SGD(model.parameters(), lr=0.09)
loss_func = nn.MSELoss(reduction='mean')

train_lossList=[]
validate_lossList = []
epochs = 100
for epoch in range(epochs):#开始训练
    train_loss_epoch=0 
    validata_loss_epoch = 0

    #验证集loss
    with torch.no_grad():
        pred, labels = GetDatasetPredictAndLabels(model, g_validate_set)
        validata_loss_epoch = loss_func(pred, torch.FloatTensor(labels)).item()

    for input1, input2, labels in g_train_loader:
        pred = model(input1, input2)

        loss = loss_func(pred, torch.FloatTensor(labels))

        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
      
        train_loss_epoch += loss.item()

    print("%d:train_loss=%0.2f, validate_loss=%0.2f" % (epoch, train_loss_epoch, validata_loss_epoch))                           
    train_lossList.append(train_loss_epoch)
    validate_lossList.append(validata_loss_epoch)

with torch.no_grad():
    #使用验证集制作ROC图
    pred, labels= GetDatasetPredictAndLabels(model, g_validate_set)
    fpr, tpr, thresholds = roc_curve(labels, pred.tolist(), pos_label=1)
    idx = np.argmax(tpr-fpr)
    pred_labels = [1 if label>=thresholds[idx] else -1 for label in pred.tolist()]
    print("optimal threshold:%0.2f, TPR:%0.2f, FPR:%0.2f, accuracy:%f" % (thresholds[idx], tpr[idx], fpr[idx], accuracy_score(labels, pred_labels)))

    plt.figure(1)
    plt.plot(fpr, tpr, label = ("AUC=%0.2f"%(auc(fpr, tpr))))
    plt.xlabel('False Positive Rate')#x轴名称
    plt.ylabel('True Positive Rate')#y轴名称
    plt.legend()
    plt.savefig("roc")

    #计算测试集的准确度
    pred, labels = GetDatasetPredictAndLabels(model, g_test_set)
    pred_labels = [1 if label>=thresholds[idx] else -1 for label in pred.tolist()]
    print("test dataset accuracy:%0.2f " % accuracy_score(labels, pred_labels))

    torch.save(model, "lstm.pt")

#绘制训练集和验证集的loss趋势图
plt.figure(2)
plt.plot([i for i in range(epochs)], train_lossList)
plt.xlabel('epoch')#x轴名称
plt.ylabel('train_loss')#y轴名称
#plt.legend()
plt.savefig("train_loss")

plt.figure(3)
plt.plot([i for i in range(epochs)], validate_lossList)
plt.xlabel('epoch')#x轴名称
plt.ylabel('val_loss')#y轴名称
plt.savefig("val_loss")

plt.show()