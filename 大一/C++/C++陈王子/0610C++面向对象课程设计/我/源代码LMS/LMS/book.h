#ifndef BOOK
#define BOOK
#include<string>
#include<iostream>
using namespace std;
class Book{
private:
	string bno;//���
	string bname;//����
    string author;//����
	string press;//������
	int storenum;//������
	int borrownum;//�����
	int canborrow;//�ɽ�����
public:
	Book(string bno1="null",string bname1="null",string author1="null",string press1="null",int storenum1=0,int canborrow1=0,int borrownum1=0)
		:bno(bno1),bname(bname1),author(author1),press(press1),storenum(storenum1),canborrow(canborrow1),borrownum(borrownum1){}
	Book *next;
	Book* getnext()const{return next;}
	string gbno()const{return bno;}//������
	string gbname()const{return bname;}//�������
	string gauthor()const{return author;}//�������
	string gpress()const{return press;}//��ó�����
	int gstorenum()const{return storenum;}//��ò�����
	int gcanborrow()const{return canborrow;}//��ÿɽ�����
	int gborrownum()const{return borrownum;}//��ý������
	bool operator==(const Book& m){return(bno==m.bno);}
	void bookdisplay();
	void storebook(){storenum++;canborrow++;}//�������
	void returnbook(){//����
		canborrow++;
		borrownum--;
	}
	void borrowbook(){//����
		canborrow--;
		borrownum++;
	}
	void setnull(){bno="null";}//���������Ϊnull
	bool ifbnofull();//�ж�����Ƿ�Ϊnull
    void setinformationg();//����ͼ����Ϣ
	void setbno(string str){bno=str;}
	void setauthor(string str){author=str;}
	void setpress(string str){press=str;}
};
#endif