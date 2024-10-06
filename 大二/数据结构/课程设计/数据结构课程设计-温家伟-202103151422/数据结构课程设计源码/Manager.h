#pragma once
#include "Bignum.hpp"
#include <string>
#include <vector>
#include "Vector.hpp"
#include <fstream>
#include <iostream>

struct Expression					// ���ʽ�ṹ��
{
	Bignum<List<int>> _left;		// �������
	Bignum<List<int>> _right;		// �Ҳ�����
	Bignum<List<int>> _result;		// ���
	char _sign;						// ������
};
class Manager
{
public:
	bool read(const std::string& fileName);									// ��ȡ�ļ�������
	void write(const std::string& fileName, string wstr) const;				// д�����ݵ��ļ�
	void addBignum(const Expression& bignum);								// ��Ӵ�����
	const Expression& getBignums(const int& index) const;					// ��ȡ����������
	void setBignum(const int& index, const Expression& bignum);				// �޸Ĵ�����
	void deleteBignum(const int& index);									// ɾ��������
	const size_t size() const;												// ����������
	Bignum<List<int>> string2Bignum(string str);							// stringת������
private:
	vector<Expression> _bignums;											// ����������
};