#include <iostream>
using namespace std;
class Date; //对Date类的提前引用声明
class Clock //定义clock类
{
public:
	Clock(int, int, int);
	void display(const Date&); //display是成员函数，形参是Date类对象的引用
private:
	int hour;
	int minute;
	int second;
};
class Date //声明Date类
{
public:
	Date(int, int, int);
	friend void clock::display(const Date&); //声明clock中的display函数为友元成员函数
private:
	int month;
	int day;
	int year;
};