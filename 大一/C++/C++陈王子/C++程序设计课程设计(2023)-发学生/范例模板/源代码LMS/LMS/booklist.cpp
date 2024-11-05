#include"booklist.h"
#include"book.h"
#include<fstream>
//����ͼ����Ϣ
void Booklist::find(int i){
	int n=0;
	string hao="null",ming="null";		
	Book a(hao,ming);
	switch(i){
	case 1:cout<<"��������ţ�";
		cin>>hao;
        a.setbno(hao);
		if(Book* linbook=allfind(a)){//����ҵ��û�������飬����һ��ָ��Book�ĵ�ָ�룬�����丳ֵ��ֵΪallfind�������ص�ָ��m
		linbook->bookdisplay();//���ͼ����Ϣ
		}
		else{
			cout<<"û���ҵ����ͼ����Ϣ"<<endl;
		}
		break;
	case 2:
		{ cout<<"������������";
		cin>>ming;
		for(Book* r=ptr;r;r=r->next){//ָ��r����next���ִ�Խ��������
			if(r->gbname()==ming){//���ı����ÿһ�������������������ƥ��һ��
				r->bookdisplay();
				n=1;
			}
		}
		if(n==0){
			cout<<"û���ҵ����ͼ����Ϣ"<<endl;
		}
		break;}
	default:
		cout<<"�������"<<endl;
		break;
	}
	
}
//������Ϣ��������
void Booklist::add(Book& a){
    Book* pn=new Book(a);
	if(ptr){//ptrָ��Ϊ��ʱ�����ײ�����
		pn->next=ptr;
	}
	if(!ptr){//���ָ�벻Ϊ�գ���β������
		pn->next=NULL;
	}
	ptr=pn;//��������һ����ʱָ���Ѿ���Ϊ��
}
//���������Ƴ���Ϣ

void Booklist::remove(Book& rea)
{
	ofstream out("book.txt");
	for(Book* r=ptr;r;r=r->next){
		if(*r==Book(rea)){
		
		}else{//���������
			out<<r->gbno()<<"    "<<r->gbname()<<"     "<<r->gauthor()<<"    "<<r->gpress()<<"   "<<r->gborrownum()<<"    "<<r->gstorenum()<<"    "<<r->gcanborrow()<<endl;//ˢ��һ��txt������
		}
	}
}
//��������
void Booklist::addbook(Book& a){
	add(a);
}

//���
void Booklist::booklistdisplay(){
	for(Book* pn=ptr;pn;pn=pn->next)
	{
		
		
			pn->bookdisplay();
		
	}
}
//д���ı�
void Booklist::write(){
	ofstream out("book.txt");
	for(Book* r=ptr;r!=NULL;r=r->next)
	{  
		if(!r->ifbnofull())//�����������
		{
			out<<r->gbno()<<"    "<<r->gbname()<<"     "<<r->gauthor()<<"     "<<r->gpress()<<"     "<<r->gstorenum()<<"     "<<
				r->gcanborrow()<<"     "<<r->gborrownum()<<endl;
		}
	}
}
//������Ϣ��ͼ�����
void Booklist::readerbookfind(string are){

	Book a(are);

	for(Book* m=ptr;m;m=m->next)
	{	
		if(*m==a){//���ָ������ĳ�ֵΪa
		   cout<<"��ţ�"<<m->gbno()<<"  "<<"������"<<m->gbname()<<"  "<<"���ߣ�"<<m->gauthor()<<"  "<<"�����磺"<<m->gpress()<<endl;

		
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
		bz->setnull();//��������ߣ����������Ƴ����
	}
}

void Booklist::advancedfind()//�߼�����
{
	int i=0,n=0;
	Book rea;
	string str;
	cout<<"1.�����߲���"<<endl<<"2.�����������"<<endl;
	cin>>i;
	switch(i){
	case 1:
		cout<<"����������������";
		cin>>str;
		break;
	case 2:
		cout<<"��������������ƣ�";
		cin>>str;
		break;
	default:
		cout<<"�������"<<endl;
	}
	if(i==1){
		rea.setauthor(str);//���������Ϣ������rea������
	}
	if(i==2){
		rea.setpress(str);
	}
	for(Book* m=ptr;m;m=m->next){
		if(m->gauthor()==rea.gauthor()||m->gpress()==rea.gpress()){//������ı��е���Ϣƥ��
			m->bookdisplay();
			n=1;
		}
	}
	if(n==0){
		cout<<"û���ҵ����ͼ��"<<endl;
	}
}
Booklist::~Booklist()
{
	for(Book* r=ptr;r=ptr;delete r){
		ptr=ptr->next;
	}
}

			

		
