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
Clock::Clock(int h, int m, int s) //类clock的构造函数
{
	hour = h;
	minute = m;
	second = s;
}
void Clock::display(const Date& d) //display的作用是输出年、月、日和时、分、秒
{
	cout << d.month << "/" << d.day << "/" << d.year << endl; //引用Date类对象中的私有数据
	cout << hour << ":" << minute << ":" << second << endl; //引用本类对象中的私有数据
}
Date::Date(int m, int d, int y) //类Date的构造函数
{
	month = m;
	day = d;
	year = y;
}
int main()
{
	Clock t1(10, 13, 56); //定义Clock类对象t1
	Date d1(12, 25, 2004); //定义Date类对象d1
	t1.display(d1); //调用t1中的display函数，实参是Date类对象d1
	return 0;
}