//header2.h (ͷ�ļ�2�������ļ���Ϊexample2_header2.h)
#include <string>
#include <cmath>
using namespace std;
class Student//����Student��
{
public:
	Student(intn,stringnam,char s) //������header1�е�student��ͬ
	{
	num=n;name=nam;sex=s;
	}
	void get_data( );
private:
	int num;
	string name;
	char sex; //������header1��ͬ
};
void Student::get_data( ) //��Ա��������
{
	cout<<num<<" "<<name<<" "<<sex<<endl;
}
double fun(double a,double b) //����ȫ�ֺ���
{
	return sqrt(a-b);
} //����ֵ��header1�е�fun������ͬ

//ͷ�ļ�2�п��ܻ�����������