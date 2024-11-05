#include<iostream>
using namespace std;


 class A { //基类
public:
A(int v1=0,int v2=0,int v3=0):a(v1),b(v2),c(v3){ }
void F1(){cout<< "F1"<<a<<" "<<b<<" "<<c<<endl;}
     int a;
protected:
void F2( ) {cout<<"F2"<<a<<" "<<b<<" "<<c<<endl;}
     int b;
private:
void F3(){cout<<"F3"<<a<<" "<<b<<" "<<c<<endl;}
int c;
};
class B: public A{
public:
    //B的构造函数缺失
    void F4( ) {cout<<"F4"<<Ba<" "<<Bb<<" "<<Bc<<endl;}
int Ba;
protected:
    void F5( ) {cout<<"F5"<<Ba<<" "<<Bb<<" "<<Bc<<endl;}
int Bb;
private:
void F6(){cout<<"F6"<<Ba<<" "<<Bb<<" "<<Bc<<endl;}
int Bc;
};
class C: protected  B{
public:
   //C的构造函数缺失
void F7(){cout<<"F7"<<Ba<<" "<<Bb <<endl;}
void F8(){cout<<"F8"<<Ca<<" "<<Cb <<endl;}
   int Ca;
private:
   int Cb;
};



class B: public A{
public:
    B(int v1=0, int v2=0, int v3=0, int v4=0, int v5=0) : A(v1, v2, v3), Ba(v4), Bb(v5), Bc(0) {}
    void F4( ) {cout<<"F4"<<Ba<<" "<<Bb<<" "<<Bc<<endl;}
    int Ba;
protected:
    void F5( ) {cout<<"F5"<<Ba<<" "<<Bb<<" "<<Bc<<endl;}
    int Bb;
private:
    void F6(){cout<<"F6"<<Ba<<" "<<Bb<<" "<<Bc<<endl;}
    int Bc;
};

class C: protected B{
public:
    C(int v1=0, int v2=0, int v3=0, int v4=0, int v5=0, int v6=0) : B(v1, v2, v3, v4, v5), Ca(v6), Cb(0) {}
    void F7(){cout<<"F7"<<Ba<<" "<<Bb <<endl;}
    void F8(){cout<<"F8"<<Ca<<" "<<Cb <<endl;}
    int Ca;
protected:
    int Cb;
};

int main()
{
    A Aobj1,Aobj2(1,2,3);
    B Bobj1,Bobj2(1,2,3,4,5);
    C Cobj1,Cobj2(1,2,3,4,5,6);

    // 访问类A的成员
    Aobj1.a = 10;
    Aobj1.F1();

    // 访问类B的成员
    Bobj2.a = 20;
    Bobj2.Ba = 30;
    Bobj2.F4();

    // 访问类C的成员
    Cobj2.a = 40;
    Cobj2.Ba = 50;
    Cobj2.Ca = 60;
    Cobj2.F7();
    Cobj2.F8();

    return 0;
}
