#ifndef WORKERLIST
#define WORKERLIST
#include"worker.h"
class Workerlist{
	int size;
	Worker* ptr;

public:
	Workerlist():ptr(0),size(0){}
	void remove(string rmv);//�Ƴ�
	void add(Worker& a);//�����Ϣ��������
	void load(Worker& a,Booklist& booklist,Readerlist& readerlist);//��½
	void workerlistdisplay();
	Worker* find(Worker& a);//����
	void write();//д���ļ�
	void newadd();
	Worker* yanzhenfind(Worker& a);
	~Workerlist();

};
#endif