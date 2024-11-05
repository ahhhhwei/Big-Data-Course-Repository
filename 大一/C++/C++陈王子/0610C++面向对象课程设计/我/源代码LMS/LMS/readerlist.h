#ifndef READERLIST
#define READERLIST
#include"reader.h"
class Readerlist{
	int size;
	Reader* ptr;

public:
	Readerlist():ptr(0),size(0){}
	void readerstringremove(string str);//移除
	void add(Reader& a);//添加信息到链表中
	void load(Reader& a,Booklist& booklist);//登入
	void display();
	Reader* find(Reader& a);//查找
	void write();//写入文件
	void newadd();
	Reader* yanzhenfind(Reader& a);
	~Readerlist();
};
#endif