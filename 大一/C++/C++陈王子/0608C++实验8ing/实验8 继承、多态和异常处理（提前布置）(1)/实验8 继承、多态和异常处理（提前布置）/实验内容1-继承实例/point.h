#ifndef  POINT_H
#define POINT_H
#include <iostream>
using namespace std;
//Point������� point.h
class Point{
public:
  Point(float x=0,float y=0);//��Ĭ�ϲ����Ĺ��캯��
  void setPoint(float,float); //��������ֵ
  float getX ( ) const {return x;} //��x����
  float getY ( ) const {return y;} //��y����
  friend ostream& operator<<(ostream&,const Point &);//�������
protected: //�ܱ�����Ա
  float x,y;     };
#endif
