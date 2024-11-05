#ifndef MANAGERLIST
#define MANAGERLIST
#include"manager.h"
#include"workerlist.h"
class Managerlist{
	int size;
	Manager* ptr;

public:
	Managerlist():ptr(0),size(0){}
	void remove(string rmv);//移除
	void add(Manager& a);//添加信息到链表中
	void load(Manager& a,Booklist& booklist,Readerlist& readerlist,Workerlist& workerlist);//登陆
	void display();
	Manager* find(Manager& a);//查找
	void write();//写入文件
	Manager* yanzhenfind(Manager& a);
	~Managerlist();
};
#endif