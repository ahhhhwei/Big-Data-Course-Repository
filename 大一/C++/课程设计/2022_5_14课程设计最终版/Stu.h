#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <assert.h>
#include<iostream>
#include <graphics.h>
#include <conio.h>
#include <fstream>
#define N 26
using namespace std;
class Student
{
public:
	char num[10];
	char name[10];
	char password[10];
	char _course[100];
	bool operator==(Student& right);
};
class StudentNode
{
public:
	Student data;
	struct StudentNode* next;
	// 单链表打印
	void StudentPrint(StudentNode* plist, int h = 0);
	//创建学生链表
	StudentNode* createStudent();
};