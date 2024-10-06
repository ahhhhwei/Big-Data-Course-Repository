import string
import angr
import graph as gh
import re
from gensim.models import Word2Vec
import numpy as np
import os
import pdb

token_dimension = 10

def RefineAsmCode(asmCode:str) -> str:#替换一些数值，降低词库的大小，减少OOV(out of vocabulary)的情况
    asmStr = asmCode
    
    hexNumStrList = re.findall('0x\w+',asmCode)
    
    for hexStr in hexNumStrList:
        if(int(hexStr,16) < 0x5000):#小于0x5000的数值保留
            continue
            
        idx1 = asmCode.find('[')
        idx2 = asmCode.find(']')
        idxHexStr = asmCode.find(hexStr)
        if(-1 != idx1 and -1 != idx2 and idxHexStr < idx2):
            if(hexStr == asmCode[idx1+1:idx2]): 
                asmStr = asmStr.replace(asmCode[idx1+1:idx2], "mem") #[0xXXXXXXXX] -> [mem]
                
            else:
                asmStr = asmStr.replace(hexStr, "disp")#[0xXXXXXXXX + index*scale + base] -> [disp + index*scale + base]
                
        else:
            asmStr = asmStr.replace(hexStr, "imm")   #0xXXXXXXXX -> imm
                
    #asmStr.replace('[','')
    #asmStr.replace(']','')
    #asmStr.replace(':',' ')
    #asmStr = asmStr.replace('byte','')
    #asmStr = asmStr.replace('dword','')
    #asmStr = asmStr.replace('word','')
    #asmStr = asmStr.replace('ptr','')
    
    return asmStr
    
def instruction2vector(model:Word2Vec, asmCode:str, wordDim=token_dimension) -> np.ndarray:
    try:
        mnemonic = asmCode.split()[0]
        insnVec = model.wv[mnemonic]
        
        op_str = asmCode.replace(mnemonic,'')
        op_str = op_str.strip()
        opList = op_str.split(',')
        
        if(len(op_str) == 0):#没有操作数
            insnVec = np.hstack([insnVec,np.zeros(wordDim)])
            insnVec = np.hstack([insnVec,np.zeros(wordDim)])
            
        elif(len(opList) == 1 and len(op_str) > 0): #只有一个操作数  
            opVec = np.zeros(wordDim)
            tokensList = re.findall('\w+|[\+\-\*\:\[\]]', opList[0])           
            for word in tokensList:
                opVec += model.wv[word]
            #line = Word(alphas) + Optional(' ') + Optional(Word(alphas,alphanums)) + Optional(",") + Optional(Word(alphas,alphanums))    
            opVec = float(1 / len(tokensList)) * opVec
                
            insnVec = np.hstack([insnVec,opVec])
            insnVec = np.hstack([insnVec,np.zeros(wordDim)])
         
        elif(len(opList) == 2):  #两个操作数
            for op in opList:  
                opVec = np.zeros(wordDim)
                tokensList = re.findall('\w+|[\+\-\*\:\[\]]', op)
                for word in tokensList:
                    opVec += model.wv[word]               
                    #print(model.wv[word][0:5])
                    
                opVec = float(1 / len(tokensList)) * opVec
                #print(opVec[0:5])
                insnVec = np.hstack([insnVec,opVec])
                
        elif(len(opList) == 3):  #三个操作数当两个操作数处理
            for i,op in enumerate(opList):  
                if(2 == i):
                    break
                opVec = np.zeros(wordDim)
                tokensList = re.findall('\w+|[\+\-\*\:\[\]]', op)
                for word in tokensList:
                    opVec += model.wv[word]               
                    #print(model.wv[word][0:5])
                    
                opVec = float(1 / len(tokensList)) * opVec
                #print(opVec[0:5])
                insnVec = np.hstack([insnVec,opVec])        #三个操作数当两个操作数处理

        else:
            raise
            
        return insnVec
        
    except:      
        print('error: %s' % asmCode)


def GetFunctionInsnStrList(proj, func)->list:
    #proj:<class 'angr.project.Project'>
    #func:<class 'angr.knowledge_plugins.functions.function.Function'>
    #return: list[instruction_string]
    InsnStrList = []
    supergraph = gh.to_supergraph(func.transition_graph)#cfg with ida style 
    supergraph_nodes = sorted(supergraph.nodes(), key = lambda node : node.addr)
    for node in supergraph_nodes:
        for angr_block_node in node.cfg_nodes:
            block_start_addr = angr_block_node.addr
            block = proj.factory.block(block_start_addr)
            for insn in block.capstone.insns:
                InsnStrList.append(insn.mnemonic + " " + insn.op_str)

    return InsnStrList

def GetBinaryFileAllFuncDisasm(FileName:string)->dict:
    ret = {}#{function_name:[instruction_string]}
    proj = angr.Project(FileName, auto_load_libs=False)
    cfg = proj.analyses.CFGFast(normalize = True, start_at_entry=False)
    '''
    function_starts = []
    for sym in proj.loader.main_object.symbols:#获取导出表的函数
        if(sym.is_export):
            function_starts.append(sym.linked_addr)

    cfg = proj.analyses.CFGFast(normalize = True, force_smart_scan=False, symbols=False, \
        start_at_entry=False, function_prologues=False, function_starts=function_starts) 
    ''' 
    for func in cfg.functions.values():
        if(func.size == 0 or func.name[:3] == "sub"):
            continue

        InsnStrList = GetFunctionInsnStrList(proj, func)
        ret[func.name] = InsnStrList

    return ret

def GetDataFiles(root:str) -> list:
    dataFilePathList = []
    for root,dirs,files in os.walk(root):
        for fileName in files:
            dataFilePathList.append(os.path.join(root, fileName))
            
    return dataFilePathList

def GetCorpus()->list:
    tokensList = []

    x86_data = dict()
    x64_data = dict()

    for x86file in GetDataFiles("./data\\x86"):
        data = GetBinaryFileAllFuncDisasm(x86file)
        x86_data.update(data.copy())

    for x86file in GetDataFiles("./data\\x64"):
        data = GetBinaryFileAllFuncDisasm(x86file)
        x64_data.update(data.copy())    

    for insnStrList in x86_data.values():
        for insnStr in insnStrList:        
            insnStr = RefineAsmCode(insnStr)
            tokensList.append(re.findall('\w+|[\+\-\*\:\[\]]', insnStr))

    for insnStrList in x64_data.values():
        for insnStr in insnStrList:        
            insnStr = RefineAsmCode(insnStr)
            tokensList.append(re.findall('\w+|[\+\-\*\:\[\]]', insnStr))
       
    return tokensList

def GenerateInsn2VecModel(wordDim=token_dimension):
    tokensList = GetCorpus()
    #seed=1
    #sg参数默认为0：sg({0, 1}) – Training algorithm: 1 for skip-gram; otherwise CBOW
    model = Word2Vec(tokensList, vector_size=wordDim, negative=15, window=5, min_count=1, workers=1, epochs=10, sg=1)
    
    model.save('insn2vec.model')
    #model = Word2Vec.load("word2vec.model")#加载模型后，可以继续训练
    #model.train([["hello", "world"]], total_examples=1, epochs=1)
    return model

def testInsn2vecModel():
    model = Word2Vec.load("insn2vec.model")
    #model.wv.most_similar('push',topn=10)#余弦相似度
    pdb.set_trace()
    vec = instruction2vector(model,'lea ecx, [ecx + 0x4000]')

if __name__ == "__main__":
    #testInsn2vecModel()
    GenerateInsn2VecModel()  
