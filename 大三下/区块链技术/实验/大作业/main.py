import streamlit as st
from web3 import Web3
import json
import pandas as pd
import base64 

# 初始化Web3连接
w3 = Web3(Web3.HTTPProvider("HTTP://127.0.0.1:7545"))  # 例如Infura或Alchemy的URL

# 加载智能合约ABI
with open("abi.json") as f:
    crowd_funding_abi = json.load(f)

# 设置智能合约地址
crowd_funding_address = "0xfA0d88D6fF4E1100C5558f4D2421ABBE6a2294CA"

# 实例化智能合约
crowd_funding_contract = w3.eth.contract(address=crowd_funding_address, abi=crowd_funding_abi)

def main_bg(main_bg):
    main_bg_ext = "png"
    st.markdown(
        f"""
         <style>
         .stApp {{
             background: url(data:image/{main_bg_ext};base64,{base64.b64encode(open(main_bg, "rb").read()).decode()});
             background-size: cover
         }}
         </style>
         """,
        unsafe_allow_html=True
    )

def main():
    menu = ["全部众筹", "创建众筹", "使用申请", "使用申请投票"]
    main_bg('bac.png')
    choice = st.sidebar.selectbox("菜单", menu)

    # 根据选择显示不同的页面
    if choice == "全部众筹":
        all_crowdfundings()
    elif choice == "创建众筹":
        my_creations()
    elif choice == "使用申请":
        use4apply()
    elif choice == "使用申请投票":
        vote()

# 全部众筹开始
def fetch_crowdfunding_data():
    total_fundings = crowd_funding_contract.functions.getTotalNum().call()
    crowdfunding_data = []

    for i in range(total_fundings):
        title = crowd_funding_contract.functions.getTitle(i).call()
        initiator = crowd_funding_contract.functions.getInitiator(i).call()
        goal = crowd_funding_contract.functions.getGoal(i).call()
        current = crowd_funding_contract.functions.getCurrent(i).call()
        is_success = "成功" if goal == current else "进行中"
        crowdfunding_data.append({
            '名称': title,
            '发起人': initiator[:10] + '...' if len(initiator) > 10 else initiator,
            '目标金额': goal,
            '当前已筹集金额': current,
            '状态': is_success,
        })
    
    return pd.DataFrame(crowdfunding_data)

def display_crowdfunding_table():
    st.title("全部众筹项目")
    df = fetch_crowdfunding_data()

    # 使用 Pandas 样式设置文本居中
    styled_df = df.style.set_properties(**{
        'text-align': 'center'
    }).set_table_styles(
        [{'selector': 'th', 'props': [('text-align', 'center')]}]
    )

    # 渲染表格
    st.write(styled_df.to_html(), unsafe_allow_html=True)

def all_crowdfundings():
    display_crowdfunding_table()
# 全部众筹结束

# 创建众筹开始

def create_new_funding(title, goal, info):
    # 不知道咋用那个环境变量，我就直接传私钥了
    w3.eth.enable_unaudited_features()
    # 发送交易
    account = w3.eth.account.privateKeyToAccount("0x38e382617e446f99e415bd8efcf5895304a04a52d1840656b58be24e03d88979")
    tx_hash = crowd_funding_contract.functions.newFunding(title, goal, info).transact({'from': account.address})
    print("众筹项目已创建")

def my_creations():
    # 创建新的众筹项目表单
    st.title("创建新的众筹项目")
    title = st.text_input("项目标题")
    goal = st.number_input("目标金额", min_value=0)
    info = st.text_area("项目信息")
    if st.button("创建"):
        create_new_funding(title, goal, info)
# 创建众筹结束

def use4apply():
    st.title("众筹资金使用申请")
    # 展示用户参与投资的众筹项目
    Num = st.number_input("项目编号", key="project_number", min_value=0)
    context = st.text_area("使用请求信息")
    Money = st.number_input("金额", key="request_amount", min_value=0)


    if st.button("创建"):
        # 不知道咋用那个环境变量，我就直接传私钥了
        w3.eth.enable_unaudited_features()
        # 发送交易
        account = w3.eth.account.privateKeyToAccount("0x38e382617e446f99e415bd8efcf5895304a04a52d1840656b58be24e03d88979")
        tx_hash = crowd_funding_contract.functions.newUse(Num, context, Money).transact({'from': account.address})
        print("使用请求已创建")



def vote():
    st.title("众筹资金使用申请投票")
    total_fundings = crowd_funding_contract.functions.getTotalNum().call()
    crowdfunding_data = []

    for i in range(total_fundings):
        num = crowd_funding_contract.functions.getUseNum(i).call()
        for j in range(num):
            title = crowd_funding_contract.functions.getTitle(i).call()
            initiator = crowd_funding_contract.functions.getInitiator(i).call()
            goal = crowd_funding_contract.functions.getGoal(i).call()
            current = crowd_funding_contract.functions.getCurrent(i).call()
            useContext = crowd_funding_contract.functions.getUseContent(i, j).call()
            useMoney = crowd_funding_contract.functions.getUseMoney(i, j).call()
            piao = crowd_funding_contract.functions.getUseAgreeNum(i, j).call()

            
            print(useContext)
            is_success = "成功" if goal == current else "进行中"
            crowdfunding_data.append({
                '名称': title,
                '发起人': initiator[:10] + '...' if len(initiator) > 10 else initiator,
                '目标金额': goal,
                '当前已筹集金额': current,
                '状态': is_success,
                '使用请求内容': useContext,
                '使用请求金额': useMoney,
                '使用请求票数': piao,
            })
    
    df = pd.DataFrame(crowdfunding_data)

    styled_df = df.style.set_properties(**{
        'text-align': 'center'
    }).set_table_styles(
        [{'selector': 'th', 'props': [('text-align', 'center')]}]
    )

    # 渲染表格
    st.write(styled_df.to_html(), unsafe_allow_html=True)


if __name__ == "__main__":
    main()