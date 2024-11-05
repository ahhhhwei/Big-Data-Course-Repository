#include <iostream>
using namespace std;
class myString{
public: 
//根据测试程序写构造函数原型

void display() const; //显示字符串
void input(); //输入字符串
int len() const ;//求字符串长
//补充下标重载运算
int  operator==(const myString& a,const myString& b); //字符串等于比较
int  operator>(const myString& a,const myString& b); //字符串大于比较
myString operator+(const myString& a,const myString &b); //字符串拼接

//补充赋值重载运算
//补充析构函数
private:
   char *str;
   int size;
};

//考虑为myString添加输入输出流重载