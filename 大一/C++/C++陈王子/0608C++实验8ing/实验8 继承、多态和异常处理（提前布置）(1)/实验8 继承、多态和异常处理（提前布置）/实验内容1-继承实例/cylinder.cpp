#include "pch.h"
#include "cylinder.h"
//Cylinder���ʵ�� cylinder.cpp
Cylinder::Cylinder(float a,float b,float r,float h):                                                                   Circle(a,b,r),height(h){    }

void Cylinder::setHeight(float h) //����Բ����
{height=h;}

float Cylinder::getHeight( ) const//��ȡԲ����
 {return height;} 

float Cylinder::area( ) const//����Բ�������
{ return 2*Circle::area( )+2*3.14159*radius*height;}

float Cylinder::volume() const //����Բ�������
{return Circle::area()*height;}

//Cylinder���ʵ��
ostream& operator<<(ostream&output, const Cylinder& cy)
{   
   output<<"Center=["<<cy.x<<","<<cy.y<<"],r="<<cy.radius
                                   <<",h="<<cy.height<<"\n area="<<cy.area( )
                                   <<",volume="<<cy.volume( )<<endl;
   return output;
}
