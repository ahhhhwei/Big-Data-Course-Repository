#include "friend_test.h"
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