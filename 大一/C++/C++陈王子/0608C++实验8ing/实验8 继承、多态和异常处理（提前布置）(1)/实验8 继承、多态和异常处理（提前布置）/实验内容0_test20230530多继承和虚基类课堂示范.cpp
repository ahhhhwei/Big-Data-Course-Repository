#include<iostream>
using namespace std;
class A{
public:
  A(int x=1):ax(x){ 
    cout<<"A(int=1):"<<ax<<endl;
  }
  ~A(){ 
    cout<<"~A():"<<ax<<endl;
  }
protected:
  int ax;
};
class B:virtual public A{
public:
  B(int xa,int xb):A(xa),bx(xb){ 
    cout<<"B(int,int):ax="<<ax
		<<",bx="<<bx<<endl;
  }
   ~B(){ 
    cout<<"~B():"<<endl;
  }
protected:
  int bx;
};
class C:virtual public A{
public:
  C(int xa,int xc):cx(xc){ 
    cout<<"C(int,int):ax="<<ax<<",cx="<<cx<<endl;
  }
  ~C(){ 
    cout<<"~C():"<<endl;
  }
protected:
  int cx;
};
class D:public B,public C{
public:
  D(int xa,int xb,int xc,int xd)
	  :C(xa,xc),B(xa,xb),A(xa){  //没有定义虚基类时，这里的A(xa)去掉；有虚基类定义时这里的A(xa)也是可写可不写
      dx=xd;
	  cout<<"D(int,int):ax="
		  <<B::ax
	  <<",bx="<<bx
	  <<",cx="<<cx
	  <<",dx="<<dx<<endl;
  }
  ~D(){ 
    cout<<"~D():"<<endl;
  }
protected:
  int dx;
};

int main(){
	D obj(2,3,4,5); //比较去掉virtual后的构造和析构的执行顺序

	return 0;
}








#ifndef rect_hpp
#define rect_hpp
#include <stdio.h>
#include "point.hpp"
class Rect:public Point {
public:
    Rect(float x=0,float y=0,float chang=0,float kuan=0); //构造函数
    void setchang(float); //设置长
    void setkuan(float); //设置宽
    float getchang() const; //读取长
    float getkuan( ) const; //读取宽
    virtual float area ( ) const//计算矩形面积
    {
        return chang*kuan;
    }
    friend ostream& operator<<(ostream&,const Rect &);
protected:
  float chang,kuan;
};
#endif /* rect_hpp */
#include "rect.hpp"
Rect::Rect(float x,float y,float ch,float k):Point(x,y),chang(ch),kuan(k){}//构造函数
void Rect::setchang(float ch)//设置长
{
    chang = ch;
}
void Rect::setkuan(float k)//设置宽
{
    kuan = k;
}
float Rect::getchang() const//读取长
{
    return chang;
}
float Rect::getkuan( ) const//读取宽
{
    return kuan;
}
ostream& operator<<(ostream& output,const Rect & R)
{
    output<<"Center=["<<R.x<<","<<R.y<<"],chang="<<R.chang<<",kuan="<<R.kuan<<",area="<<R.area()<<endl;
    return output;
}
	三角形类Triangle：
#ifndef Triangle_hpp
#define Triangle_hpp
#include <stdio.h>
#include <cmath>
#include "point.hpp"
class Triangle:public Point {
public:
    Triangle(float x=0,float y=0,float x2=0,float y2=0,float x3=0,float y3=0); //构造函数
    void setx2y2(float,float); //设置(x2,y2)点
    void setx3y3(float,float); //设置(x3,y3)点
    float getx2() const; //读取x2
    float gety2( ) const; //读取y2
    float getx3() const; //读取x3
    float gety3( ) const; //读取y3
    virtual float area ( ) const//计算三角形面积
    {
        float a = sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2));
        float b = sqrt((x2-x)*(x2-x)+(y2-y)*(y2-y));
        float c = sqrt((x3-x)*(x3-x)+(y3-y)*(y3-y));
        float p = (a+b+c)/2;
        return sqrt(p*(p-a)*(p-b)*(p-c));
    }
    friend ostream& operator<<(ostream&,const Triangle &);
protected:
    float x2,y2,x3,y3;
};
#endif /* Triangle_hpp */
#include "Triangle.hpp"
Triangle::Triangle(float x,float y,float x2,float y2,float x3,float y3):Point(x,y),x2(x2),y2(y2),x3(x3),y3(y3){}//构造函数
void Triangle::setx2y2(float a,float b)//设置(x2,y2)点
{
    x2 = a;
    y2 = b;
}
void Triangle::setx3y3(float a,float b) //设置(x3,y3)点
{
    x3 = a;
    y3 = b;
}
float Triangle::getx2() const//读取x2
{
    return x2;
}
float Triangle::gety2( ) const//读取y2
{
    return y2;
}
float Triangle::getx3() const//读取x3
{
    return x3;
}
float Triangle::gety3( ) const//读取y3
{
    return y3;
}
ostream& operator<<(ostream& output,const Triangle &T)
{
    output<<"(x,y)=["<<T.x<<","<<T.y<<"]"<<endl;
    output<<"(x2,y2)=["<<T.x2<<","<<T.y2<<"]"<<endl;
    output<<"(x3,y3)=["<<T.x3<<","<<T.y3<<"]"<<endl;
    output<<"area="<<T.area()<<endl;
    return output;
}
	球体类Sphere：
#ifndef Sphere_hpp
#define Sphere_hpp
#include <stdio.h>
#include "circle.hpp"
class Sphere:public Circle{
public:
    Sphere(float x=0,float y=0,float r=0);//构造函数
    void setr(float); //设置圆半径
    float getr( ) const; //读取圆半径
    float area( ) const; //计算圆面积
    float volume( ) const; //计算圆体积
    friend ostream& operator<<(ostream&,const Sphere&);//重载输出运算符
};
#endif /* Sphere_hpp */
#include "Sphere.hpp"
Sphere::Sphere(float a,float b,float rr)//构造函数
{
    x = a;
    y = b;
    radius = rr;
}
void Sphere::setr(float rr)//设置圆半径
{
    radius = rr;
}
float Sphere::getr( ) const//读取圆半径
{
    return radius;
}
float Sphere::area( ) const//计算球面积
{
    return 4*3.14159*radius*radius;
}
float Sphere::volume( ) const//计算球体积
{
    return (4/3)*3.14159*radius*radius*radius;
}
ostream& operator<<(ostream& output,const Sphere& S)//重载输出运算符
{
    output<<"Center=["<<S.x<<","<<S.y<<"],r="<<S.radius<<endl;
    output<<"area="<<S.area( )<<",volume="<<S.volume()<<endl;
    return output;
}
	立方体类Cube：
#ifndef Cube_hpp
#define Cube_hpp
#include <stdio.h>
#include "rect.hpp"
class Cube:public Rect{
public:
    Cube(float x=0,float y=0,float chang=0,float kuan=0,float height=0);//构造函数
    void setHeight(float); //设置立方体高
    float getHeight( ) const; //读取立方体高
    float area( ) const; //计算立方体表面积
    float volume( ) const; //计算立方体体积
    friend ostream& operator<<(ostream&,const Cube&);//重载输出运算符
protected:
    float height; //立方体高
};
#endif /* Cube_hpp */
#include "Cube.hpp"
Cube::Cube(float a,float b,float ch,float k,float h)//构造函数
{
    x = a;
    y = b;
    chang = ch;
    kuan = k;
    height = h;
}
void Cube::setHeight(float h)//设置立方体高
{
    height = h;
}
float Cube::getHeight( ) const //读取立方体高
{
    return height;
}
float Cube::area( ) const //计算立方体表面积
{
    return 2*(chang*kuan)+2*(chang*height)+2*(kuan*height);
}
float Cube::volume( ) const //计算立方体体积
{
    return Rect::area()*height;
}
ostream& operator<<(ostream& output,const Cube& cu)//重载输出运算符
{
    output<<"chang="<<cu.chang<<",kuan="<<cu.kuan<<",height="<<cu.height<<endl;
    output<<"area="<<cu.area()<<",volume="<<cu.volume()<<endl;
    return output;
}
6)体验使用基类引用体现多态的应用场合。
Step1：为Point类，Circle类，Cylinder类设计同名成员函数display()，原型为：
void display(ostream& out) const;
该接口完成不同类的数据信息的输出。不同类的display实现参考如下：
void Point::display(ostream& out) const{
   cout<<”Point:”<<x<<”,”<<y<<endl;
}
void Circle::display(ostream& out)const{
   cout<<”Circle:”<<x<<”,”<<y<<”; radius:”<<radius<<”; area:”<<area()<<endl;
}
void Cylinder::display(ostream& out) const{
cout<<”Cylinder:”<<x<<”,”<<y<<”;radius:”<<radius<<”;area:”<<area()
<<”;volumn:”<<volumn()<<endl;
} 
Step2：并在基类Point中限定display为虚函数。
Step3：修改基类Point的输出流重载函数为：
ostream& operator<<(ostream& out, const Point& p){
p.display(out);
return out;
}
