#ifndef READERLIST
#define READERLIST
#include"reader.h"
class Readerlist{
	int size;
	Reader* ptr;

public:
	Readerlist():ptr(0),size(0){}
	void readerstringremove(string str);//�Ƴ�
	void add(Reader& a);//�����Ϣ��������
	void load(Reader& a,Booklist& booklist);//����
	void display();
	Reader* find(Reader& a);//����
	void write();//д���ļ�
	void newadd();
	Reader* yanzhenfind(Reader& a);
	~Readerlist();
};
#endif