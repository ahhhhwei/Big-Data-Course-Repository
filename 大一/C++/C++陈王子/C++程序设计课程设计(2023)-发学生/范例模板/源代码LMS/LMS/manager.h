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
	void gpass();//�޸�����
	void gname();//�޸ĸ�����
	void bookinf();//ͼ����Ϣ
	bool operator==(const Manager& m){return(pass==m.pass&&no==m.no);}
	void managerdisplay();//��ʾ������Ϣ
    string getmpass(){return pass;}//����޸ĺ������
	Manager setmanager(string account,string password)
{
	return Manager(account,"null",password);
}

};
#endif