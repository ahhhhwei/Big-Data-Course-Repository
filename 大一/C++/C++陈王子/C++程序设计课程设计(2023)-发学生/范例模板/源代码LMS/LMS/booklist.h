#ifndef BOOKLIST
#define BOOKLIST
#include"book.h"

class Booklist{
	int size;
	Book* ptr;

public:
	Booklist():ptr(0),size(0){}
	void remove(Book& rea);//�Ƴ�
	void add(Book& a);//�����Ϣ��������
    void booklistdisplay();
	void addbook(Book& a);//ͼ�����������
	void find(int i);//����
	void write();//д���ļ�
	void readerbookfind(string are);//������Ϣ��ͼ�����
	Book* allfind(Book& finbook);
	void stringremove(string str);//�����ַ����Ƴ���Ϣ
	void advancedfind();
	~Booklist();
};
#endif