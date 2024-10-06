// SPDX-License-Identifier: GPL3.0
pragma solidity ^0.6.0;

// 一个众筹
contract CrowdFunding {
    string public title;                              // 众筹标题
    address payable public initiator;                 // 众筹发起人
    uint public goal;                                 // 众筹目标金额
    string public info;                               // 众筹详情
    uint public remainder;                            // 众筹剩余可用金额(成功后)
    uint public current;                              // 众筹已筹金额
    uint public funderNum;                            // 参与者数量
    bool public isSuccessful;                         // 众筹是否成功
    address[] public funders;                         // 所有参与者
    mapping(address => uint) public funderMoney;      // 各参与者投的钱
    mapping(address => uint) public funderId;         // 各参与者序号

    // 使用请求
    struct Use {
        string content;     // 请求内容
        uint money;         // 请求金额
        uint agreeNum;      // 同意票数
        uint disagreeNum;   // 不同意票数
        mapping(address => bool) isVote;  // 每个参与者是否投票
    }
    Use[] public allUses;   // 所有使用请求

    constructor(string memory _title, address payable _initiator, uint _goal, string memory _info) public {
        title = _title;
        initiator = _initiator;
        goal = _goal;
        info = _info;
        current = 0;
        remainder = _goal;
        funderNum = 0;
    }

    // 往一个众筹里投钱
    function contribute(uint money, address _funder) payable public{
        require(money>0 && money<=goal-current);
        //require(isSuccessful == false);

        current = current + money;
        if(funderId[_funder]!=0){
            funderMoney[_funder] += money;
        }
        else{
            funderMoney[_funder] = money;
            funders.push(_funder);
            funderNum++;
            funderId[_funder] = uint(funders.length);
        }
    }

    // 退钱
    function returnMoney(address _funder) public{
        require(funderId[_funder]!=0 && funderMoney[_funder]>0);
        require(current<goal);

        address payable funderAddr = address(uint160(_funder));
        funderAddr.transfer(funderMoney[_funder]);
        current -= funderMoney[_funder];
        funderId[_funder] = 0;
        funderMoney[_funder] = 0;
    }

    // 创建使用请求
    function newUse(address _funder, string calldata _content, uint _money) public{
        require(_funder == initiator);
        require(_money <= remainder);
        require(goal == current);

        remainder -= _money;
        allUses.push(Use({
            content: _content,
            money: _money,
            agreeNum: 0,
            disagreeNum: 0
        }));
    }

    // 给使用请求投票
    function voteForUse(address _funder, uint index, bool agree) payable public{
        require(goal == current);
        require(allUses[index].isVote[_funder] != true);
        require(funderId[_funder]!=0 && funderMoney[_funder]>0);
        require(allUses[index].agreeNum < (goal + 1) / 2);
        require(allUses[index].disagreeNum < (goal + 1) / 2);
        
        //require(isSuccessful == true);

        allUses[index].isVote[_funder] = true;
        uint leastMoney = (goal + 1) / 2;
        if(agree==true){
            allUses[index].agreeNum += funderMoney[_funder];
            if(allUses[index].agreeNum >= leastMoney){
                initiator.transfer(allUses[index].money);
            }
        }
        else{
            allUses[index].disagreeNum += funderMoney[_funder];
            if(allUses[index].disagreeNum >= leastMoney){
                remainder += allUses[index].money;
            }
        }
    }

    // 空投到众筹项目的参与者
    function airdrop(uint totalAirdropAmount) public {
        if (goal==current) {
            // 计算每个参与者的空投份额
            uint perFunderShare = totalAirdropAmount / funderNum;
            
            // 遍历所有参与者并进行空投
            for (uint j = 0; j < funderNum; j++) {
                address funder = funders[j]; 
                payable(funder).transfer(perFunderShare);
                remainder -= perFunderShare;
            }
        }
    }

    // 获取使用请求总数
    function getUseNum() public view returns(uint){
        return allUses.length;
    }

    // 获取使用请求内容
    function getUseContent(uint index) public view returns(string memory){
        return allUses[index].content;
    }

    // 获取使用请求金额
    function getUseMoney(uint index) public view returns(uint){
        return allUses[index].money;
    }

    // 获取使用请求同意数量
    function getUseAgreeNum(uint index) public view returns(uint){
        return allUses[index].agreeNum;
    }

    // 获取使用请求不同意数量
    function getUseDisagreeNum(uint index) public view returns(uint){
        return allUses[index].disagreeNum;
    }

    // 获取参与者是否已对某使用请求投票
    function getUseVote(uint index, address funder) public view returns(bool){
        return allUses[index].isVote[funder];
    }

    // 获取参与者在一个众筹里投的钱
    function getFunderMoney(address funder) public view returns(uint){
        return funderMoney[funder];
    }

    // 获取众筹地址
    function getAddress() public view returns(address payable){
        return address(this);
    }

    // 合约余额查询
    function getContractBalance() public view returns (uint) {
        return address(this).balance;
    }

    fallback() payable external {}
    receive () payable external {}

}

// 所有众筹
contract AllFundings {
    address payable[] fundings;
    // 创建众筹项目
    function newFunding(string calldata title, uint goal, string calldata info) public{
        CrowdFunding funding = new CrowdFunding(title, msg.sender, goal, info);
        fundings.push(funding.getAddress());
    }

    // 给一个众筹项目投钱
    function contribute(uint i) payable public {
        address payable fundingAddr = fundings[i];
        CrowdFunding(fundingAddr).contribute(uint(msg.value), msg.sender);
        fundingAddr.transfer(msg.value); 
        // 众筹成功自动执行空投 
        // 这里不判断众筹成功，而是放在airdrop里判断
        // if(CrowdFunding(fundingAddr).isSuccessful() == true) {
            CrowdFunding(fundingAddr).airdrop(getGoal(i) / 10);
        // }
    }

    // 退钱
    function returnMoney(uint i) payable public {
        address payable fundingAddr = fundings[i];
        CrowdFunding(fundingAddr).returnMoney(msg.sender);
    } 

    // 创建使用请求
    function newUse(uint i, string calldata content, uint money) public {
        address payable fundingAddr = fundings[i];
        CrowdFunding(fundingAddr).newUse(msg.sender, content, money);
    }

    // 给使用请求投票
    function voteForUse(uint i, uint useId, bool isAgree) public {
        address payable fundingAddr = fundings[i];
        CrowdFunding(fundingAddr).voteForUse(msg.sender, useId, isAgree);
    }

    // 获取众筹总数
    function getTotalNum() public view returns(uint){
        return fundings.length;
    }

    // 获取某众筹地址
    function getAddress(uint i) public view returns(address payable){
        return fundings[i];
    }

    // 获取某众筹标题
    function getTitle(uint i) public view returns(string memory){
        return CrowdFunding(fundings[i]).title();
    }

    // 获取某众筹发起人
    function getInitiator(uint i) public view returns(address payable){
        return CrowdFunding(fundings[i]).initiator();
    }

    // 获取某众筹目标金额
    function getGoal(uint i) public view returns(uint){
        return CrowdFunding(fundings[i]).goal();
    }

    // 获取某众筹当前已筹金额
    function getCurrent(uint i) public view returns(uint){
        return CrowdFunding(fundings[i]).current();
    }

    // 获取某众筹剩余可用金额
    function getRemainder(uint i) public view returns(uint){
        // return CrowdFunding(fundings[i]).remainder();
        return  CrowdFunding(fundings[i]).getContractBalance();
    }

    // 获取某众筹详细信息
    function getInfo(uint i) public view returns(string memory){
        return CrowdFunding(fundings[i]).info();
    }

    // 获取某参与者在某众筹中投的钱
    function getFunderMoney(uint i, address funder) public view returns(uint){
        return CrowdFunding(fundings[i]).getFunderMoney(funder);
    }

    // 获取某众筹的使用请求总数
    function getUseNum(uint i) public view returns(uint){
        return CrowdFunding(fundings[i]).getUseNum();
    }

    // 获取某众筹的某使用请求内容
    function getUseContent(uint i, uint j) public view returns(string memory){
        return CrowdFunding(fundings[i]).getUseContent(j);
    }

    // 获取某众筹的某使用请求金额
    function getUseMoney(uint i, uint j) public view returns(uint){
        return CrowdFunding(fundings[i]).getUseMoney(j);
    }

    // 获取某众筹的某使用请求同意数量
    function getUseAgreeNum(uint i, uint j) public view returns(uint){
        return CrowdFunding(fundings[i]).getUseAgreeNum(j);
    }

    // 获取某众筹的某使用请求不同意数量
    function getUseDisagreeNum(uint i, uint j) public view returns(uint){
        return CrowdFunding(fundings[i]).getUseDisagreeNum(j);
    }

    // 获取某众筹的某参与者是否已经针对某使用请求投票
    function getUseVote(uint i, uint j, address funder) public view returns(bool){
        return CrowdFunding(fundings[i]).getUseVote(j, funder);
    }
}