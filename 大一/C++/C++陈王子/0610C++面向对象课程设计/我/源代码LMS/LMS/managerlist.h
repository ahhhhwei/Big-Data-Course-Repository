#ifndef MANAGERLIST
#define MANAGERLIST
#include"manager.h"
#include"workerlist.h"
class Managerlist{
	int size;
	Manager* ptr;

public:
	Managerlist():ptr(0),size(0){}
	void remove(string rmv);//�Ƴ�
	void add(Manager& a);//�����Ϣ��������
	void load(Manager& a,Booklist& booklist,Readerlist& readerlist,Workerlist& workerlist);//��½
	void display();
	Manager* find(Manager& a);//����
	void write();//д���ļ�
	Manager* yanzhenfind(Manager& a);
	~Managerlist();
};
#endif