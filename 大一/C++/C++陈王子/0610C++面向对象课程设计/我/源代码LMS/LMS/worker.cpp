#include"worker.h"
//修改工作人员姓名
void Worker::gname()
{   
	string na;
	cout<<"输入修改后的姓名："<<endl;
	cin>>na;
	mpeople(na);
}
//修改密码
void Worker::gpass()
{
	string p;
	cout<<"输入修改后的密码：";
	cin>>p;
	pass=p;
}


void Worker::workerdisplay()
{
	cout<<"账号："<<no<<"  姓名："<<name<<endl;
}


bool Worker::ifworkernofull()
{
	return (no=="null");
}


void Worker::setworkerinfomation()
{
	cout<<"请输入工作人员的下列信息"<<endl;
	cout<<"姓名  "<<"密码  "<<endl;
	cin>>name>>pass;
	cout<<"修改成功"<<endl;
}