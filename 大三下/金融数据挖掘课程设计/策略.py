#加载库函数
import datetime                       #加载时间函数库
import numpy as np
import pandas as pd
from sklearn.cross_validation import train_test_split
from sklearn.metrics import precision_recall_curve
from sklearn.metrics import classification_report
from sklearn.linear_model.logistic import LogisticRegression
from sklearn.svm import SVC


#初始化回测环境
start = '20240101'                    # 回测起始时间 注：支持两种日期表述形式（ '2015-01-01'，'20150101'）
end = '20240517'                      # 回测结束时间
benchmark = '000002.ZICN'             # 策略参考标准为A股指数
universe = set_universe('A')          # 证券池：可供选择的股票的范围为A股.（由于选股条件比较苛刻，所以为了保证有充足的可供选择股票，因此以整个A股作为投资范围）
freq = 'd'                            # 用日线回测的策略
refresh_rate = 2                      # 每10日调一次仓，即每个交易日都会运行第三部分的handle_data函数

def trading(buylist,context):      
    #数据获取（通用部分）：投资者账户，可供投资股票
    account = context.get_account('fantasy_account')                                        #获取投资者的股票账户（fantasy_account）
    current_universe = context.get_universe(asset_type = 'stock',exclude_halt=True)         #获取当前除停牌外的所有可供投资股票（universe）   
    security_position = account.get_positions()                                             #字典型数据，上一K线结束后的有效证券头寸，即持仓数量大于0的证券及其头寸
    cash = account.cash                                                                     #获取股票账户可用于投资的现金额度
    
    #交易执行部分：卖出
    for sec in current_universe:
        if sec not in buylist and sec in security_position:                                 #不在buylist中，且有持仓，卖出        
            order_to(sec,0)                                                                 #执行卖出指令后,会自动更新股票账户中的金额
    #交易执行部分：买入
    if len(buylist) > 0:                                                                    #判读本期是否有需要买入股票（buylist>0）
            weight = min(Max_Position_per,1.0/len(buylist))                                 #每只股票所分配的金额相同，但最多为总金额的10%
    else:
        weight = 0                                                                          #若本期没有要购入股票，设置分配权重为0
    for sec in buylist:                                                                     #判断股票是否为本期要购入股票且尚未持有
        if sec not in security_position:
            order_pct_to(sec,weight)                                                        #购入指定比例的股票    
def stock_sellection_stock(context):
    """
    前一天的历史数据（前一天的x）训练今天的数据(今天的y)，再用今天的数据（今天的x）预测明天的数据（明天的y）。
    """
    buylist=[]
    #数据获取（通用部分）：投资者账户，可供投资股票  
    hist=DataAPI.MktIdxdGet(tradeDate=u"",indexID=u"000001.ZICN",ticker=u"",beginDate=start,
                                endDate=end,exchangeCD=u"XSHE,XSHG",field=u"",
                                pandas="1")[(["tradeDate","closeIndex"])]
    previous_date = context.previous_date                                                           #获取上一交易日的时间
    current_date = context.current_date                                                             #获取本交易日的时间
        
    pre3_date = context.current_date-datetime.timedelta(days=3) 
    pre2_date = context.current_date-datetime.timedelta(days=2)
    previous_date = previous_date.strftime('%Y%m%d')                                                #将日期格式调整为%Y%m%d形式（20240101），方便读取因子数据
    account = context.get_account('fantasy_account')                                                #获取投资者的股票账户（fantasy_account）
    current_universe = context.get_universe(asset_type = 'stock',exclude_halt=True) 
    
    #获取T-3日的所有HS300成分股的部分有效因子作为(训练集)
    
    yes_factor = DataAPI.MktStockFactorsOneDayGet(tradeDate=pre3_date,secID=current_universe,field=['secID','PB','PE','PS','LCAP','CTOP','DebtEquityRatio','ROE','ROA','EPS','CurrentRatio','DAVOL10','DAVOL5','MA5','MA10','MA20','MFI','ATR6','BIAS10','CCI5','BollDown','BollUp','ROC6'],pandas="1")
    yes_factor2 = DataAPI.MktStockFactorsOneDayGet(tradeDate=pre2_date,secID=current_universe,field=['secID','PB','PE','PS','LCAP','CTOP','DebtEquityRatio','ROE','ROA','EPS','CurrentRatio','DAVOL10','DAVOL5','MA5','MA10','MA20','MFI','ATR6','BIAS10','CCI5','BollDown','BollUp','ROC6'],pandas="1")
    while(yes_factor.shape[0]==0):
        if (yes_factor.shape[0]==0):
            pre3_date =pre3_date - datetime.timedelta(days=1)
            yes_factor = DataAPI.MktStockFactorsOneDayGet(tradeDate=pre3_date,secID=current_universe,field=['secID','PB','PE','PS','LCAP','CTOP','DebtEquityRatio','ROE','ROA','EPS','CurrentRatio','DAVOL10','DAVOL5','MA5','MA10','MA20','MFI','ATR6','BIAS10','CCI5','BollDown','BollUp','ROC6'],pandas="1")
    
    
    while(yes_factor2.shape[0]==0):
        if (yes_factor2.shape[0]==0):
            pre2_date =  pre2_date - datetime.timedelta(days=1)
            yes_factor2 = DataAPI.MktStockFactorsOneDayGet(tradeDate=pre2_date,secID=current_universe,field=['secID','PB','PE','PS','LCAP','CTOP','DebtEquityRatio','ROE','ROA','EPS','CurrentRatio','DAVOL10','DAVOL5','MA5','MA10','MA20','MFI','ATR6','BIAS10','CCI5','BollDown','BollUp','ROC6'],pandas="1")
    #数据处理部分（数据结构部分）： 去掉无效数据并设定索引
    yes_factor = yes_factor.dropna()       #去掉无效数据
    #数据处理部分（逻辑部分）:将所有因子数据标准化
    yes_factor.set_index(['secID'],inplace=True,drop=True)
    yes_factor_train=yes_factor[['PB','PE','PS','LCAP','CTOP','DebtEquityRatio','ROE','ROA','EPS','CurrentRatio','DAVOL10','DAVOL5','MA5','MA10','MA20','MFI','ATR6','BIAS10','CCI5','BollDown','BollUp','ROC6']]
    yes_factor_train = yes_factor_train.apply(lambda x: (x-x.mean())/x.std(), axis=0)
    #拿出今天的收盘价作为(训练集的结果验证)
    cur_price=DataAPI.MktEqudGet(secID=current_universe,tradeDate="",beginDate=pre2_date,endDate=current_date,isOpen="",field=u"",pandas="1")#先拿出前天、昨天、今天的三天数据，然后用分组
    cur_price=cur_price.groupby(['secID'])['chgPct'].sum()
    cur_price = pd.DataFrame(cur_price, columns = ['chgPct'])
    cur_price['label']=0
    cur_price = cur_price.dropna()
    #cur_price.set_index(['secID'],inplace=True,drop=True)
    
    cur_price.loc[cur_price['chgPct']>0.02,'label']=1
    cur_price.loc[cur_price['chgPct']<=0.02,'label']=0

    cur_price=cur_price.loc[cur_price.index.isin(yes_factor_train.index),:]
    yes_factor_train=yes_factor_train.loc[yes_factor_train.index.isin(cur_price.index),:]
    #print(yes_factor_train)
    #获取T日的所有HS300成分股的部分有效因子作为(测试集)
    yes_factor_test = DataAPI.MktStockFactorsOneDayGet(tradeDate=current_date,secID=current_universe,field=['secID','PB','PE','PS','LCAP','CTOP','DebtEquityRatio','ROE','ROA','EPS','CurrentRatio','DAVOL10','DAVOL5','MA5','MA10','MA20','MFI','ATR6','BIAS10','CCI5','BollDown','BollUp','ROC6'],pandas="1")
    #数据处理部分（数据结构部分）： 去掉无效数据并设定索引
    yes_factor_test = yes_factor_test.dropna()                                                                  #去掉无效数据
    #数据处理部分（逻辑部分）:将所有因子数据标准化
    yes_factor_test.set_index(['secID'],inplace=True,drop=True)
    yes_factor_test=yes_factor_test[['PB','PE','PS','LCAP','CTOP','DebtEquityRatio','ROE','ROA','EPS','CurrentRatio','DAVOL10','DAVOL5','MA5','MA10','MA20','MFI','ATR6','BIAS10','CCI5','BollDown','BollUp','ROC6']]
    yes_factor_test = yes_factor_test.apply(lambda x: (x-x.mean())/x.std(), axis=0)
     # 剔除T+1日涨停的股票（测试集的T+1日去预测T+2日，T+1日涨停的股票在T+1的尾盘没法买入T+2日的股票，直接剔除），series可以直接和某个数值比较
    yes_factor_test_avilible=cur_price[cur_price['chgPct']<0.095].index
    yes_factor_test=yes_factor_test.loc[yes_factor_test.index.isin(yes_factor_test_avilible),:]
    
    # 1.
    #用SVM开始训练类别
    clf = SVC(C=80, kernel='rbf', gamma=0.2,
               decision_function_shape='ovr')  # 高斯核，gamma值越小，分类界面越连续；gamma值越大，分类界面越“散”，分类效果越好，但有可能会过拟合
    clf.fit(yes_factor_train.values,cur_price['label'].values)
    
    # 2.
    # from sklearn.neural_network import MLPClassifier

    # # 实例化一个多层感知器分类器
    # clf = MLPClassifier(hidden_layer_sizes=(100, 50), max_iter=300, alpha=1e-4,
    #                     solver='sgd', activation='relu', random_state=1,
    #                     learning_rate_init=.1)

    # clf.fit(yes_factor_train.values, cur_price['label'].values)

    # 3.
    # from sklearn.ensemble import RandomForestClassifier

    # # 实例化随机森林分类器
    # clf = RandomForestClassifier(n_estimators=100, max_depth=10, random_state=0)

    # clf.fit(yes_factor_train.values, cur_price['label'].values)

    # 4.
    # from sklearn.naive_bayes import GaussianNB

    # # 实例化高斯朴素贝叶斯分类器，适用于连续特征
    # clf = GaussianNB()

    # clf.fit(yes_factor_train.values, cur_price['label'].values)

    # 5.
    # from sklearn.ensemble import ExtraTreesClassifier

    # # 实例化ExtraTrees分类器
    # clf = ExtraTreesClassifier(n_estimators=100, random_state=0)

    # clf.fit(yes_factor_train.values, cur_price['label'].values)

    # 6.
    # from sklearn.ensemble import AdaBoostClassifier

    # # 实例化AdaBoost分类器
    # clf = AdaBoostClassifier(n_estimators=50, learning_rate=1.0, random_state=0)

    # clf.fit(yes_factor_train.values, cur_price['label'].values)

    # 进行预测并保存数据，predict_proba是可以得到每行预测的值落入某个类别的概率。所有行取第1列，代表所有行涨的概率
    prediction1 = clf.predict(yes_factor_test.values)
    yes_factor_test['prediction'] = prediction1
    yes_factor_test2=yes_factor_test[yes_factor_test['prediction']==1]
    yes_factor_test2=yes_factor_test2[['PB','PE','PS','LCAP','CTOP','DebtEquityRatio','ROE','ROA','EPS','CurrentRatio','DAVOL10','DAVOL5','MA5','MA10','MA20','MFI','ATR6','BIAS10','CCI5','BollDown','BollUp','ROC6']]
    
    #SVM训练出来为1的再用logistic模型训练，为1概率最大的20只
    clf2 = LogisticRegression()
    clf2.fit(yes_factor_train.values, cur_price['label'])
    # 进行预测并保存数据，predict_proba是可以得到每行预测的值落入某个类别的概率。所有行取第1列，代表所有行涨的概率
    prediction2 = clf2.predict_proba(yes_factor_test2.values)
    yes_factor_test2['prediction'] = prediction2[:,1]
    
    # 逻辑回归策略买入了所有预测为上涨的股票，这里改进为买入上涨概率最大（prediction列）的20只股票；按降序排列
    yes_factor_test2.sort_values(by='prediction', inplace=True, ascending=False)

    #i=a['secID'].tolist()
    buylist =  yes_factor_test2[:20].index.tolist()     #选择前10只作为选择的股,生成buylist
    #print (buylist)
    return  list(buylist)                    #返回buylist

#初始化投资者（账户）参数
#accounts为字典类型，代表投资者所有的账户，而字典中每一个键代表一个账户，而每一个键对应的值为该账户的初始情况，如本程序中的键为fantasy_account（股票账户），值为相应配置
accounts = {
    'fantasy_account': AccountConfig(account_type='security', capital_base=10000000)  #初始化投资者的股票账户： 投资品种为股票，初始投资金额为1千万
}

#初始化策略参数:
Max_Position_per = 0.1             #每只股票购入的最高比例为10%

#初始化回测环境，指明创建账户时的工作，全局只运行一次
def initialize(context):
    pass
        
#handle_data函数是策略的核心函数，包含了所有策略算法的内容，包括数据获取，交易信号生成，订单委托等逻辑。
#handle_data函数无论是回测还是模拟交易场景，这个函数会根据回测频率 freq 的设置被调用。当freq='d'时，每天被调用一次，当freq='m'时，每分钟被调用一次。
def handle_data(context):
    buylist = stock_sellection_stock(context)     # 选股策略
    trading(buylist,context)                                   # 基于固定投资比例的仓位管理策略