//Point���ʵ�� point.cpp
#include "pch.h"
#include "point.h"
Point::Point(float a,float b) //��x,y��ʼ��
{ x=a;y=b;  }

//����x��y������ֵ
void Point::setPoint(float a,float b) //Ϊx,y����ֵ
{x=a;y=b;    }

//������������
ostream& operator<<(ostream&output,const Point &p)
{output<<"["<<p.x<<" "<<p.y<<"]"<<endl;
 return output; }
