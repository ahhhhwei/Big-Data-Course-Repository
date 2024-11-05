#ifndef WORKERLIST
#define WORKERLIST
#include"worker.h"
class Workerlist{
	int size;
	Worker* ptr;

public:
	Workerlist():ptr(0),size(0){}
	void remove(string rmv);//移除
	void add(Worker& a);//添加信息到链表中
	void load(Worker& a,Booklist& booklist,Readerlist& readerlist);//登陆
	void workerlistdisplay();
	Worker* find(Worker& a);//查找
	void write();//写入文件
	void newadd();
	Worker* yanzhenfind(Worker& a);
	~Workerlist();

};
#endif