#include"workerlist.h"
#include<fstream>
//���ҹ�����Ա��Ϣ
Worker* Workerlist::find(Worker& a){
	for(Worker* m=ptr;m;m=m->next)
	{
		if(m->no==a.no){
			return  m;
		}
	}
}
Worker* Workerlist::yanzhenfind(Worker& a){
	for(Worker* m=ptr;m;m=m->next)
	{
		if(*m==a){
			return m;
		}
	}
}
//��½������Ա�˻�
void Workerlist::load(Worker& a,Booklist& booklist,Readerlist& readerlist){
     string readern="null",xuhao="000";
	 if(yanzhenfind(a))
	 {
		 Worker *z;
		 z=find(a);
		 cout<<"��½�ɹ�"<<endl;
		 z->workerdisplay();
		 int n=0,fh=0;
		 
		 while(n!=-1)
		 {   
			 n=0;
			 fh=0;
			 cout<<"---------------�������ҷָ���--------------------"<<endl;
			 cout<<"1.��ʾ������Ϣ"<<endl;
			 cout<<"2.�޸�����"<<endl;
			 cout<<"3.�޸�����"<<endl;
			 cout<<"4.����"<<endl;
			 cout<<"5.����"<<endl;
			 cout<<"��ѡ������-1�����ϲ�ṹ����";
			 cin>>n;
		     switch(n)
			 {
			 case 1:
				 while(fh!=-1)
				 {
					 z->workerdisplay();
					 cout<<"�����������"<<endl;
			         cin>>fh;
                     fh=-1;
				 }
	 		 break;
		    case 2:
			 
				while(fh!=-1)
				{				  
					z->gpass();
				    cout<<"�޸ĺ������Ϊ��"<<z->getwpass()<<endl;
				    write();
				    cout<<"�����������"<<endl;
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
				   cout<<"�����������"<<endl;
			       cin>>fh;
                   fh=-1;
			   }
			 break;
		 case 4:			 
			 cout<<"������ߺţ�";
			 cin>>readern;		
		     break;
		 case 5:
				 cout<<"������ߺţ�";
			     cin>>readern;			
			 break;		 			 
		 default:
			 if(n!=-1){
			 cout<<"�������"<<endl;
			 }
			 break;				
			 }		 		 			 
			 while(fh!=-1)		 
			 {							 
				 if(n==4){			 				 
					 Reader reader1(readern,"null","null");					
					 if(Reader* za=readerlist.find(reader1)){				 					
						 if(za->alreadyborrownum()==8){					 											 
							 cout<<"�ѽ���8���������ٽ�"<<endl;														
						 }				 											
						 else{					 				 					 													
							 cout<<"���������������ţ�";				 					 												
							 cin>>xuhao;					 									 												
							 Book linbook(xuhao);				 					 												 
							 if(Book* bz=booklist.allfind(linbook)){					 																			 
								 if(bz->gcanborrow()>1){						 							 
									 za->setsinglealbno(za->canalbnonum(),xuhao);				         							 																	 
									 bz->borrowbook();								
									 booklist.write();								 
									 readerlist.write();								 
									 cout<<"����ɹ�"<<endl;							 
								 }					 						 														
								 else{						 							 								
									 cout<<"�����ѽ���"<<endl;											 														 								 
								 }					 									 													 
							 }							 
							 else{						 							 
								 cout<<"��Ŵ���"<<endl;									 				 						 
							 }						 					 
						 }					 				 
					 }					 			 				 				 
					 else{									 
						 cout<<"�����˺Ŵ���"<<endl;					 			 				 
					 }			 			 				 
					 cout<<"�����������"<<endl;
					 cin>>fh;
				 }		 		 			 						 				 			 
				 fh=-1;					 			 		 
			 }
		 
		fh=0;
		 while(fh!=-1)		
		 {		
			 if(n==5){
				 Reader reader1(readern,"null","null");				
				 if(Reader* za=readerlist.find(reader1)){
					 
					 cout<<"���������������ţ�";					
					 cin>>xuhao;					
					 Book linbook(xuhao);					
					 if(Book* bz=booklist.allfind(linbook)){
						 					
						 if(za->alreadyborrow(xuhao)){					 						
							 if(bz->gcanborrow()<bz->gstorenum()){						 							
								 bz->returnbook();								
								 za->returnreaderbook(xuhao);
								 cout<<"����ɹ�"<<endl;
								 readerlist.write();
								 booklist.write();
							 }														 
							 
							 else{							
								 cout<<"ͼ��Ŵ���"<<endl;
							 }							 
						 }
						 else{
							 cout<<"�ö���δ�����"<<endl;							 
						 }						 
					 }
					 else{
						 cout<<"ͼ��Ŵ���"<<endl;						 					 
					 }
					 					 				 				 
				 }
				 else{						
					 cout<<"�����˺Ŵ���"<<endl;					
				 } 
				 cout<<"�����������ַ���"<<endl;			    
			 
				 cin>>fh;
			 }				 
			                
			 fh=-1;
			 //n=0;//
		 
		 }
		 }
		 

		 }
		 else			
		 {
			
			 cout<<"������˺��������"<<endl;
			
		 }

}    

//�����Ϣ������
void Workerlist::add(Worker& a){
    Worker* pn=new Worker(a);
	if(ptr){
		pn->next=ptr;
	}
	if(!ptr){
		pn->next=NULL;
	}
	ptr=pn;
}
//�Ƴ���Ϣ


	
void Workerlist::remove(string rev)
{
	Worker rea(rev);
	if(Worker *wz=find(rea)){
		wz->workersetfull();
	}
}
		


	

//���
void Workerlist::workerlistdisplay(){
	for(Worker* pn=ptr;pn;pn=pn->next)
	{
		pn->display();
	}
}

void Workerlist::write(){
	ofstream out("worker.txt");
	
	for(Worker* r=ptr;r!=NULL;r=r->next)
	{  
		if(!r->ifworkernofull()){
		out<<r->no<<"    "<<r->name<<"     "<<r->getwpass()<<endl;
		}
	}
}
void Workerlist::newadd()
{
    string linno,linname,linpass;
	cout<<"�����빤����Ա��������Ϣ"<<endl;
	cout<<"�˺�  "<<"����  "<<"�˻�����  "<<endl;
	cin>>linno>>linname>>linpass;
    Worker linworker(linno);
	if(find(linworker)){
		cout<<"���˺��ѱ�ע��"<<endl;
	}
	else{
		Worker linworker1(linno,linname,linpass);
		add(linworker1);
		cout<<"ע��ɹ�"<<endl;
	}
}
Workerlist::~Workerlist()
{
	for(Worker* r=ptr;r=ptr;delete r){
		ptr=ptr->next;
	}
}