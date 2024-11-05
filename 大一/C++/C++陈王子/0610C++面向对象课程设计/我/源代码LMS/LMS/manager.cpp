#include"manager.h"
//修改姓名
void Manager::gname()
{   
	string na;
	cout<<"请输入修改后的姓名："<<endl;
	cin>>na;
	mpeople(na);
}
//修改密码
void Manager::gpass()
{
	string p;
	cout<<"请输入修改后的密码：";
	cin>>p;
	pass=p;
}
void Manager::managerdisplay()
{
	cout<<"账号："<<no<<"  姓名："<<name<<"  密码："<<pass<<endl;
}
