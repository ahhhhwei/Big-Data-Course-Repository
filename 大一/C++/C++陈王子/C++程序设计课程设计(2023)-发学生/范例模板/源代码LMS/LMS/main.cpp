#include"booklist.h"
#include"managerlist.h"
#include"workerlist.h"
#include"readerlist.h"
#include<fstream>
using namespace std;
int main(){
	Reader reader2;
	Worker worker2;
	Manager manager2;
	string a,b,c,d,ds,es,fs,gs,hs,is,js,ks,account,password;
    int e,f,g,i=0,fh=0;
	ifstream inbook("book.txt");	
	ifstream inreader("reader.txt");
	ifstream inworker("worker.txt");
	Booklist blist;	
	Readerlist rlist;
	Workerlist wlist;
	Managerlist mlist;
	ifstream inmanager("manager.txt");
	while(inbook>>a>>b>>c>>d>>e>>f>>g){
		Book rea(a,b,c,d,e,f,g);
	    blist.add(rea);
	}
	while(inreader>>a>>b>>c>>ds>>es>>fs>>gs>>hs>>is>>js>>ks){
	    Reader reader1(a,b,c);
	    reader1.setalbno(ds,es,fs,gs,hs,is,js,ks);
		rlist.add(reader1);
	}
    while(inworker>>a>>b>>c){
		Worker worker1(a,b,c);
		wlist.add(worker1);
	}
	while(inmanager>>a>>b>>c){
	   Manager manager1(a,b,c);
	   mlist.add(manager1);
	}
	int i1=0,i2;
    while(i1!=-1)
	{  
		i1=0,i2=0;
		i=0;
		cout<<"    ------------------------------------------------------\n";
		cout<<"    |           ��ӭ����ͼ�����ϵͳ                     |"<<endl;
	    cout<<"    |           1.��ѯͼ����Ϣ                           |"<<endl; 
		cout<<"    |           2.��¼                  ��Ȩ������Ȩ�ؾ� |"<<endl;  
		cout<<"    ------------------------------------------------------\n";
    	cout<<"               ��ѡ��1/2,-1Ϊ��������";
    	cin>>i1;
		system("cls");
	    switch(i1){
    	case 1:
			   
			  while(i!=-1)
			  {  
				  fh=0;
				  cout<<"--------------����ҽзָ���--------------------\n";
				  cout<<"1.����Ų���"<<endl;
				  cout<<"2.����������"<<endl;
				  cout<<"3.�߼�����"<<endl;
				  cout<<"��ѡ��1/2/3,����-1�����ϲ�ṹ����"<<endl;
				   cin>>i;
				   system("cls");
				   switch(i){
				   case 1:
					   while(fh!=-1)
					   {

						   blist.find(i);

						   cout<<"�����������ַ���"<<endl;
			               cin>>fh;
                           fh=-1;
					   }
					   break;
				   case 2:
					   while(fh!=-1)
					   {
	
						   blist.find(i);
						   cout<<"�����������ַ���"<<endl;
			               cin>>fh;
                           fh=-1;
					   }
						   break;
		           case 3:
					   while(fh!=-1)
					   {
						   blist.advancedfind();
						   cout<<"�����������ַ���"<<endl;
			               cin>>fh;
                           fh=-1;
					   }
			           break;
				   }
				   fh=0;
			  }
			  break;
    case 2:
		while(i2!=-1){
			cout<<"--------------����ҽзָ���--------------------"<<endl;
			cout<<"�û�ѡ��"<<endl;
			cout<<"1.���ߵ�¼"<<endl;
			cout<<"2.������Ա��¼"<<endl;
			cout<<"3.������Ա��¼"<<endl;
			cout<<"��ѡ��1/2/3,����-1�����ϲ�ṹ��"<<endl;
            cin>>i2;
			if(i2!=-1)
			{
				if(i2>=4||i2<=0)
					cout<<"�������"<<endl;
				else{
					cout<<"�˺�    "<<endl;
					cin>>account;
					cout<<"����    "<<endl;
					cin>>password;
					switch(i2)
					{
					case 1:
					rlist.load(reader2.setreader(account,password),blist);
		            break;
					case 2:
					wlist.load(worker2.setwoker(account,password),blist,rlist);
					break;
					case 3:
					mlist.load(manager2.setmanager(account,password),blist,rlist,wlist);
		            break;
					}

				}
			}
		}
			system("cls");
		    break;
		
		
	  case -1:
		i1=-1;

		break;
	

		
	default:
		
		cout<<"�������"<<endl;
		i1=-1;

		break;
	
		}
	}

	

		wlist.write();
    	blist.write();
	    rlist.write();
    	mlist.write();
		blist.~Booklist();
		rlist.~Readerlist();
		mlist.~Managerlist();
		wlist.~Workerlist();
		cout<<"ллʹ��"<<endl;


	return 0;
}
