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
	void gpass();//�޸�����
	void gname();//�޸ĸ�����
	string getrname(){return name;}//�������
    string getrpass(){return pass;}//�������
	void setalbno(string s1,string s2,string s3,string s4,string s5,string s6,string s7,string s8);//�����ѽ��������
    void getalbno(string* al);//����ѽ��������
	bool operator==(const Reader& m){return(pass==m.pass&&no==m.no);}
    string getrrepass(){string repass;repass=pass;return repass;}//����޸ĺ������
	void readerdisplay(Booklist& rebooklist);//��ʾ������Ϣ
	int alreadyborrownum();//����ѽ��������
	int canalbnonum();//��ÿɽ������������
	void setsinglealbno(int i,string str);
	void returnreaderbook(string str);//����ʱ����˻����ڸ���ļ�¼
	bool alreadyborrow(string str);//�Ƿ�������
	void readersetnull(){no="null";}
	bool ifreadernofull();
	void setreaderinfomation();
	Reader setreader(string account,string password)
{
	return Reader(account,"null",password);
};
};
#endif