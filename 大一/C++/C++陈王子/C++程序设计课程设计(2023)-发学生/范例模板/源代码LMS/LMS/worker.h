#ifndef WORKER
#define WORKER
#include"readerlist.h"
class Worker:public People{
private:
	string pass;//����
public:
	
	Worker(string no="null",string name="null",string p="123456"):People(name,no),pass(p){}
	Worker *next;
	Worker* getnext()const{return next;}
	void gpass();//�޸�����
	void gname();//�޸ĸ�����
	void bookinf();//ͼ����Ϣ
	bool operator==(const Worker& m){return(pass==m.pass&&no==m.no);}
    string getwpass(){return pass;}//����޸ĺ������
	void workerdisplay();//��ʾ������Ϣ
	void workersetfull(){no="null";}
    bool ifworkernofull();	
	void setworkerinfomation();
	Worker setwoker(string account,string password)
{
	return Worker(account,"null",password);
}

};
#endif