#ifndef PEOPLE
#define PEOPLE
#include<iostream>
#include<string>
using namespace std;
class People{	


public:	
	string name;//����
	string no;//�˺�
	People(string na="null",string n="null"):name(na),no(n){}
	string mpeople(string a)//������
	{
	return name=a;
	};
	void display(){cout<<"������"<<name<<" "<<"  �˺ţ�"<<no<<endl;}
};
#endif