#include"worker.h"
//�޸Ĺ�����Ա����
void Worker::gname()
{   
	string na;
	cout<<"�����޸ĺ��������"<<endl;
	cin>>na;
	mpeople(na);
}
//�޸�����
void Worker::gpass()
{
	string p;
	cout<<"�����޸ĺ�����룺";
	cin>>p;
	pass=p;
}


void Worker::workerdisplay()
{
	cout<<"�˺ţ�"<<no<<"  ������"<<name<<endl;
}


bool Worker::ifworkernofull()
{
	return (no=="null");
}


void Worker::setworkerinfomation()
{
	cout<<"�����빤����Ա��������Ϣ"<<endl;
	cout<<"����  "<<"����  "<<endl;
	cin>>name>>pass;
	cout<<"�޸ĳɹ�"<<endl;
}