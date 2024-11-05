#ifndef PEOPLE
#define PEOPLE
#include<iostream>
#include<string>
using namespace std;
class People{	


public:	
	string name;//姓名
	string no;//账号
	People(string na="null",string n="null"):name(na),no(n){}
	string mpeople(string a)//改名字
	{
	return name=a;
	};
	void display(){cout<<"姓名："<<name<<" "<<"  账号："<<no<<endl;}
};
#endif