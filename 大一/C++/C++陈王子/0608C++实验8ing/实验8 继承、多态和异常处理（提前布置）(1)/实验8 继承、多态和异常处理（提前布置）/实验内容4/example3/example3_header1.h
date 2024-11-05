//header1.h (头文件1，设其文件名为example2.h)
#include <string>
#include <cmath>
using namespace std;
class Student//声明Student类
{
public:
	Student(int n,string nam,char s)
	{num=n;name=nam;sex=s;}
	void get_data( );
private:
	int num;
	string name;
	char sex;
};
void Student::get_data( ) //成员函数定义
{
	cout<<num<<""<<name<<""<<sex<<endl;
}
double fun(double a,double b) //定义全局函数(即外部函数)
{
	return sqrt(a+b);
}