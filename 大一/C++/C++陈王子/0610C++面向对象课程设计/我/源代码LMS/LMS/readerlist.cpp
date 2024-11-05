#include"readerlist.h"
#include<fstream>
//���Ҷ�����Ϣ
Reader* Readerlist::find(Reader& a){
	for(Reader* m=ptr;m;m=m->next)
	{
		if(m->no==a.no){
			return  m;
		}
	}
}
Reader* Readerlist::yanzhenfind(Reader& a){
	for(Reader* m=ptr;m;m=m->next)
	{
		if(*m==a){
			return m;
		}
	}
}
//��½�����˻�
void Readerlist::load(Reader& a,Booklist& booklist){


	 if(yanzhenfind(a))
	 {
		 Reader *z;
		 z=find(a);
		 cout<<"��½�ɹ�"<<endl;
		 int n=0,fh=0;
		 while(n!=-1)
		 {   
			 n=0;
			 fh=0;
			 cout<<"1.��ʾ������Ϣ"<<endl;
			 cout<<"2.�޸�����"<<endl;
			 cout<<"3.�޸�����"<<endl;
			 cout<<"��ѡ��1/2/3,����-1�����ϲ�ṹ����"<<endl;
			 cin>>n;
			 switch(n)
			 {
			 case 1:
				 while(fh!=-1)
				 {
					 z->readerdisplay(booklist);
					 cout<<"�����������ַ���"<<endl;
					 cin>>fh;
                     fh=-1;
				 }
					 break;
		     case 2:
				  while(fh!=-1)
				 {
					  z->gpass();
				      cout<<"�޸ĺ������Ϊ��"<<z->getrpass()<<endl;
				      write();
					  cout<<"�����������ַ���"<<endl;
					  cin>>fh;
                      fh=-1;
				  }
			 break;
		 case 3:
			 while(fh!=-1)
			 {
				 z->gname();
			     cout<<"�޸ĺ������Ϊ��"<<z->getrname()<<endl;
			     write();
				 cout<<"�����������ַ���"<<endl;
			     cin>>fh;
                 fh=-1;
			 }
			 break;
		}
	 }
	 }
	 else
	 {
		 cout<<"������˺��������"<<endl;
	 }
}    
//�����Ϣ������
void Readerlist::add(Reader& a){
    Reader* pn=new Reader(a);
	if(ptr){
		pn->next=ptr;
	}
	if(!ptr){
		pn->next=NULL;
	}
	ptr=pn;
}
//���������Ƴ���Ϣ
void Readerlist::readerstringremove(string str)
{
    Reader reader(str);
	if(Reader* rz=find(reader)){
		rz->readersetnull();
	}

	
}
//���
void Readerlist::display(){
	for(Reader* pn=ptr;pn;pn=pn->next)
	{
		pn->display();
	}
}

void Readerlist::write(){
	ofstream out("reader.txt");

	
	for(Reader* r=ptr;r!=NULL;r=r->next){  
		if(!r->ifreadernofull()){
		    out<<r->no<<"  "<<r->name<<"  "<<r->getrpass()<<"  "<<r->albno[0]<<"  "<<r->albno[1]<<"  "<<r->albno[2]<<"  "<<r->albno[3]<<"  "<<r->albno[4]<<"  "<<r->albno[5]<<"  "<<r->albno[6]<<"  "<<r->albno[7]<<endl;
        }
	}
	
}
void Readerlist::newadd()
{
	string linno,linname,linpass;
	cout<<"��������ߵ�������Ϣ"<<endl;
	cout<<"�˺�  "<<"����  "<<"�˻�����  "<<endl;
	cin>>linno>>linname>>linpass;
    Reader linreader(linno);
	if(find(linreader)){
		cout<<"���˺��ѱ�ע��"<<endl;
	}
	else{
		Reader linreader1(linno,linname,linpass);
		add(linreader1);
		cout<<"ע��ɹ�"<<endl;
	}
}
Readerlist::~Readerlist()
{
	for(Reader* r=ptr;r=ptr;delete r){
		ptr=ptr->next;
	}
}
	
