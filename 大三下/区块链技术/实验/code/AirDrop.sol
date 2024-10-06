// SPDX-License-Identifier: NIT
pragma solidity ^0.8.0;

contract AirDrop {
    address public owner;
    constructor() {
        owner = msg.sender;
    }
    // modifier 修饰符,是一种修改函数行为的特殊声明，如访问控制
    modifier onlyOwner() {
        require(msg.sender == owner, "only the owner can inwoke");
        _; //告知编译器内部，修饰符功能结束
    }
    // 仅允许合约拥有者将指定数量的ETH发送到一个特定地址
    // msg.value = 合约拥有者指定数量的ETH
    // function transferToAddress(address payable recipient) payable public {
    //     // require(msg.sender == owner, "only the owner can inwoke");
    //     recipient.transfer(msg.value);
    // }
    function transferToAddress(address payable recipient) payable public onlyOwner{
        recipient.transfer(msg.value);
    }

    // 仅允许合约拥有者将指定数量的ETH平均分配给特定的多个地址
    // memory 内存 storage 磁盘 calldata 内存（数组）
    function transferToMultiAddress(address payable[] calldata recipients) payable public onlyOwner{
        require(recipients.length > 0, "No recipients provided");
        // 均分后的金额 = 总金额 / 数组长度
        uint amount = msg.value / recipients.length;
        for (uint i = 0; i < recipients.length; i++) {
            recipients[i].transfer(amount);
        }
    }

    // 仅允许合约拥有者一次性给多个地址转ETH（指定金额）
    function transferToMultipleAddressesWithAmount(address payable[] calldata recipients, uint amount) payable public onlyOwner {
        require(recipients.length > 0, "No recipients provided");
        require(msg.value >= amount * recipients.length, "Insufficient funds");

        for (uint i = 0; i < recipients.length; i++) {
            recipients[i].transfer(amount);
        }
    }

    // 合约余额查询
    function getContractBalance() public view returns (uint) {
        return address(this).balance;
    }
}