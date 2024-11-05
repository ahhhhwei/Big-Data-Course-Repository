#include"booklist.h"
#include"book.h"
#include<fstream>
//查找图书信息
void Booklist::find(int i){
	int n=0;
	string hao="null",ming="null";		
	Book a(hao,ming);
	switch(i){
	case 1:cout<<"请输入书号：";
		cin>>hao;
        a.setbno(hao);
		if(Book* linbook=allfind(a)){//如果找到用户输入的书，声明一个指向Book的的指针，并对其赋值，值为allfind函数返回的指针m
		linbook->bookdisplay();//输出图书信息
		}
		else{
			cout<<"没有找到相关图书信息"<<endl;
		}
		break;
	case 2:
		{ cout<<"请输入书名：";
		cin>>ming;
		for(Book* r=ptr;r;r=r->next){//指针r沿着next部分穿越整个链表
			if(r->gbname()==ming){//将文本里的每一个书名都与输入的名字匹配一遍
				r->bookdisplay();
				n=1;
			}
		}
		if(n==0){
			cout<<"没有找到相关图书信息"<<endl;
		}
		break;}
	default:
		cout<<"输入错误"<<endl;
		break;
	}
	
}
//加入信息到链表中
void Booklist::add(Book& a){
    Book* pn=new Book(a);
	if(ptr){//ptr指针为空时，在首部插入
		pn->next=ptr;
	}
	if(!ptr){//如果指针不为空，在尾部插入
		pn->next=NULL;
	}
	ptr=pn;//当继续下一本书时指针已经不为空
}
//从链表中移除信息

void Booklist::remove(Book& rea)
{
	ofstream out("book.txt");
	for(Book* r=ptr;r;r=r->next){
		if(*r==Book(rea)){
		
		}else{//如果被借走
			out<<r->gbno()<<"    "<<r->gbname()<<"     "<<r->gauthor()<<"    "<<r->gpress()<<"   "<<r->gborrownum()<<"    "<<r->gstorenum()<<"    "<<r->gcanborrow()<<endl;//刷新一行txt的数据
		}
	}
}
//增加新书
void Booklist::addbook(Book& a){
	add(a);
}

//输出
void Booklist::booklistdisplay(){
	for(Book* pn=ptr;pn;pn=pn->next)
	{
		
		
			pn->bookdisplay();
		
	}
}
//写入文本
void Booklist::write(){
	ofstream out("book.txt");
	for(Book* r=ptr;r!=NULL;r=r->next)
	{  
		if(!r->ifbnofull())//如果有这个书号
		{
			out<<r->gbno()<<"    "<<r->gbname()<<"     "<<r->gauthor()<<"     "<<r->gpress()<<"     "<<r->gstorenum()<<"     "<<
				r->gcanborrow()<<"     "<<r->gborrownum()<<endl;
		}
	}
}
//读者信息中图书查找
void Booklist::readerbookfind(string are){

	Book a(are);

	for(Book* m=ptr;m;m=m->next)
	{	
		if(*m==a){//如果指针变量的初值为a
		   cout<<"书号："<<m->gbno()<<"  "<<"书名："<<m->gbname()<<"  "<<"作者："<<m->gauthor()<<"  "<<"出版社："<<m->gpress()<<endl;

		
		}
	}
	
}
Book* Booklist::allfind(Book& finbook)
{	
	for(Book* m=ptr;m;m=m->next)
	{
		if(*m==finbook){

			return  m;
		}
	}
}
void Booklist::stringremove(string str)
{
	Book book(str);
	if(Book* bz=allfind(book)){
		bz->setnull();//如果被借走，在链表中移除书号
	}
}

void Booklist::advancedfind()//高级查找
{
	int i=0,n=0;
	Book rea;
	string str;
	cout<<"1.按作者查找"<<endl<<"2.按出版社查找"<<endl;
	cin>>i;
	switch(i){
	case 1:
		cout<<"请输入作者姓名：";
		cin>>str;
		break;
	case 2:
		cout<<"请输入出版社名称：";
		cin>>str;
		break;
	default:
		cout<<"输入错误"<<endl;
	}
	if(i==1){
		rea.setauthor(str);//将输入的信息关联到rea对象中
	}
	if(i==2){
		rea.setpress(str);
	}
	for(Book* m=ptr;m;m=m->next){
		if(m->gauthor()==rea.gauthor()||m->gpress()==rea.gpress()){//如果与文本中的信息匹配
			m->bookdisplay();
			n=1;
		}
	}
	if(n==0){
		cout<<"没有找到相关图书"<<endl;
	}
}
Booklist::~Booklist()
{
	for(Book* r=ptr;r=ptr;delete r){
		ptr=ptr->next;
	}
}

			

		
