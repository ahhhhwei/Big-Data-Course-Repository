//header1.h (ͷ�ļ�1�������ļ���Ϊexample2.h)
#include <string>
#include <cmath>
using namespace std;
class Student//����Student��
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
void Student::get_data( ) //��Ա��������
{
	cout<<num<<""<<name<<""<<sex<<endl;
}
double fun(double a,double b) //����ȫ�ֺ���(���ⲿ����)
{
	return sqrt(a+b);
}