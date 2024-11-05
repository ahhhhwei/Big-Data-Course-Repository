#ifndef READER
#define READER
#include"people.h"
#include"book.h"
#include"booklist.h"
class Reader:public People,public Book,public Booklist{
    string pass;
public:
	string albno[8];
    Reader(string no="null",string name="null",string p="123456"):People(name,no),pass(p){
		int i;
		for(i=0;i<=7;i++){
			albno[i]="null";
		}
		
	}
	Reader *next;
	Reader* getnext()const{return next;}
	void gpass();//修改密码
	void gname();//修改改名字
	string getrname(){return name;}//获得名字
    string getrpass(){return pass;}//获得密码
	void setalbno(string s1,string s2,string s3,string s4,string s5,string s6,string s7,string s8);//设置已借的书的书号
    void getalbno(string* al);//获得已借的书的书号
	bool operator==(const Reader& m){return(pass==m.pass&&no==m.no);}
    string getrrepass(){string repass;repass=pass;return repass;}//获得修改后的密码
	void readerdisplay(Booklist& rebooklist);//显示读者信息
	int alreadyborrownum();//获得已借书的数量
	int canalbnonum();//获得可借书的数组的序号
	void setsinglealbno(int i,string str);
	void returnreaderbook(string str);//还书时清除账户关于该书的记录
	bool alreadyborrow(string str);//是否借过该书
	void readersetnull(){no="null";}
	bool ifreadernofull();
	void setreaderinfomation();
	Reader setreader(string account,string password)
{
	return Reader(account,"null",password);
};
};
#endif