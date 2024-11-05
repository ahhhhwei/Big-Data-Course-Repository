#include"book.h"
void Book::bookdisplay()
{
	cout<<"书号："<<gbno()<<endl;
	cout<<"书名："<<gbname()<<endl;
	cout<<"出版社："<<gpress()<<endl;
	cout<<"藏书量："<<gstorenum()<<endl;
	cout<<"可借数："<<gcanborrow()<<endl;
}
bool Book::ifbnofull()
{
	return (bno=="null");

}
void Book::setinformationg()
{
	cout<<"请输入图书信息"<<endl;
	cout<<"书名  "<<"作者  "<<"出版社  "<<"馆藏数量  "<<"可借数量"<<endl;
	cin>>bname>>author>>press>>storenum>>canborrow;
	borrownum=storenum-canborrow;
	cout<<"修改成功"<<endl;
}
