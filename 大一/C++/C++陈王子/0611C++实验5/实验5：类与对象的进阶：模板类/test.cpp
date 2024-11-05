#include <iostream>
#include<cstring>
#include "mystring.hpp"
#include "myvector.hpp"
using namespace std;

//测试模板类的工作
int main()
{
char str[5][20]={"Today-","is-","a-","sunny-","day."};
myString astr;
int num,i;
cin>>num;  //5
myvector<mystring>  aStrSet(num), bStrSet(num-1),cStrSet;  //构建3个字符串（向量）集合


for(i=0;i<aStrSet.get_size();i++) cin>>aStrSet[i];  //输入若干个字符串到a     Today-   is-  a-  rainy-  day.

for(i=0;i<bStrSet.get_size();i++) cin>>bStrSet[i]; //输入若干字符串到b        Today- is-  my-  birthday.

cout<<"字符串集a的构成为："<<endl;
for(i=0;i<aStrSet.get_size();i++){
      cout<<aStrSet[i]; //增加myString的输出流运算支持，将字符串集合a 输出到屏幕上      
} //Today-is-a-rainy-day.
 cout<<endl;

cout<<"字符串集b的构成为："<<endl;
for(i=0;i<bStrSet.get_size();i++){
      cout<<bStrSet[i]; //将字符串集合b输出到屏幕上    
}//Today- is- my- birthday.
  cout<<endl;

cStrSet=aStrSet-bStrSet;
for(i=0;i<cStrSet.get_size();i++){ //将字符串集合a和b的差的结果输出到屏幕上
  cout<<cStrSet[i];
  cout<<endl;
}//a-rainy-day.

cStrSet.set_size(5);
for(i=0;i<5;i++)
   cStrSet[i]=str[i];
 
for(i=0;i<cStrSet.get_size();i++){ //将字符串集合c的结果输出到屏幕上
  cout<<cStrSet[i];  
}//Today-is-a-sunny-day.
cout<<endl;

for(i=0;i<cStrSet.get_size();i++) //将集合内的字符串拼接起来
   astr= astr + cStrSet[i]; 

cout<<astr; //显示拼接后的字符串 Today-is-a-sunny-day.
cout<<endl;

astr++; //定义myString的增量操作，将串内的每个字母循环调整为其后面的字母，如abc 调整为bcd；其他符号保持不变。
cout<<astr; //Upebz-jt-b-tvmmz-ebz.
cout<<endl;

cout<<strlen(astr); //定义myString的类型转换操作，使其可以使用strlen, 输出 21

return 0;
}