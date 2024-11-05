//Point类的实现 point.cpp
#include "pch.h"
#include "point.h"
Point::Point(float a,float b) //对x,y初始化
{ x=a;y=b;  }

//设置x和y的坐标值
void Point::setPoint(float a,float b) //为x,y赋新值
{x=a;y=b;    }

//重载输出运算符
ostream& operator<<(ostream&output,const Point &p)
{output<<"["<<p.x<<" "<<p.y<<"]"<<endl;
 return output; }
