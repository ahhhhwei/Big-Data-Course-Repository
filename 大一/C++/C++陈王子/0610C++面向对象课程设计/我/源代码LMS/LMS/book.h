#ifndef BOOK
#define BOOK
#include<string>
#include<iostream>
using namespace std;
class Book{
private:
	string bno;//书号
	string bname;//书名
    string author;//作者
	string press;//出版社
	int storenum;//藏书量
	int borrownum;//借出数
	int canborrow;//可借数量
public:
	Book(string bno1="null",string bname1="null",string author1="null",string press1="null",int storenum1=0,int canborrow1=0,int borrownum1=0)
		:bno(bno1),bname(bname1),author(author1),press(press1),storenum(storenum1),canborrow(canborrow1),borrownum(borrownum1){}
	Book *next;
	Book* getnext()const{return next;}
	string gbno()const{return bno;}//获得书号
	string gbname()const{return bname;}//获得书名
	string gauthor()const{return author;}//获得作者
	string gpress()const{return press;}//获得出版社
	int gstorenum()const{return storenum;}//获得藏书量
	int gcanborrow()const{return canborrow;}//获得可借数量
	int gborrownum()const{return borrownum;}//获得借出数量
	bool operator==(const Book& m){return(bno==m.bno);}
	void bookdisplay();
	void storebook(){storenum++;canborrow++;}//存入该书
	void returnbook(){//还书
		canborrow++;
		borrownum--;
	}
	void borrowbook(){//借书
		canborrow--;
		borrownum++;
	}
	void setnull(){bno="null";}//将书号设置为null
	bool ifbnofull();//判断书号是否为null
    void setinformationg();//设置图书信息
	void setbno(string str){bno=str;}
	void setauthor(string str){author=str;}
	void setpress(string str){press=str;}
};
#endif