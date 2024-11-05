#include <iostream>
using namespace std;
class Date; //��Date�����ǰ��������
class Clock //����clock��
{
public:
	Clock(int, int, int);
	void display(const Date&); //display�ǳ�Ա�������β���Date����������
private:
	int hour;
	int minute;
	int second;
};
class Date //����Date��
{
public:
	Date(int, int, int);
	friend void clock::display(const Date&); //����clock�е�display����Ϊ��Ԫ��Ա����
private:
	int month;
	int day;
	int year;
};
Clock::Clock(int h, int m, int s) //��clock�Ĺ��캯��
{
	hour = h;
	minute = m;
	second = s;
}
void Clock::display(const Date& d) //display������������ꡢ�¡��պ�ʱ���֡���
{
	cout << d.month << "/" << d.day << "/" << d.year << endl; //����Date������е�˽������
	cout << hour << ":" << minute << ":" << second << endl; //���ñ�������е�˽������
}
Date::Date(int m, int d, int y) //��Date�Ĺ��캯��
{
	month = m;
	day = d;
	year = y;
}
int main()
{
	Clock t1(10, 13, 56); //����Clock�����t1
	Date d1(12, 25, 2004); //����Date�����d1
	t1.display(d1); //����t1�е�display������ʵ����Date�����d1
	return 0;
}