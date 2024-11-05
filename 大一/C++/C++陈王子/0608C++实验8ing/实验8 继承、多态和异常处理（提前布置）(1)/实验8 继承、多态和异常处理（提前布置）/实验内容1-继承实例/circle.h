#ifndef CIRCLE_H
#define CIRCLE_H
#include "point.h"
//Circle类的声明  circle.h
class Circle:public Point {
public:
  Circle(float x=0,float y=0,float r=0); //构造函数
  void setRadius(float); //设置半径值
  float getRadius( ) const; //读取半径值
  float area ( ) const; //计算圆面积
  friend ostream& operator<<(ostream&,const Circle &);
protected:
  float radius;
};
#endif