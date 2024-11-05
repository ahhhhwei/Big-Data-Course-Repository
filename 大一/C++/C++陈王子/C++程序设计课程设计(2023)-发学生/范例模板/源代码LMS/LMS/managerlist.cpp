#include"managerlist.h"
#include<fstream>
//查找管理员信息
Manager* Managerlist::find(Manager& a){
	for(Manager* m=ptr;m;m=m->next)
	{
		if(m->no==a.no){
			return  m;
		}
	}
}
Manager* Managerlist::yanzhenfind(Manager& a){
	for(Manager* m=ptr;m;m=m->next)
	{
		if(*m==a){
			return m;
		}
	}
}
//登陆管理员账户
void Managerlist::load(Manager& a,Booklist& booklist,Readerlist& readerlist,Workerlist& workerlist){
     string readern="null",xuhao="000";
	 int fh=0;
	 if(yanzhenfind(a))
	 {
		 Manager *z;
		 Book linbook;
		 Reader linreader;
		 Worker linworker;
		 z=find(a);
		 cout<<"登陆成功"<<endl;		 
		 int n=0,n4=0;
		 while(n!=-1)
		 {  
			 n4=0;
			 z->display();
			 cout<<"1.显示个人信息"<<endl;
			 cout<<"2.修改密码"<<endl;
			 cout<<"3.修改名字"<<endl;
			 cout<<"4.维护图书信息"<<endl;
			 cout<<"5.维护读者信息"<<endl;
			 cout<<"6.维护工作人员信息"<<endl;
			 cout<<"请选择（输入-1返回上层结构）："<<endl;
			 cin>>n;
			 fh=0;
		     switch(n)
			 {
			 case 1:
				while(fh!=-1)
				{
				  z->managerdisplay();
				  cout<<"输入任意数字返回"<<endl;
				  cin>>fh;
				  fh=-1;
				}
				 break;
		     case 2:
				 while(fh!=-1)
				 {
					 z->gpass();
			         cout<<"修改后的密码为："<<z->getmpass()<<endl;
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
				     write();
			         cout<<"修改后的姓名为："<<z->name<<endl;
					 cout<<"输入任意数字返回"<<endl;
				     cin>>fh;
				     fh=-1;
				 }
			     break;
			 }
	    	if(n==4){
				while(n4!=-1)
				{   fh=0;
				    cout<<"1.添加图书"<<endl;
					cout<<"2.删除图书"<<endl;
					cout<<"3.修改图书信息"<<endl;
					cout<<"请选择（1/2/3，输入-1返回上层结构）：";
					cin>>n4;
					switch(n4){
			        case 1:
						while(fh!=-1)
						{
							cout<<"请输入新存入的书的书号：";					 
							cin>>xuhao;					 
						    linbook.setbno(xuhao);		 
							if(Book* bz=booklist.allfind(linbook)){			 				 
								bz->storebook();
								cout<<"已存入"<<endl;
							}					 
				            else{			 				
								string linname,linauthor,linpress;			 				 
					            int linnum;							
					            cout<<"请输该书下列信息"<<endl;							
					            cout<<"书名"<<"  "<<"作者"<<"  "<<"出版社"<<"  "<<"存入数量"<<endl;							 
					            cin>>linname>>linauthor>>linpress>>linnum;							
					            Book cunbook(xuhao,linname,linauthor,linpress,linnum,linnum,0);			 				 
					            booklist.add(cunbook);
								cout<<"已存入"<<endl;
							}
							cout<<"输入任意数字返回"<<endl;
							cin>>fh;
							booklist.write();

                            fh=-1;
						}
				        break;
			         case 2: 
						 while(fh!=-1)
						 {
							 cout<<"请输入需要删除的书的书号：";
			                 cin>>xuhao;
							 linbook.setbno(xuhao);
			                 if(Book* bz=booklist.allfind(linbook)){
								 booklist.stringremove(xuhao);
								 cout<<"删除成功"<<endl;
							 }
							 else{
							 cout<<"该本书不存在"<<endl;
							 }
							 booklist.write();
							 cout<<"输入任意数字返回"<<endl;
							 cin>>fh;
                             fh=-1;
						 }
				        break;
			         case 3:
						 while(fh!=-1)
						 {
							 cout<<"请输入需要修改的书的书号：";
				             cin>>xuhao;
							 linbook.setbno(xuhao);  
				             if(Book* bz=booklist.allfind(linbook)){
								 bz->setinformationg();
								 booklist.write();
								 
							 }
							 else{
							 cout<<"该本书不存在"<<endl;
							 }
							 
							 cout<<"输入任意数字返回"<<endl;
							 cin>>fh;
                             fh=-1;
						 }
					}
				}
			}
		 
			if(n==5){
				while(n4!=-1)
				{   
					fh=0;
					cout<<"1.添加读者"<<endl;
					cout<<"2.删除读者"<<endl;
					cout<<"3.修改读者信息"<<endl;
					cout<<"请选择（1/2/3）：";
				    cin>>n4;
				    switch(n4){
				    case 1:
						while(fh!=-1)
						{
							readerlist.newadd();
							readerlist.write();
							cout<<"输入任意数字返回"<<endl;
							cin>>fh;
                            fh=-1;
						}
							break;
					case 2:
						while(fh!=-1)
						{
							cout<<"请输入要删除的读者的账号：";
						    cin>>xuhao;
						    linreader.no=xuhao;
						    if(Reader* ez=readerlist.find(linreader)){
								readerlist.readerstringremove(xuhao);
								cout<<"删除成功"<<endl;
							}
							else{
							 cout<<"该账号不存在"<<endl;
							 }
							readerlist.write();
							cout<<"输入任意数字返回"<<endl;
							cin>>fh;
                            fh=-1;
						}
					    break;
				    case 3:
						while(fh!=-1)
						{
							cout<<"请输入需要修改的读者的账号：";
					        cin>>xuhao;
					        linreader.no=xuhao;
							if(Reader* rz=readerlist.find(linreader)){
								rz->setreaderinfomation();
								cout<<"修改成功"<<endl;
							}
							else{
							 cout<<"该帐号不存在"<<endl;
							 }
							readerlist.write();
							cout<<"输入任意数字返回"<<endl;
							cin>>fh;
                            fh=-1;
						}
					break;
				}
			}
			}
			if(n==6){
				while(n4!=-1)
				{   
					fh=0;
					cout<<"1.添加工作人员"<<endl;
					cout<<"2.删除工作人员"<<endl;
					cout<<"3.修改工作人员信息"<<endl;
					cout<<"请选择（1/2/3,输入-1返回上层结构）：";
					cin>>n4;
					switch(n4){
					case 1:
						while(fh!=-1)
						{
							workerlist.newadd();
							workerlist.write();
							cout<<"输入任意数字返回"<<endl;
							cin>>fh;
                            fh=-1;
						}
						break;
			        case 2:
						while(fh!=-1)
						{
							cout<<"请输入要删除的工作人员的账号：";
						    cin>>xuhao;
						    linworker.no=xuhao;
							if(Worker* wz=workerlist.find(linworker)){
								workerlist.remove(xuhao);
								cout<<"删除成功"<<endl;
							}
							else{
							 cout<<"该账号不存在"<<endl;
							 }
							workerlist.write();
							cout<<"输入任意数字返回"<<endl;
							cin>>fh;
                            fh=-1;
						}
						 break;
					 
					 case 3:
						 while(fh!=-1)
						{
							 cout<<"请输入需要修改的工作人员的账号：";
						     cin>>xuhao;
						     linworker.no=xuhao;
						     if(Worker* wz=workerlist.find(linworker)){
								 wz->setworkerinfomation();
							 }
							 else{
							 cout<<"该账号不存在"<<endl;
							 }
							 workerlist.write();
							 cout<<"输入任意数字返回"<<endl;
							 cin>>fh;
                             fh=-1;
						}
						 break;
				
				}

			}
			}
			}
    }

	  else
	 {
		 cout<<"密码或账号输入错误"<<endl;
	 }
}    
//添加信息到链表
void Managerlist::add(Manager& a){
    Manager* pn=new Manager(a);
	if(ptr){
		pn->next=ptr;
	}
	if(!ptr){
		pn->next=NULL;
	}
	ptr=pn;
}
//移除
void Managerlist::remove(string rev)
{
	Manager rea(rev);
	for(Manager* r=ptr;r;r=r->next){
		if(*r==Manager(rea)){
			r=r->next;
			delete r;
			break;
		}
	}

	
}
//输出
void Managerlist::display(){
	for(Manager* pn=ptr;pn;pn=pn->next)
	{
		pn->display();
	}
}
void Managerlist::write(){
	ofstream out("manager.txt");
	
	for(Manager* r=ptr;r!=NULL;r=r->next)
	{  
		
		out<<r->no<<"    "<<r->name<<"     "<<r->getmpass()<<endl;
	}
}
Managerlist::~Managerlist()
{
	for(Manager* r=ptr;r=ptr;delete r){
		ptr=ptr->next;
	}
}