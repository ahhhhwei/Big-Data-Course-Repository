#include"workerlist.h"
#include<fstream>
//查找工作人员信息
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
//登陆工作人员账户
void Workerlist::load(Worker& a,Booklist& booklist,Readerlist& readerlist){
     string readern="null",xuhao="000";
	 if(yanzhenfind(a))
	 {
		 Worker *z;
		 z=find(a);
		 cout<<"登陆成功"<<endl;
		 z->workerdisplay();
		 int n=0,fh=0;
		 
		 while(n!=-1)
		 {   
			 n=0;
			 fh=0;
			 cout<<"---------------你好请叫我分割线--------------------"<<endl;
			 cout<<"1.显示个人信息"<<endl;
			 cout<<"2.修改密码"<<endl;
			 cout<<"3.修改姓名"<<endl;
			 cout<<"4.借书"<<endl;
			 cout<<"5.还书"<<endl;
			 cout<<"请选择（输入-1返回上层结构）：";
			 cin>>n;
		     switch(n)
			 {
			 case 1:
				 while(fh!=-1)
				 {
					 z->workerdisplay();
					 cout<<"按任意键返回"<<endl;
			         cin>>fh;
                     fh=-1;
				 }
	 		 break;
		    case 2:
			 
				while(fh!=-1)
				{				  
					z->gpass();
				    cout<<"修改后的密码为："<<z->getwpass()<<endl;
				    write();
				    cout<<"按任意键返回"<<endl;
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
				   cout<<"按任意键返回"<<endl;
			       cin>>fh;
                   fh=-1;
			   }
			 break;
		 case 4:			 
			 cout<<"输入读者号：";
			 cin>>readern;		
		     break;
		 case 5:
				 cout<<"输入读者号：";
			     cin>>readern;			
			 break;		 			 
		 default:
			 if(n!=-1){
			 cout<<"输入错误"<<endl;
			 }
			 break;				
			 }		 		 			 
			 while(fh!=-1)		 
			 {							 
				 if(n==4){			 				 
					 Reader reader1(readern,"null","null");					
					 if(Reader* za=readerlist.find(reader1)){				 					
						 if(za->alreadyborrownum()==8){					 											 
							 cout<<"已借满8本，不能再借"<<endl;														
						 }				 											
						 else{					 				 					 													
							 cout<<"请输入所借书的序号：";				 					 												
							 cin>>xuhao;					 									 												
							 Book linbook(xuhao);				 					 												 
							 if(Book* bz=booklist.allfind(linbook)){					 																			 
								 if(bz->gcanborrow()>1){						 							 
									 za->setsinglealbno(za->canalbnonum(),xuhao);				         							 																	 
									 bz->borrowbook();								
									 booklist.write();								 
									 readerlist.write();								 
									 cout<<"借书成功"<<endl;							 
								 }					 						 														
								 else{						 							 								
									 cout<<"此书已借完"<<endl;											 														 								 
								 }					 									 													 
							 }							 
							 else{						 							 
								 cout<<"书号错误"<<endl;									 				 						 
							 }						 					 
						 }					 				 
					 }					 			 				 				 
					 else{									 
						 cout<<"读者账号错误"<<endl;					 			 				 
					 }			 			 				 
					 cout<<"按任意键返回"<<endl;
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
					 
					 cout<<"请输入所还书的书号：";					
					 cin>>xuhao;					
					 Book linbook(xuhao);					
					 if(Book* bz=booklist.allfind(linbook)){
						 					
						 if(za->alreadyborrow(xuhao)){					 						
							 if(bz->gcanborrow()<bz->gstorenum()){						 							
								 bz->returnbook();								
								 za->returnreaderbook(xuhao);
								 cout<<"还书成功"<<endl;
								 readerlist.write();
								 booklist.write();
							 }														 
							 
							 else{							
								 cout<<"图书号错误"<<endl;
							 }							 
						 }
						 else{
							 cout<<"该读者未借该书"<<endl;							 
						 }						 
					 }
					 else{
						 cout<<"图书号错误"<<endl;						 					 
					 }
					 					 				 				 
				 }
				 else{						
					 cout<<"读者账号错误"<<endl;					
				 } 
				 cout<<"输入任意数字返回"<<endl;			    
			 
				 cin>>fh;
			 }				 
			                
			 fh=-1;
			 //n=0;//
		 
		 }
		 }
		 

		 }
		 else			
		 {
			
			 cout<<"密码或账号输入错误"<<endl;
			
		 }

}    

//添加信息到链表
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
//移除信息


	
void Workerlist::remove(string rev)
{
	Worker rea(rev);
	if(Worker *wz=find(rea)){
		wz->workersetfull();
	}
}
		


	

//输出
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
	cout<<"请输入工作人员的以下信息"<<endl;
	cout<<"账号  "<<"姓名  "<<"账户密码  "<<endl;
	cin>>linno>>linname>>linpass;
    Worker linworker(linno);
	if(find(linworker)){
		cout<<"该账号已被注册"<<endl;
	}
	else{
		Worker linworker1(linno,linname,linpass);
		add(linworker1);
		cout<<"注册成功"<<endl;
	}
}
Workerlist::~Workerlist()
{
	for(Worker* r=ptr;r=ptr;delete r){
		ptr=ptr->next;
	}
}