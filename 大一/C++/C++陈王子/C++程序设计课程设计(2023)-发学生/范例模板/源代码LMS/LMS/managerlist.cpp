#include"managerlist.h"
#include<fstream>
//���ҹ���Ա��Ϣ
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
//��½����Ա�˻�
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
		 cout<<"��½�ɹ�"<<endl;		 
		 int n=0,n4=0;
		 while(n!=-1)
		 {  
			 n4=0;
			 z->display();
			 cout<<"1.��ʾ������Ϣ"<<endl;
			 cout<<"2.�޸�����"<<endl;
			 cout<<"3.�޸�����"<<endl;
			 cout<<"4.ά��ͼ����Ϣ"<<endl;
			 cout<<"5.ά��������Ϣ"<<endl;
			 cout<<"6.ά��������Ա��Ϣ"<<endl;
			 cout<<"��ѡ������-1�����ϲ�ṹ����"<<endl;
			 cin>>n;
			 fh=0;
		     switch(n)
			 {
			 case 1:
				while(fh!=-1)
				{
				  z->managerdisplay();
				  cout<<"�����������ַ���"<<endl;
				  cin>>fh;
				  fh=-1;
				}
				 break;
		     case 2:
				 while(fh!=-1)
				 {
					 z->gpass();
			         cout<<"�޸ĺ������Ϊ��"<<z->getmpass()<<endl;
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
				     write();
			         cout<<"�޸ĺ������Ϊ��"<<z->name<<endl;
					 cout<<"�����������ַ���"<<endl;
				     cin>>fh;
				     fh=-1;
				 }
			     break;
			 }
	    	if(n==4){
				while(n4!=-1)
				{   fh=0;
				    cout<<"1.���ͼ��"<<endl;
					cout<<"2.ɾ��ͼ��"<<endl;
					cout<<"3.�޸�ͼ����Ϣ"<<endl;
					cout<<"��ѡ��1/2/3������-1�����ϲ�ṹ����";
					cin>>n4;
					switch(n4){
			        case 1:
						while(fh!=-1)
						{
							cout<<"�������´���������ţ�";					 
							cin>>xuhao;					 
						    linbook.setbno(xuhao);		 
							if(Book* bz=booklist.allfind(linbook)){			 				 
								bz->storebook();
								cout<<"�Ѵ���"<<endl;
							}					 
				            else{			 				
								string linname,linauthor,linpress;			 				 
					            int linnum;							
					            cout<<"�������������Ϣ"<<endl;							
					            cout<<"����"<<"  "<<"����"<<"  "<<"������"<<"  "<<"��������"<<endl;							 
					            cin>>linname>>linauthor>>linpress>>linnum;							
					            Book cunbook(xuhao,linname,linauthor,linpress,linnum,linnum,0);			 				 
					            booklist.add(cunbook);
								cout<<"�Ѵ���"<<endl;
							}
							cout<<"�����������ַ���"<<endl;
							cin>>fh;
							booklist.write();

                            fh=-1;
						}
				        break;
			         case 2: 
						 while(fh!=-1)
						 {
							 cout<<"��������Ҫɾ���������ţ�";
			                 cin>>xuhao;
							 linbook.setbno(xuhao);
			                 if(Book* bz=booklist.allfind(linbook)){
								 booklist.stringremove(xuhao);
								 cout<<"ɾ���ɹ�"<<endl;
							 }
							 else{
							 cout<<"�ñ��鲻����"<<endl;
							 }
							 booklist.write();
							 cout<<"�����������ַ���"<<endl;
							 cin>>fh;
                             fh=-1;
						 }
				        break;
			         case 3:
						 while(fh!=-1)
						 {
							 cout<<"��������Ҫ�޸ĵ������ţ�";
				             cin>>xuhao;
							 linbook.setbno(xuhao);  
				             if(Book* bz=booklist.allfind(linbook)){
								 bz->setinformationg();
								 booklist.write();
								 
							 }
							 else{
							 cout<<"�ñ��鲻����"<<endl;
							 }
							 
							 cout<<"�����������ַ���"<<endl;
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
					cout<<"1.��Ӷ���"<<endl;
					cout<<"2.ɾ������"<<endl;
					cout<<"3.�޸Ķ�����Ϣ"<<endl;
					cout<<"��ѡ��1/2/3����";
				    cin>>n4;
				    switch(n4){
				    case 1:
						while(fh!=-1)
						{
							readerlist.newadd();
							readerlist.write();
							cout<<"�����������ַ���"<<endl;
							cin>>fh;
                            fh=-1;
						}
							break;
					case 2:
						while(fh!=-1)
						{
							cout<<"������Ҫɾ���Ķ��ߵ��˺ţ�";
						    cin>>xuhao;
						    linreader.no=xuhao;
						    if(Reader* ez=readerlist.find(linreader)){
								readerlist.readerstringremove(xuhao);
								cout<<"ɾ���ɹ�"<<endl;
							}
							else{
							 cout<<"���˺Ų�����"<<endl;
							 }
							readerlist.write();
							cout<<"�����������ַ���"<<endl;
							cin>>fh;
                            fh=-1;
						}
					    break;
				    case 3:
						while(fh!=-1)
						{
							cout<<"��������Ҫ�޸ĵĶ��ߵ��˺ţ�";
					        cin>>xuhao;
					        linreader.no=xuhao;
							if(Reader* rz=readerlist.find(linreader)){
								rz->setreaderinfomation();
								cout<<"�޸ĳɹ�"<<endl;
							}
							else{
							 cout<<"���ʺŲ�����"<<endl;
							 }
							readerlist.write();
							cout<<"�����������ַ���"<<endl;
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
					cout<<"1.��ӹ�����Ա"<<endl;
					cout<<"2.ɾ��������Ա"<<endl;
					cout<<"3.�޸Ĺ�����Ա��Ϣ"<<endl;
					cout<<"��ѡ��1/2/3,����-1�����ϲ�ṹ����";
					cin>>n4;
					switch(n4){
					case 1:
						while(fh!=-1)
						{
							workerlist.newadd();
							workerlist.write();
							cout<<"�����������ַ���"<<endl;
							cin>>fh;
                            fh=-1;
						}
						break;
			        case 2:
						while(fh!=-1)
						{
							cout<<"������Ҫɾ���Ĺ�����Ա���˺ţ�";
						    cin>>xuhao;
						    linworker.no=xuhao;
							if(Worker* wz=workerlist.find(linworker)){
								workerlist.remove(xuhao);
								cout<<"ɾ���ɹ�"<<endl;
							}
							else{
							 cout<<"���˺Ų�����"<<endl;
							 }
							workerlist.write();
							cout<<"�����������ַ���"<<endl;
							cin>>fh;
                            fh=-1;
						}
						 break;
					 
					 case 3:
						 while(fh!=-1)
						{
							 cout<<"��������Ҫ�޸ĵĹ�����Ա���˺ţ�";
						     cin>>xuhao;
						     linworker.no=xuhao;
						     if(Worker* wz=workerlist.find(linworker)){
								 wz->setworkerinfomation();
							 }
							 else{
							 cout<<"���˺Ų�����"<<endl;
							 }
							 workerlist.write();
							 cout<<"�����������ַ���"<<endl;
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
		 cout<<"������˺��������"<<endl;
	 }
}    
//�����Ϣ������
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
//�Ƴ�
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
//���
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