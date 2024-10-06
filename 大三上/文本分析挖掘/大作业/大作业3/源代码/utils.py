# import logging, sys, argparse


# def str2bool(v):
#     # copy from StackOverflow
#     if v.lower() in ('yes', 'true', 't', 'y', '1'):
#         return True
#     elif v.lower() in ('no', 'false', 'f', 'n', '0'):
#         return False
#     else:
#         raise argparse.ArgumentTypeError('Boolean value expected.')


# def get_entity(tag_seq, char_seq):
#     PER = get_PER_entity(tag_seq, char_seq)
#     LOC = get_LOC_entity(tag_seq, char_seq)
#     ORG = get_ORG_entity(tag_seq, char_seq)
#     return PER, LOC, ORG


# def get_PER_entity(tag_seq, char_seq):
#     length = len(char_seq)
#     PER = []
#     for i, (char, tag) in enumerate(zip(char_seq, tag_seq)):
#         if tag == 'B-PER':
#             if 'per' in locals().keys():
#                 PER.append(per)
#                 del per
#             per = char
#             if i+1 == length:
#                 PER.append(per)
#         if tag == 'I-PER':
#             per += char
#             if i+1 == length:
#                 PER.append(per)
#         if tag not in ['I-PER', 'B-PER']:
#             if 'per' in locals().keys():
#                 PER.append(per)
#                 del per
#             continue
#     return PER


# def get_LOC_entity(tag_seq, char_seq):
#     length = len(char_seq)
#     LOC = []
#     for i, (char, tag) in enumerate(zip(char_seq, tag_seq)):
#         if tag == 'B-LOC':
#             if 'loc' in locals().keys():
#                 LOC.append(loc)
#                 del loc
#             loc = char
#             if i+1 == length:
#                 LOC.append(loc)
#         if tag == 'I-LOC':
#             loc += char
#             if i+1 == length:
#                 LOC.append(loc)
#         if tag not in ['I-LOC', 'B-LOC']:
#             if 'loc' in locals().keys():
#                 LOC.append(loc)
#                 del loc
#             continue
#     return LOC


# def get_ORG_entity(tag_seq, char_seq):
#     length = len(char_seq)
#     ORG = []
#     for i, (char, tag) in enumerate(zip(char_seq, tag_seq)):
#         if tag == 'B-ORG':
#             if 'org' in locals().keys():
#                 ORG.append(org)
#                 del org
#             org = char
#             if i+1 == length:
#                 ORG.append(org)
#         if tag == 'I-ORG':
#             org += char
#             if i+1 == length:
#                 ORG.append(org)
#         if tag not in ['I-ORG', 'B-ORG']:
#             if 'org' in locals().keys():
#                 ORG.append(org)
#                 del org
#             continue
#     return ORG


# def get_logger(filename):
#     logger = logging.getLogger('logger')
#     logger.setLevel(logging.DEBUG)
#     logging.basicConfig(format='%(message)s', level=logging.DEBUG)
#     handler = logging.FileHandler(filename)
#     handler.setLevel(logging.DEBUG)
#     handler.setFormatter(logging.Formatter('%(asctime)s:%(levelname)s: %(message)s'))
#     logging.getLogger().addHandler(handler)
#     return logger



import logging, sys, argparse


def str2bool(v):
    # copy from StackOverflow
    if v.lower() in ('yes', 'true', 't', 'y', '1'):
        return True
    elif v.lower() in ('no', 'false', 'f', 'n', '0'):
        return False
    else:
        raise argparse.ArgumentTypeError('Boolean value expected.')


def get_entity(tag_seq, char_seq):
    PRO = get_PRO_entity(tag_seq, char_seq)
    DIS = get_DIS_entity(tag_seq, char_seq)
    DRU = get_DRU_entity(tag_seq, char_seq)
    BOD = get_BOD_entity(tag_seq, char_seq)
    SYM = get_SYM_entity(tag_seq, char_seq)
    MIC = get_MIC_entity(tag_seq, char_seq)
    EQU = get_EQU_entity(tag_seq, char_seq)
    ITE = get_ITE_entity(tag_seq, char_seq)
    DEP = get_DEP_entity(tag_seq, char_seq)
    return PRO, DIS, DRU, BOD, SYM, MIC, EQU, ITE, DEP


def get_PRO_entity(tag_seq, char_seq):
    length = len(char_seq)
    PRO = []
    for i, (char, tag) in enumerate(zip(char_seq, tag_seq)):
        if tag == 'B-pro':
            if 'pro' in locals().keys():
                PRO.append(pro)
                PRO.append(i - len(pro))
                PRO.append(i)
                print(locals().keys())
                del pro
            pro = char
            if i+1 == length:
                PRO.append(pro)
                PRO.append(i - len(pro))
                PRO.append(i)
        if tag == 'I-pro':
            if 'pro' not in locals().keys():
                pro = char
            pro += char
            if i+1 == length:
                PRO.append(pro)
                PRO.append(i - len(pro))
                PRO.append(i)
        if tag not in ['I-pro', 'B-pro']:
            if 'pro' in locals().keys():
                PRO.append(pro)
                PRO.append(i - len(pro))
                PRO.append(i)
                print(locals().keys())
                del pro
            continue
    return PRO


def get_DIS_entity(tag_seq, char_seq):
    print(tag_seq)
    print(char_seq)
    length = len(char_seq)
    DIS = []
    for i, (char, tag) in enumerate(zip(char_seq, tag_seq)):
        if tag == 'B-dis':
            if 'dis' in locals().keys():
                DIS.append(dis)
                DIS.append(i - len(dis))
                DIS.append(i)
                del dis
            dis = char
            if i+1 == length:
                DIS.append(dis)
                DIS.append(i - len(dis))
                DIS.append(i)
        if tag == 'I-dis':
            if 'dis' not in locals().keys():
                dis = char 
            dis += char
            if i+1 == length:
                DIS.append(dis)
                DIS.append(i - len(dis))
                DIS.append(i)
        if tag not in ['I-dis', 'B-dis']:
            if 'dis' in locals().keys():
                DIS.append(dis)
                DIS.append(i - len(dis))
                DIS.append(i)
                del dis
            continue
    return DIS


def get_DRU_entity(tag_seq, char_seq):
    length = len(char_seq)
    DRU = []
    for i, (char, tag) in enumerate(zip(char_seq, tag_seq)):
        if tag == 'B-dru':
            if 'dru' in locals().keys():
                DRU.append(dru)
                DRU.append(i - len(dru))
                DRU.append(i)
                print(locals().keys())
                del dru
            dru = char
            if i+1 == length:
                DRU.append(dru)
                DRU.append(i - len(dru))
                DRU.append(i)
        if tag == 'I-dru':
            if 'dru' not in locals().keys():
                dru = char 
            dru += char
            if i+1 == length:
                DRU.append(dru)
                DRU.append(i - len(dru))
                DRU.append(i)
        if tag not in ['I-dru', 'B-dru']:
            if 'dru' in locals().keys():
                DRU.append(dru)
                DRU.append(i - len(dru))
                DRU.append(i)
                print(locals().keys())
                del dru
            continue
    return DRU


def get_BOD_entity(tag_seq, char_seq):
    length = len(char_seq)
    BOD = []
    for i, (char, tag) in enumerate(zip(char_seq, tag_seq)):
        if tag == 'B-bod':
            if 'bod' in locals().keys():
                BOD.append(bod)
                BOD.append(i - len(bod))
                BOD.append(i)
                del bod
            bod = char
            if i+1 == length:
                BOD.append(bod)
                BOD.append(i - len(bod))
                BOD.append(i)
        if tag == 'I-bod':
            if 'bod' not in locals().keys():
                bod = char 
            bod += char
            if i+1 == length:
                BOD.append(bod)
                BOD.append(i - len(bod))
                BOD.append(i)
        if tag not in ['I-bod', 'B-bod']:
            if 'bod' in locals().keys():
                BOD.append(bod)
                BOD.append(i - len(bod))
                BOD.append(i)
                del bod
            continue
    return BOD


def get_SYM_entity(tag_seq, char_seq):
    length = len(char_seq)
    SYM = []
    for i, (char, tag) in enumerate(zip(char_seq, tag_seq)):
        if tag == 'B-sym':
            if 'sym' in locals().keys():
                SYM.append(sym)
                SYM.append(i - len(sym))
                SYM.append(i)
                del sym
            sym = char
            if i+1 == length:
                SYM.append(sym)
                SYM.append(i - len(sym))
                SYM.append(i)
        if tag == 'I-sym':
            if 'sym' not in locals().keys():
                sym = char
            sym += char
            if i+1 == length:
                SYM.append(sym)
                SYM.append(i - len(sym))
                SYM.append(i)
        if tag not in ['I-sym', 'B-sym']:
            if 'sym' in locals().keys():
                SYM.append(sym)
                SYM.append(i - len(sym))
                SYM.append(i)
                del sym
            continue
    return SYM


def get_MIC_entity(tag_seq, char_seq):
    length = len(char_seq)
    MIC = []
    for i, (char, tag) in enumerate(zip(char_seq, tag_seq)):
        if tag == 'B-mic':
            if 'mic' in locals().keys():
                MIC.append(mic)
                MIC.append(i - len(mic))
                MIC.append(i)
                del mic
            mic = char
            if i+1 == length:
                MIC.append(mic)
                MIC.append(i - len(mic))
                MIC.append(i)
        if tag == 'I-mic':
            if 'mic' not in locals().keys():
                mic = char 
            mic += char
            if i+1 == length:
                MIC.append(mic)
                MIC.append(i - len(mic))
                MIC.append(i)
        if tag not in ['I-mic', 'B-mic']:
            if 'mic' in locals().keys():
                MIC.append(mic)
                MIC.append(i - len(mic))
                MIC.append(i)
                del mic
            continue
    return MIC


def get_EQU_entity(tag_seq, char_seq):
    length = len(char_seq)
    EQU = []
    for i, (char, tag) in enumerate(zip(char_seq, tag_seq)):
        if tag == 'B-equ':
            if 'equ' in locals().keys():
                EQU.append(equ)
                EQU.append(i - len(equ))
                EQU.append(i)
                del equ
            equ = char
            if i+1 == length:
                EQU.append(equ)
                EQU.append(i - len(equ))
                EQU.append(i)
        if tag == 'I-equ':
            if 'equ' not in locals().keys():
                equ = char 
            equ += char
            if i+1 == length:
                EQU.append(equ)
                EQU.append(i - len(equ))
                EQU.append(i)
        if tag not in ['I-equ', 'B-equ']:
            if 'equ' in locals().keys():
                EQU.append(equ)
                EQU.append(i - len(equ))
                EQU.append(i)
                del equ
            continue
    return EQU


def get_ITE_entity(tag_seq, char_seq):
    length = len(char_seq)
    ITE = []
    for i, (char, tag) in enumerate(zip(char_seq, tag_seq)):
        if tag == 'B-ite':
            if 'ite' in locals().keys():
                ITE.append(ite)
                ITE.append(i - len(ite))
                ITE.append(i)
                del ite
            ite = char
            if i+1 == length:
                ITE.append(ite)
                ITE.append(i - len(ite))
                ITE.append(i)
        if tag == 'I-ite':
            if 'ite' not in locals().keys():
                ite = char
            ite += char
            if i+1 == length:
                ITE.append(ite)
                ITE.append(i - len(ite))
                ITE.append(i)
        if tag not in ['I-ite', 'B-ite']:
            if 'ite' in locals().keys():
                ITE.append(ite)
                ITE.append(i - len(ite))
                ITE.append(i)
                del ite
            continue
    return ITE


def get_DEP_entity(tag_seq, char_seq):
    length = len(char_seq)
    DEP = []
    for i, (char, tag) in enumerate(zip(char_seq, tag_seq)):
        if tag == 'B-dep':
            if 'dep' in locals().keys():
                DEP.append(dep)
                DEP.append(i - len(dep))
                DEP.append(i)
                del dep
            dep = char
            if i+1 == length:
                DEP.append(dep)
                DEP.append(i - len(dep))
                DEP.append(i)
        if tag == 'I-DEP':
            if dep not in locals().keys():
                dep = char
            dep += char
            if i+1 == length:
                DEP.append(dep)
                DEP.append(i - len(dep))
                DEP.append(i)
        if tag not in ['I-dep', 'B-dep']:
            if 'dep' in locals().keys():
                DEP.append(dep)
                DEP.append(i - len(dep))
                DEP.append(i)
                del dep
            continue
    return DEP


def get_logger(filename):
    logger = logging.getLogger('logger')
    logger.setLevel(logging.DEBUG)
    logging.basicConfig(format='%(message)s', level=logging.DEBUG)
    handler = logging.FileHandler(filename)
    handler.setLevel(logging.DEBUG)
    handler.setFormatter(logging.Formatter('%(asctime)s:%(levelname)s: %(message)s'))
    logging.getLogger().addHandler(handler)
    return logger
