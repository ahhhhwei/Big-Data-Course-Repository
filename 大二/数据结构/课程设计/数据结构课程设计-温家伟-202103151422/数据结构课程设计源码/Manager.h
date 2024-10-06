#pragma once
#include "Bignum.hpp"
#include <string>
#include <vector>
#include "Vector.hpp"
#include <fstream>
#include <iostream>

struct Expression					// 表达式结构体
{
	Bignum<List<int>> _left;		// 左操作数
	Bignum<List<int>> _right;		// 右操作数
	Bignum<List<int>> _result;		// 结果
	char _sign;						// 操作符
};
class Manager
{
public:
	bool read(const std::string& fileName);									// 读取文件到数据
	void write(const std::string& fileName, string wstr) const;				// 写入数据到文件
	void addBignum(const Expression& bignum);								// 添加大整数
	const Expression& getBignums(const int& index) const;					// 获取大整数数据
	void setBignum(const int& index, const Expression& bignum);				// 修改大整数
	void deleteBignum(const int& index);									// 删除大整数
	const size_t size() const;												// 大整数数量
	Bignum<List<int>> string2Bignum(string str);							// string转大整数
private:
	vector<Expression> _bignums;											// 大整数数组
};