#include"manager.h"
//�޸�����
void Manager::gname()
{   
	string na;
	cout<<"�������޸ĺ��������"<<endl;
	cin>>na;
	mpeople(na);
}
//�޸�����
void Manager::gpass()
{
	string p;
	cout<<"�������޸ĺ�����룺";
	cin>>p;
	pass=p;
}
void Manager::managerdisplay()
{
	cout<<"�˺ţ�"<<no<<"  ������"<<name<<"  ���룺"<<pass<<endl;
}
