#include"readerlist.h"
#include<fstream>
//查找读者信息
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
//登陆读者账户
void Readerlist::load(Reader& a,Booklist& booklist){


	 if(yanzhenfind(a))
	 {
		 Reader *z;
		 z=find(a);
		 cout<<"登陆成功"<<endl;
		 int n=0,fh=0;
		 while(n!=-1)
		 {   
			 n=0;
			 fh=0;
			 cout<<"1.显示个人信息"<<endl;
			 cout<<"2.修改密码"<<endl;
			 cout<<"3.修改名字"<<endl;
			 cout<<"请选择（1/2/3,输入-1返回上层结构）："<<endl;
			 cin>>n;
			 switch(n)
			 {
			 case 1:
				 while(fh!=-1)
				 {
					 z->readerdisplay(booklist);
					 cout<<"输入任意数字返回"<<endl;
					 cin>>fh;
                     fh=-1;
				 }
					 break;
		     case 2:
				  while(fh!=-1)
				 {
					  z->gpass();
				      cout<<"修改后的密码为："<<z->getrpass()<<endl;
				      write();
					  cout<<"输入任意数字返回"<<endl;
					  cin>>fh;
                      fh=-1;
				  }
			 break;
		 case 3:
			 while(fh!=-1)
			 {
				 z->gname();
			     cout<<"修改后的名字为："<<z->getrname()<<endl;
			     write();
				 cout<<"输入任意数字返回"<<endl;
			     cin>>fh;
                 fh=-1;
			 }
			 break;
		}
	 }
	 }
	 else
	 {
		 cout<<"密码或账号输入错误"<<endl;
	 }
}    
//添加信息到链表
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
//从链表中移除信息
void Readerlist::readerstringremove(string str)
{
    Reader reader(str);
	if(Reader* rz=find(reader)){
		rz->readersetnull();
	}

	
}
//输出
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
	cout<<"请输入读者的以下信息"<<endl;
	cout<<"账号  "<<"姓名  "<<"账户密码  "<<endl;
	cin>>linno>>linname>>linpass;
    Reader linreader(linno);
	if(find(linreader)){
		cout<<"该账号已被注册"<<endl;
	}
	else{
		Reader linreader1(linno,linname,linpass);
		add(linreader1);
		cout<<"注册成功"<<endl;
	}
}
Readerlist::~Readerlist()
{
	for(Reader* r=ptr;r=ptr;delete r){
		ptr=ptr->next;
	}
}
	
