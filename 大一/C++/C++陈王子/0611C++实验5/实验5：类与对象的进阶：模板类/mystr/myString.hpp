#include <iostream>
using namespace std;
class myString{
public: 
//���ݲ��Գ���д���캯��ԭ��

void display() const; //��ʾ�ַ���
void input(); //�����ַ���
int len() const ;//���ַ�����
//�����±���������
int  operator==(const myString& a,const myString& b); //�ַ������ڱȽ�
int  operator>(const myString& a,const myString& b); //�ַ������ڱȽ�
myString operator+(const myString& a,const myString &b); //�ַ���ƴ��

//���丳ֵ��������
//������������
private:
   char *str;
   int size;
};

//����ΪmyString����������������