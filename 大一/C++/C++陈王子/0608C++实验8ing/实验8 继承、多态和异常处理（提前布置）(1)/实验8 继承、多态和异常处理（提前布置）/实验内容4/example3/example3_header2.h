//header2.h (头文件2，设其文件名为example2_header2.h)
#include <string>
#include <cmath>
using namespace std;
class Student//声明Student类
{
public:
	Student(intn,stringnam,char s) //参数与header1中的student不同
	{
	num=n;name=nam;sex=s;
	}
	void get_data( );
private:
	int num;
	string name;
	char sex; //此项与header1不同
};
void Student::get_data( ) //成员函数定义
{
	cout<<num<<" "<<name<<" "<<sex<<endl;
}
double fun(double a,double b) //定义全局函数
{
	return sqrt(a-b);
} //返回值与header1中的fun函数不同

//头文件2中可能还有其他内容