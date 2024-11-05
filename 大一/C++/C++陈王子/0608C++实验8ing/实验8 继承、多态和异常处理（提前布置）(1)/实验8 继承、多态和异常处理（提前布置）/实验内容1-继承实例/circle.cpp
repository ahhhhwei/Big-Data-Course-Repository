#include "pch.h"
#include "circle.h"
//Circle类的实现 circle.cpp
Circle::Circle(float a,float b,float r):Point(a,b),radius(r){ }
void Circle::setRadius(float r) //设置半径值
{radius=r;}
float Circle::getRadius( ) const//读取半径值
 {return radius;}
float Circle::area( ) const//计算圆面积
{return 3.14159*radius*radius;}
ostream& operator<<(ostream&output,const Circle &c)
{output<<"Center=["<<c.x<<","<<c.y<<"],r="<<c.radius<<",area="<<c.area( )<<endl;
return output;
}
