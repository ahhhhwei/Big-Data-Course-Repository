#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <assert.h>
#include<iostream>
#include <graphics.h>
#include <conio.h>
#include <fstream>
#define N 26
using namespace std;

class CMsg
{
public:
	size_t num;
	char  name[10];
	char  kind[10];
	size_t Coursehour;
	size_t credit;
	size_t studentNum;
	size_t semester;
	bool operator==(CMsg& right);
};
class SListNode
{
public:
	CMsg data;
	struct SListNode* next;
	// �������ӡ
	void SListPrint(SListNode* plist, int h = 0);
	//�����γ�����
	SListNode* createSListCourse();
	//��ѧ������
	void sortByCredit(SListNode** plist);
	//����������
	void sortByStuNum(SListNode** plist);
};