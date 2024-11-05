#include "pch.h"
#include "cylinder.h"
//Cylinder类的实现 cylinder.cpp
Cylinder::Cylinder(float a,float b,float r,float h):                                                                   Circle(a,b,r),height(h){    }

void Cylinder::setHeight(float h) //设置圆柱高
{height=h;}

float Cylinder::getHeight( ) const//读取圆柱高
 {return height;} 

float Cylinder::area( ) const//计算圆柱体面积
{ return 2*Circle::area( )+2*3.14159*radius*height;}

float Cylinder::volume() const //计算圆柱体体积
{return Circle::area()*height;}

//Cylinder类的实现
ostream& operator<<(ostream&output, const Cylinder& cy)
{   
   output<<"Center=["<<cy.x<<","<<cy.y<<"],r="<<cy.radius
                                   <<",h="<<cy.height<<"\n area="<<cy.area( )
                                   <<",volume="<<cy.volume( )<<endl;
   return output;
}
