#include"reader.h"
//修改读者姓名
void Reader::gname()
{   
	string na;
	cout<<"输入修改后的姓名："<<endl;
	cin>>na;
	name=na;
}
//修改密码
void Reader::gpass()
{
	string p;
	cout<<"输入修改后的密码：";
	cin>>p;
	pass=p;
}

void Reader::getalbno(string* al){
	int i=0;
	for(;i<=7;i++){
		al[i]=albno[i];
	}
}
void Reader::setalbno(string s1,string s2,string s3,string s4,string s5,string s6,string s7,string s8)
{
	albno[0]=s1;
	albno[1]=s2;
	albno[2]=s3;
	albno[3]=s4;
	albno[4]=s5;
	albno[5]=s6;
	albno[6]=s7;
	albno[7]=s8;
}
void Reader::readerdisplay(Booklist& rebooklist){
	cout<<"账号："<<no<<endl<<"姓名："<<name<<endl;
	int i;
	cout<<"已借图书："<<endl;
	
	for(i=0;i<=7;i++){
		if(albno[i]!="null")
		  rebooklist.readerbookfind(albno[i]);
	}
}
int Reader::alreadyborrownum()
{
	int n=0,i;
	for(i=0;i<=7;i++){
		if(albno[i]!="null"){
			n++;
		}
	}
	return n;
}
int Reader::canalbnonum()
{
	int i,n=0;
	for(i=0;i<=7;i++){
		if(albno[i]=="null"){
			n=i;
			break;
		}
	}
	return n;
}
void Reader::setsinglealbno(int i,string str)
{
	albno[i]=str;
}
void Reader::returnreaderbook(string str)
{
	int i;
	for(i=0;i<=7;i++){
		if(albno[i]==str){
			albno[i]="null";
			break;
		}
	}
}
bool Reader::alreadyborrow(string str)
{
	int i,n=0;
	for(i=0;i<=7;i++){
		if(albno[i]==str){
			n=1;
			break;
		}
	}
	return n;
}
bool Reader::ifreadernofull()
{
	return (no=="null");
}
void Reader::setreaderinfomation()
{

	cout<<"请输入读者的下列信息"<<endl;
	cout<<"姓名  "<<"密码  "<<endl;
	cin>>name>>pass;
	cout<<"修改成功"<<endl;
}
