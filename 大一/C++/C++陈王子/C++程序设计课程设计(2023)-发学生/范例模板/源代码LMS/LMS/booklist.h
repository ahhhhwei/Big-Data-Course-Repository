#ifndef BOOKLIST
#define BOOKLIST
#include"book.h"

class Booklist{
	int size;
	Book* ptr;

public:
	Booklist():ptr(0),size(0){}
	void remove(Book& rea);//移除
	void add(Book& a);//添加信息到链表中
    void booklistdisplay();
	void addbook(Book& a);//图书库增加新书
	void find(int i);//查找
	void write();//写入文件
	void readerbookfind(string are);//读者信息中图书查找
	Book* allfind(Book& finbook);
	void stringremove(string str);//依靠字符来移除信息
	void advancedfind();
	~Booklist();
};
#endif