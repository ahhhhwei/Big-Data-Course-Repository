#ifndef MANAGER
#define MANAGER
#include"reader.h"
#include"worker.h"
#include"book.h"
class Manager:public People{
private:
	string pass;
public:
	
	Manager(string no="null",string name="null",string p="123456"):People(name,no),pass(p){}
	Manager* next;
	Manager* getnext()const{return next;}
	void gpass();//修改密码
	void gname();//修改改名字
	void bookinf();//图书信息
	bool operator==(const Manager& m){return(pass==m.pass&&no==m.no);}
	void managerdisplay();//显示个人信息
    string getmpass(){return pass;}//获得修改后的密码
	Manager setmanager(string account,string password)
{
	return Manager(account,"null",password);
}

};
#endif