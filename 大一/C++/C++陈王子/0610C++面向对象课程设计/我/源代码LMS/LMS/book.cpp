#include"book.h"
void Book::bookdisplay()
{
	cout<<"��ţ�"<<gbno()<<endl;
	cout<<"������"<<gbname()<<endl;
	cout<<"�����磺"<<gpress()<<endl;
	cout<<"��������"<<gstorenum()<<endl;
	cout<<"�ɽ�����"<<gcanborrow()<<endl;
}
bool Book::ifbnofull()
{
	return (bno=="null");

}
void Book::setinformationg()
{
	cout<<"������ͼ����Ϣ"<<endl;
	cout<<"����  "<<"����  "<<"������  "<<"�ݲ�����  "<<"�ɽ�����"<<endl;
	cin>>bname>>author>>press>>storenum>>canborrow;
	borrownum=storenum-canborrow;
	cout<<"�޸ĳɹ�"<<endl;
}
