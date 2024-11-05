#ifndef WORKER
#define WORKER
#include"readerlist.h"
class Worker:public People{
private:
	string pass;//密码
public:
	
	Worker(string no="null",string name="null",string p="123456"):People(name,no),pass(p){}
	Worker *next;
	Worker* getnext()const{return next;}
	void gpass();//修改密码
	void gname();//修改改名字
	void bookinf();//图书信息
	bool operator==(const Worker& m){return(pass==m.pass&&no==m.no);}
    string getwpass(){return pass;}//获得修改后的密码
	void workerdisplay();//显示个人信息
	void workersetfull(){no="null";}
    bool ifworkernofull();	
	void setworkerinfomation();
	Worker setwoker(string account,string password)
{
	return Worker(account,"null",password);
}

};
#endif