// SPDX-License-Identifier: MIT 
/*允许别人在github上看*/
pragma solidity^0.8.0;

contract money {
    address public owner;
    constructor() {
        //定义一个构造函数，初始值为合约部署者的地址
        owner = msg.sender;
    }
    // 0.6.0 以上支持这个函数,function可省略
    // external 外部所有人都可以调用这个函数 public private internal
    // payable 表明这个函数可以用来接收以太币
    receive() external payable { 
        emit Received(msg.sender, msg.value);
    }

    // 允许合约创建者从合约中取钱
    function withdraw() public {
        // require 相当于if
        require(msg.sender == owner, "only the owner can withdraw!");
        payable(msg.sender).transfer(address(this).balance);
    }
    // view 只用来访问，不能修改
    function getBalance() public view returns (uint256) {
        return address(this).balance;
    }
}
