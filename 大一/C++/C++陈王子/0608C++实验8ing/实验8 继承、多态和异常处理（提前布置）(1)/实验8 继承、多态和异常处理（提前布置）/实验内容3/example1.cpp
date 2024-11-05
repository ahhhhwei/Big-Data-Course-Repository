#include <iostream>
using namespace std;
void f1( );
void f2( );
void f3( );
int main( )
{
try{ //调用f1( )
	f1( ); 
}
catch(double)
{
	cout<<"OK0!"<<endl;
}
cout<<"end0"<<endl;
return 0;
}

void f1( )
{
try{//调用f2( )
	f2( );
} 
catch(char)
{
	cout<<"OK1!";
}
cout<<"end1"<<endl;
}

void f2( )
{
try{ //调用f3( )
	f3( );
} 
catch(int)
{
	cout<<"Ok2!"<<endl;
}
cout<<"end2"<<endl;
}

void f3( )
{double a=0;
try{//抛出double类型异常信息
	throw a;
} 
catch(float)
{
	cout<<"OK3!"<<endl;
}
cout<<"end3"<<endl;
}