#include <iostream>
using namespace std;
class Date
{
public:
    int month;   
    int day;     
    int year;    
    Date(int m, int d, int y);
};
class Clock
{
public:
    Clock(int h, int m, int s);
    void display(Date&);
private:
    int hour;
    int minute;
    int second;
};
Clock::Clock(int h, int m, int s)
{
    hour = h;
    minute = m;
    second = s;
}
void Clock::display(Date& d)
{
    cout << d.month << "/" << d.day << "/" << d.year << endl;
    cout << hour << ":" << minute << ":" << second << endl;
}
Date::Date(int m, int d, int y)
{
    month = m;
    day = d;
    year = y;
}
int main()
{
    Clock t1(10, 13, 56);
    Date d1(12, 25, 2004);
    t1.display(d1);
    return 0;
}

class Clock
{
public:
    Clock(int h, int m, int s);
    friend void display(Date&, Clock&);
private:
    int hour;
    int minute;
    int second;
};
void display(Date& d, Clock& c)
{
    cout << d.month << "/" << d.day << "/" << d.year << endl;
    cout << c.hour << ":" << c.minute << ":" << c.second << endl;
}


#include <iostream>
using namespace std;
class Date
{
public:
	Date(int m, int d, int y);
	int get_month() const { return month; } //添加读取私有数据的公有接口
	int get_day() const { return day; }
	int get_year() const { return year; }
private:
	int month;
	int day;
	int year;
};
class Clock
{
public:
	Clock(int h, int m, int s);
	void display(const Date&);
private:
	int hour;
	int minute;
	int second;
};
Clock::Clock(int h, int m, int s)
{
	hour = h;
	minute = m;
	second = s;
}
void Clock::display(const Date& d)
{
	cout << d.get_month() << "/" << d.get_day() << "/" << d.get_year() << endl;
	cout << hour << ":" << minute << ":" << second << endl;
}
Date::Date(int m, int d, int y)
{
	month = m;
	day = d;
	year = y;
}
int main()
{
	Clock t1(10, 13, 56);
	Date d1(12, 25, 2004);
	t1.display(d1);
	return 0;
}