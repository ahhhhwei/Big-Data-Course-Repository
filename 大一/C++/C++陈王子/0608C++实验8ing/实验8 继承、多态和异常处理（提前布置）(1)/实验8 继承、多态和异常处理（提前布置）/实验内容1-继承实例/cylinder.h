#ifndef CYLINDER_H
#define CYLINDER_H
#include "circle.h"
//Cylinder������� cylinder.h
class Cylinder:public Circle{
public:
    Cylinder (float x=0,float y=0,float r=0,float h=0);//���캯��
    void setHeight(float); //����Բ����
    float getHeight( ) const; //��ȡԲ����
    float area( ) const; //����Բ�����
    float volume( ) const; //����Բ�����
    friend ostream& operator<<(ostream&,const   Cylinder&);//������������
protected:
    float height; //Բ����
};
#endif