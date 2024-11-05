#  C++期中

题型：

判断题（1*10）

选择题（2*10）

阅读题（5*8）

程序填空（2*9）

程序设计（12）



**选择**

```c++
class A{
public:
private:
};
//空的类定义没问题
class B{
public:
    void fun(int xv):x(xv){
        std::cout<<x<<std::endl;
    }
private:
    int x;
};
//错误：在函数参数后面使用冒号进行初始化，这种方式只适用于构造函数 B(int xv):x(xv){}


class C{
public:
void set(int xv)const{
x=xv; }
private:
int x;
};
//错误，set 函数被声明为 const，但是该函数会修改类的成员变量 x，违反了 const 的语义

int main(){
	fun(3);
	fun(3.1,7.1);
	fun('C');
}
A、
fun的原型可能是 void fun(int,int =0)
B、
fun的原型可能是 int fun(char,char='\0'）;
C、
fun的原型可能是 char fun(double,double=0.0)
D、
A、B、C都有可能
//答案D

                  
                  
                  
以下主函数使用了自定义类型xarray的输出流运算，那么对于为xarray重载输出流运算符，以下说法错误的是：
int main(){
    char str[20]="hello world";
    Xarray xobj(str,3,7),yobj(xobj);
    cout<<xobj;
    cout<<yobj;
}

A重载原型可以是:void operator<<(ostream& out,Xarray xobj);
B重载原型可以是:ostream operator<<(ostream& out,Xarray& xobj):
C重载原型可以是:ostream& operator<<(const ostream& out,Xarray& xobj);
D重载原型可以是:int operator<<(ostream& out,const Xarray& xobj);   
//正确答案C，输出流对象 out 被声明为 const ostream& 类型，这意味着调用该操作符时不能修改对应的输出流对象。然而，输出流操作通常会修改输出流对象

                  
                  
                  
                  
class A {
public:
    A(int vx) : x(vx) {}
    int getx() { return x; }
private:
    int x;
};

class B {
public:
    void fun(A& xobj) {
        xobj.x = xobj.getx() + 1;
    }
};
在使用时遇到访问xobj.x非法的问题，那么下列解决方案不正确的是：
A.可以在A定义中添加声明：friend class B
B.可以在B定义中添加声明：friend class A//B 类并没有直接访问 A 类中的私有成员的需求，友元单向性
C.可以在A定义中添加声明：friend void B:fun(A& xobj)
D.可以在A定义中将数据成员x的访问控制修改为public
                  
                  
                  

假设已经声明pool类，且类型A的数据成员描述如下。下列哪那个用法没有任何语法错误：
class A{
public:
//选项添加区域
private:
static int x;
pool cir;
};

A、可以为A添加拷贝构造函数如下:
A(const A& obj){
  x++;
  cir=obj.cir;
 }//正确
B、可以为A添加静态成员函数如下:
static double StaticFun() {  
   return x+cir.area(); 
}//cir 对象属于类 A 的非静态成员，无法在静态成员函数 StaticFun 中进行调用。
C、可以为A添加常成员函数如下:
pool ConstFun() const{  
  pool temp(x++,3.5);  
  return temp;   
}//A类声明中有一个static int，表示数据类型应该是整数类型，而C选项传递了一个浮点数3.5
D、可以为A添加构造函数如下:
A(int vx):cir(vx,5),x(vx)
{   }//构造函数参数为 int 型数据，然而 cir 是一个 pool 类型，不匹配的数据类型无法进行成员初始化列表的操作
                  
                  
                  
6、假设Animal是只包含一个数据成员char *Name和只定义了五个成员函数的类。其中，有如下三个构造函数：
Animal() ;
Animal(const char*);
Animal(const Animal&);
第四个是该类的一个公有成员：char* getAnimalName（）const;
第五个析构函数对应的实现为：
~Animal(){delete[]Name;}
那么以下主函数中可能出错的是：
A、
int main() {
 Animal Cat("Tom"),Tiger(Cat);
     cout<<Tiger.getAnimalName()<<endl;
}//首先通过 "Tom" 字符串初始化了一个 Animal 类对象 Cat，然后创建了一个名为 Tiger 的新对象并使用 Cat 对象进行拷贝构造，最后输出了 Tiger 对象的名字属性，
B、
int main() {
    Animal Cat("Tom"),*Ptiger=new Animal(Cat.getAnimalName());
     cout<<Ptiger->getAnimalName()<<endl;
}//首先通过 "Tom" 字符串初始化一个 Animal 类对象 Cat，然后调用 Cat.getAnimalName() 获取对象的名字字符串（const char* 类型），进而创建一个名为 Ptiger 的动态分配指针，该指针指向新创建的 Animal 类对象，对象的名字字符串与 Cat 对象一样。在程序最后输出 Ptiger 指针所指对象的名字字符串属性。
C、
int main() {
Animal Cat("Tom"),&Rtiger=Cat;
cout<<Rtiger.getAnimalName()<<endl;
}//首先通过字符串 "Tom" 初始化一个 Animal 类对象 Cat，随后定义了一个 Animal 类型的引用 Rtiger 并将其指向 Cat 对象。最后输出 Rtiger 所指对象的名字属性
D、
int main() {
   Animal Cat("Tom"),Tiger;
     Tiger=Cat;
     cout<<Tiger.getAnimalName()<<endl;
}//错误，通过 "Tom" 字符串初始化了一个 Animal 类对象 Cat，然后创建了一个名为 Tiger 的新对象并将其初始化为对象 Cat 的副本（使用 operator= 进行赋值拷贝），最后输出了 Tiger 对象的名字属性。这段代码的问题在于没有正确处理 Name 字符串的拷贝问题，导致 Tiger 和 Cat 对象共享同一块内存空间，可能会导致内存错误或者数据混乱。 默认合成的赋值拷贝运算符通常逐个复制对象中的所有非静态成员变量，这对于大多数类来说都是足够好的。但在以下情况下，会出现默认合成的赋值拷贝运算符无法完成正确的深拷贝：对象中有指针类型的成员变量，并且这些指针指向的是动态分配的内存区域。此时需要手动编写赋值拷贝函数，实现深度拷贝，避免多个对象共享同一块内存区域导致内存错误或数据混乱。
```

```c++
class A{
    A(int xv){
        x=xv;
    }
    int x;
};

class B{
  int x;
    public:
    B(int xv=4):x(xv){
        return;
    }
};

class C{
    public:
    C(const C& obj){
        x=obj.x;
    }
    private:
    int x;
};
```





以下主函数描述了对一个自定义类型xarray的使用，根据这个使用情况，以下说法正确的是：

```c++
int main()
{
char str[10]="hello world";
Xarray xobj(str,3,9),yobj(xobj);
Xarray *pointer;
pointer=&yobj;
cout<<(*pointer);
return 0;
}
/*
A、
Xarray 必须要写拷贝构造函数;
B、
Xarray 必须要写输出流重载函数;
C、
Xarray 必须要写&地址运算符重载函数;
D、
Xarray 必须要写析构函数;
*/

答案为B
```



```c++
class A{
    public:
    A(int vx=0){x=vx;}
    int getx(){return x;}
    void set(int vx){x=vx;}
    private:
    int x;
};
int main(){
    A a(5),b(6),&p=b;
    p.set(5);
}


以下程序使用Xfun接收类型A的obj，保证obj的值不变的 Xfun 设计错误的是：
int main(){
    A objx(5);
    Xfun(objx);
}
A、
void Xfun(A objx);
B、
void Xfun(const A& objx);
C、
void Xfun(A& objx) const;
D、
void Xfun(const A objx);





int fun(int a=0,int b=0){
    cout<<a+b<<endl;
}
template<class T> T fun(T x=0,T y=0){
    cout<<x<<endl;
}
A、
如有函数调用fun(3u); 则调用的是2)
B、
如有函数调用fun(‘3’,’1’);则调用的是1)
C、
如有函数调用fun(‘e’,’f’);则调用的是2)
D、
如有函数调用fun(3,’x’);则调用的是1)

    
    
  





```



阅读题

```c++
#include <iostream>
using namespace std;

class Rectangle { // 定义一个名为 Rectangle 的类
public:
    // 构造函数：初始化矩形的长和宽（如果不传参，长和宽默认值为 10）
    Rectangle(int x = 10, int y = 10) : length(x), width(y) {}

    // 计算矩形的面积
    int area() const { return length * width; }
private:
    int length; // 矩形的长
    int width;  // 矩形的宽
}; 

// 计算矩形面积的函数，参数为矩形的常量引用
int area(const Rectangle& b) {
    return b.area();
}

int main() {
    Rectangle a(20, 30), b(30), c, d(a); // 创建四个 Rectangle 对象，分别使用不同的构造函数参数
    cout << "area of a: " << a.area() << endl; // 输出 a 对象的面积
    cout << "area of b: " << b.area() << endl; // 输出 b 对象的面积
    cout << "area of c: " << c.area() << endl; // 输出 c 对象的面积
    cout << "area of d: " << area(d) << endl; // 输出 d 对象的面积
    return 0;
}
结果：
area of a:600
area of b:300
area of c:100
area of d:600


    
    
    
#include<iostream>
using namespace std;

// 定义一个名为 A 的类
class A {
public:
    // 默认构造函数，初始化 a 和 b 的值为 0
    A() { a = b = 0; cout << "Default constructor.\n"; }
    // 带参数的构造函数，初始化 a 和 b 的值为传入的参数
    A(int i, int j = 5) { a = i, b = j; cout << "Constructor.\n"; }
    // 析构函数，输出一条信息
    ~A() { cout << "Destructor.\n"; }
    // 输出 a 和 b 的值
    void print() { cout << "a=" << a << ", b=" << b << endl; }
private:
    int a, b; // 成员变量：a 和 b
};

int main() {
    A m(15, 18); // 创建一个 A 对象 m，使用带参数的构造函数
    m.print(); // 输出 m 对象的 a 和 b 值

    A n; // 创建一个 A 对象 n，使用默认构造函数
    n.print(); // 输出 n 对象的 a 和 b 值

    m = 12; // 改变 m 对象的 a 值为 12
    m.print(); // 输出 m 对象的 a 和 b 值

    return 0;
}
结果：
Constructor.
a=15, b=18
Default constructor.
a=0, b=0
Constructor.
Destructor.
a=12, b=5
Destructor.
Destructor.


    
#include<iostream>
using namespace std;

// 定义一个函数模板 outputArray，用于输出任意类型的数组元素
template<class T>
void outputArray(const T* Parray, int count) {
    for (int i = 0; i < count; i++) {
        cout << Parray[i] << ",";
    }
    cout << endl;
}

int main() {
    int M[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    outputArray(M, 5); // 输出 M 数组中前 5 个元素

    char N[] = "I love you!";
    outputArray(N + 2, 7); // 输出 N 数组从第 3 个元素开始的后 7 个元素

    return 0;
}
结果：
1,2,3,4,5,
l,o,v,e, ,y,o,







#include<iostream>
using namespace std;

class Myclass {
private:
    char ch;

public:
    // 默认构造函数，将 ch 的值设置为 'A'
    Myclass() { ch = 'A'; cout << "default cons:" << ch << endl; }

    // 带参数的构造函数，将 ch 的值设置为 c
    Myclass(char c) { ch = c; cout << "cons:" << ch << endl; }

    // 拷贝构造函数，将 ch 的值设置为 x.ch，并输出一条信息
    Myclass(const Myclass& x) { ch = x.ch; cout << "copy cons:" << x.ch << endl; }

    // 赋值运算符重载函数，将 ch 的值设置为 x.ch，并输出一条信息
    Myclass& operator=(Myclass x) {
        ch = x.ch;
        cout << "op=:" << 'B' << endl;
        return *this;
    }

    // 成员函数 set，用于修改 ch 的值为 c
    void set(char c) { ch = c; }

    // 析构函数，输出一条信息
    ~Myclass() { cout << "des:" << ch << endl; }
};

// 返回类型为 Myclass 的函数 fun，修改 Obj 的值并返回其本身
Myclass fun(Myclass& Obj) {
    Obj.set('F');
    return Obj;
}

int main() {
    Myclass obj1, obj2('D'), obj3(obj1); // 创建三个 Myclass 对象并初始化

    obj3.set('H'); // 修改 obj3 的值为 'H'

    Myclass *p;
    p = new Myclass(obj3); // 使用 obj3 的值创建一个动态分配的 Myclass 对象

    fun(*p).set('G'); // 调用函数 fun 并设置其返回值的成员变量为 'G'

    delete p; // 释放动态分配的内存

    obj1 = obj2; // 将 obj2 的值赋给 obj1

    return 0;
}

参考解答：

default cons:A    //0.5

cons:D            //0.5

copy cons: A     //0.5

copy cons: H     //0.5

copy cons: F     //1

des:G             //1

des:F             //1

copy cons: D    //0.5

op=B              //0.5

des:D             //0.5

des:H             //0.5  

des:D             //0.5

des:D             //0.5



    
    



//程序的结果整理后的程序如下：
#include<iostream>
#include<cstring>
using namespace std;

class Test{
    char s[10];
    int n;
public:
    Test(const char *t = "none", int b = 1);
    Test set(const char* t);
    ~Test();
};

Test::Test(const char *t, int b) : n(b){
    strcpy(s, t);
    cout << "Construct: " <<s<<" "<< n << endl;
}

Test Test::set(const char* t){
    Test temp(strcat(s, t), 2);
    return temp;
}

Test::~Test(){
    cout << "Destruct: " <<s<<" "<< n << endl;
}

int main(){
    Test a("Rosemary", 10), b("Rose"), c;
    b = c.set("ABC");
    return 0;
}


Construct: Rosemary 10  //0.5分
Construct: Rose 1       //0.5分
Construct: none 1       //1分
Construct: noneABC 2    //1分
Destruct: noneABC 2     //1分
Destruct: noneABC 2     //1分
Destruct: noneABC 1     //1分
Destruct: noneABC 2     //1分
Destruct: Rosemary 10   //1分
    
    
    
    
    
    
    
    


//整理后的程序如下：

#include <iostream>
using namespace std;

class Sample{
    int x;
    static int y;
public:
    Sample(int a);
    void print();
};

int Sample::y = 25;

Sample::Sample(int a){
    x = a;
    y++;
}

void Sample::print(){
    cout << "x=" << x << endl;
    cout << "y=" << y << endl;
}

int main(){
    Sample sl(5);
    Sample s2(10);
    sl.print();
    s2.print();
    return 0;
}

x=5

y=27

x=10

y=27
    
    
    

    

//整理后的程序如下：

#include<iostream>
using namespace std;

class A {
    int a;
public:
    A(int i = 1) {
        a = i;
        cout << "ACons: " << a << endl;
    }
    int get() { return a + 3; }
    void show() { cout << a << endl; }
    ~A() { cout << "ADes: " << a << endl; }
};

class B{
    A a, b;
public:
    B(int i, int j) : a(i-j), b(i+j) {
        cout << "Bcons" << endl;
    }
    void show() {
        a.show();
        b.show();
    }
    ~B() {
        cout << "BDes: " << endl;
    }
};

int main(){
    B* pb = new B(2, 4);
    A obj[2] = { A(5) };
    cout << obj[1].get() << endl;
    pb->show();
    delete pb;
    return 0;
}


ACons:6  //0.5分

ACons:-2 //0.5分

BCons //0.5分

ACons:5  //0.5分

ACons:1  //0.5分

4   //0.5分

-2  //0.5分

6    //0.5分

Bdes  //0.5分

ADes:-2  //1分

ADes:6   //1分

ADes:1   //1分

ADes:5   //0.5分
    
    
    
    
    

//整理后的程序如下：

#include<iostream>
using namespace std;

class complex {
public:
    complex(int r = 0, int i = 0) : real(r), image(i) { }
    int operator*(const complex& right) {
        return (real * right.real) + (image * right.image);
    }
    operator char() { return char(real + image); }
private:
    int real, image;
};

void funTest(const int& x, const int& y) {
    cout << "funTest1: " << x + y << endl;
}

void funTest(char x, char y) {
    cout << "funTest2: " << x - y << endl;
}

template<class T>
void funTest(T x, T y) {
    cout << "funtest3: " << x * y << endl;
}

int main() {
    complex c(3, 4), d(50);
    char y = 'a';
    funTest(2, 3);
    funTest('a', 'A');
    funTest(12.5, 0.8);
    funTest(c, d);
    funTest(100, 97.3);
    funTest(y, c);
    return 0;
}

funTest1:5    //1分

funTest2:32   //1分

funtest3:10   //1分

funtest3:150  //1分

funTest1:197  //2分

funTest2:90   //2分
    
    
//整理后的程序如下：

#include <iostream>
using namespace std;

class DemoB;
class DemoA {
public:
    DemoA(int vx) : x(vx) { cout << "ACons: " << x << endl; }
    DemoA(const DemoA& obj) {
        x = obj.x;
        cout << "ACopy cons: " << x << endl;
    }
    int fun(int n, int m) {
        if(n == 0) return fun();
        if(n > 0) return fun(n - 1, m) * m;
        return 0;
    }
    ~DemoA() { cout << "ADes: " << x << endl; }
    friend void fun(DemoA objA, DemoB& objB);
private:
    int fun() { return x++; }
    int x;
};

class DemoB {
public:
    DemoB(int vx) : x(vx - 1) { cout << "BCons: " << x << endl; }
    DemoB(const DemoB& obj) {
        x = obj.x;
        cout << "BCopy cons: " << x << endl;
    }
    ~DemoB() { cout << "BDes: " << x << endl; }
    friend void fun(DemoA objA, DemoB& objB);
private:
    int fun() { return ++x; }
    int x;
};

void fun(DemoA objA, DemoB& objB) {
    cout << (objA.fun() + objB.fun()) << endl;
}

int main(){
    DemoA obj1(5);
    DemoB obj2(5);
    cout << obj1.fun(2, 3) << endl;
    fun(obj1, obj2);
    return 0;
}

ACons:6

BCons:4

54

ACopy Cons:7

12

ADes:8

BDes:5

ADes:7
    

    

```

**程序题**

1、有以下myInteger类声明描述的框架，它尝试定义一个自己的整型类。现在请你按照提示完善它，并给出相关的实现：

请给出：6）8）9）4分每题，其他2分1题
1）重载后置增量运算符的声明
2）输出流重载的友元声明和输入流重载的友元声明
3）输入流重载声明
4）大千关系运算符重载声明
5）构造函数的实现
6）+运算重载的实现
7）前置++的实现
8）后置++的实现
9）求相反数的实现
10)输出流重载的实现
11)输入流重载的实现
12)运算重载的实现

```c++
class myInteger {
public:
myInteger(double vx=0);
myInteger operator+(const myInteger& right); // 重载加运算,规则与int计算规则相同
myInteger operator++(); // 重载前置增量运算，规则与int计算规则相同
myInteger operator++(int); // 1)补充后置增量运算重载声明，规则与int计算规则相同
myInteger operator-(); // 重载求相反数，规则与int计算规则相同
friend ostream& operator<<(ostream& out, const myInteger& obj); // 2）补充输出流重载的友元声明和输出流重载的友元声明
friend istream& operator>>(istream& in, myInteger& obj); // 3)补充输入流重载声明//输入整数
bool operator>(const myInteger& right); // 4）补充大于关系运算符重载声明，规则与int计算规则相同
private:
int myint;
};

ostream& operator<<(ostream& out,const myInteger& obj); // 补充输出流重载的友元声明

istream& operator>>(istream& in,myInteger& obj); // 3)补充输入流重载声明//输入整数
```

1）重载后置增量运算符的声明：

```
myInteger operator++(int);
```
2）输出流重载的友元声明和输入流重载的友元声明：
```
friend ostream& operator<<(ostream& out, const myInteger& obj);
friend istream& operator>>(istream& in, myInteger& obj);
```
3）输入流重载声明：
```
istream& operator>>(istream& in,myInteger& obj);
```
4）大于关系运算符重载声明：
```
bool operator>(const myInteger& right);
```
5）构造函数的实现：
```C++
myInteger::myInteger(double vx) {
    myint = static_cast<int>(vx);
}
```
6）+运算重载的实现：
```C++
myInteger myInteger::operator+(const myInteger& right) {
    int temp = this->myint + right.myint;
    return myInteger(temp);
}
```
7）前置++的实现：
```C++
myInteger myInteger::operator++() {
    ++(this->myint);
    return *this;
}
```
8）后置++的实现：
```C++
myInteger myInteger::operator++(int) {
    myInteger temp(*this);
    ++(this->myint);
    return temp;
}
```
9）求相反数的实现：
```C++
myInteger myInteger::operator-() {
    return myInteger(-this->myint);
}
```
10）输出流重载的实现：
```C++
ostream& operator<<(ostream& out, const myInteger& obj) {
    out << obj.myint;
    return out;
}
```
11）输入流重载的实现：
```C++
istream& operator>>(istream& in, myInteger& obj) {
    in >> obj.myint;
    return in;
}
```
12）>运算重载的实现：

```C++
bool myInteger::operator>(const myInteger& right) {
    return this->myint > right.myint;
}
```



**老师补充程序题**

```c++
户籍管理部门为了便于管理辖区内人员，想要设计一个姓名类Name。现在有Name的部分设计框架及使用需求。请你按提示完善它。
#include <iostream>
#include <cstring>
using namespace std;
class Name{
public:
//1)根据使用给出构造函数的声明
//2)给出拷贝构造函数的声明
//3)给出赋值重载函数的声明
//4)给出下标重载声明
//5)给出姓名等于比较重载声明
//6)给出求平均姓名长度的成员函数AveLen声明
 //7)给出输入流重载的友元声明
 //8)给出其他必要的成员函数声明
void display(ostream& out) const
{    out<<name<<endl;   }
private:
char *name;
int size;
static int count; //姓名个数统计
};
istream& operator>>(istream& in,Name& obj);
//9)给出输出流重载声明
//10)给出count初始化定义
int main(){
Name per1("Chen Jiaqi"),per2("Han Ying"),per3(per1),per4;
//默认的名字为X
Name *person=new Name("Mike Li");
cout<<per1<<","<<per2<<","<<per3<<","<<per4<<endl;
per4=(*person);
cout<<per4<<endl;
cin>>per4;
cout<<per4<<endl;
cout<<Name::count<<endl;
cout<<Name::AveLen()<<endl;
per2[4]='P';
cout<<per2<<endl;
if(per1==per3)
cout<<"equal"<<endl;
else
cout<<"not equal"<<endl;
if(strcmp("Chen Jiami",per3)>=0)
cout<<"Bigger"<<endl;
else
cout<<"Smaller"<<endl;
delete person;
cout<<Name::AveLen()<<endl;
return 0;
}
请你完成1）-10）的工作和所有相关函数的实现。

```

这篇题解主要是对一个姓名类 Name 的各种声明和实现进行了总结和整理。它包括姓名类 Name 的构造函数、拷贝构造函数、赋值重载函数、下标重载函数、姓名等于比较重载函数、求平均姓名长度的成员函数，输入输出流重载函数等各个方面的声明和具体实现。除此之外，还给出了必要的成员函数声明、count 初始化定义等。

其中构造函数可以接受空指针或字符串类型的参数，拷贝构造函数用于复制一个姓名类对象，赋值重载函数用于赋值两个姓名类对象，下标重载函数用于访问姓名类对象内部存放姓名字符的数组，姓名等于比较重载函数用于比较两个姓名类对象的姓名是否相同，求平均姓名长度的成员函数是一个静态成员函数，用于计算所有姓名的平均长度，输入输出流重载函数用于输入和输出姓名类对象。

```c++


1)根据使用给出构造函数的声明 1分
.	
Name(const char* n=NULL);
.	
2)给出拷贝构造函数的声明 1分
.	
Name(const Name& obj);
.	
3)给出赋值重载函数的声明 1分
.	
Name& operator=(const Name& right);
.	
4)给出下标重载声明 1分
.	
char& operator[](int index);
.	
5)给出姓名等于比较重载声明 1分
.	
bool operator==(const Name& right);
.	
6)给出求平均姓名长度的成员函数AveLen声明 1分
.	
static double AveLen();
.	
7)给出输入流重载的友元声明 1分
.	
friend istream& operator>>(istream& in,Name& obj);
.	
8)给出其他必要的成员函数声明 2分
.	
operator char*();
~Name();

void display(ostream& out) const
{    out<<name<<endl;   }
private:
char *name;
int size;
static int count; //姓名个数统计
static int totalLen;//姓名总长（自行添加，也可以定义为全局变量）
};

istream& operator>>(istream& in,Name& obj);
.	
9)给出输出流重载声明
.	
ostream& operator <<(ostream& out,const Name& obj);

.	
10)给出count初始化定义
.	
int Name::count=0;
//int Name::totalLen=0;

.	
11) 3分
.	
Name::Name(const char* n=NULL){
    if(n==NULL) {
      size=1;
      name=new char[2];
      strcpy(name,"X");
   }
   else{
     size=strlen(n);
     name=new char[size+1];
     strcpy(name,n);
    }
     totalLen+=size;   
     count++;
}

.	
12) 2分
.	
Name::Name(const Name& obj){
     size=obj.size;
     name=new char[size+1];
     strcpy(name,n);
     totalLen+=size;
    count++;
}

.	
13) 3分
.	
Name& Name::operator=(const Name& right){
   if(this!=&right){
       delete []name;
       totalLen-=size;
       size=right.size;
       totalLen+=size;
       name=new char[size+1];
      strcpy(name,right.name);
   }
   return (*this);
}

.	
14)  2分
.	
char& Name::operator[](int index){
     if(index<0) return name[0];
     if(index>size) return name[size];
     return name[index];  
}

.	
15) 1分
.	
bool Name::operator==(const Name& right){
     return (strcmp(name,right.name)==0);
}

.	
15) 2分
.	
static double Name::AveLen(){
    if(count==0) return 0;
    return totalLen/count;   
}

.	
16) 1分
.	
Name::operator char*(){
   return name;
}


.	
17)  2分
.	
~Name(){
   delete []name;
   name=NULL;
   totalLen-=size;
   count--;
}

.	
18) 2分
.	
istream& operator>>(istream& in,Name& obj){
    char str[200];
    in.getline(str,200);
    totalLen-=size;
    if(name!=NULL) delete []name;
    obj.size=strlen(str);
    obj.name=new char[obj.size+1];
    strcpy(obj.name,str);
    size=obj.size;
    totalLen+=size;
    return in;
}

.	
19) 1分
.	
ostream& operator <<(ostream& out,const Name& obj);\{
    obj.display(out);
    return out;
}

```



**第一套程序题**

有如下主函数，用于计算直角坐标系中点分布的密集程度。我们设计一个简单的点密度的计算方法，即定义密度系数k=区域面积/区域内点的个数。

区域面积是一个矩形，以分布点的最左最右最上最下坐标值经过的与X轴和Y轴平行的直线合拢构成的矩形为计算的区域面积。

我们命名直角坐标系中的点为Point。具体主函数如下：

```c++
#include<iostream>

#include<cmath>

#include “Point.hpp”  // 引入头文件 Point.hpp，可能是定义 Point 类的头文件

using namespace std;

int main(){

    // 定义四个点对象，默认位于原点位置
    Point x1, x2(2, 3), x3(4), x4(-2, -7);

    Point *px;  // 定义一个 Point 类型的指针变量 px

    double Left, Right, Up, Down, Area;  // 存储合围矩形的最左、最右、最上、最下坐标值和矩形面积
    int Count;  // 存储所有点的个数

    // 调用 Point 类中的静态成员函数，并将返回值赋给相应的变量
    Left = Point::Left;
    Right = Point::Right;
    Up = Point::Up;
    Down = Point::Down;
    Area = Point::Parea();
    Count = Point::Pcount;

    // 输出矩形面积和点的总个数
    cout << "Area:" << Area << "|Count:" << Count << endl;

    // 输出面积和点个数的比值
    cout << "K1=" << Area / Count << endl;

    // 动态分配一个新的 Point 类对象, 并将其地址赋给 px 指针变量
    px = new Point(-3.5, 9.8);

    // 在屏幕上输出新创建的点的位置
    cout << (*px);  // 这里调用了 Point 类中的重载运算符<<

    // 输出所有点构成的凸包的面积和点的总个数的比值
    cout << "K2=" << Point::Parea() / Point::Pcount << endl;

    // 重新设置 px 指针所指向的点的位置
    px->set(99, -48);

    // 输出所有点构成的凸包的面积和点的总个数的比值
    cout << "K3=" << Point::Parea() / Point::Pcount << endl;

    delete px;  // 释放动态分配的内存空间

    if (x1 > x2)  // 判断点 x1 和 x2 的大小关系
        cout << "Bigger" << endl;  // 如果 x1 > x2，输出 Bigger
    else
        cout << "Smaller" << endl;  // 否则输出 Smaller

   // 计算点 x1 和 x3 之间的距离，并输出结果
   cout << "The distance of x1 and x3 is " << distance(x1, x3) << endl;

   return 0;
}

```

请给出

1）根据主函数的工作给出Point类的声明 和其他需要的类外函数的声明；（10分）

2）根据Point类的声明给出相关的类的实现。（20分）

下面是对程序进行注释说明：

根据主函数的工作可以看出，Point类需要实现以下功能：

1. 构造函数 Point(double vx=0, double vy=0)，支持多种初始化方式。
2. 成员函数 void set(double vx,double vy)，设置点的位置。
3. 静态成员函数 static double Parea()，计算点构成的所有矩形区域的面积。
4. 重载运算符 bool operator>(const Pointer& right)，判断两点距离。
5. 友元函数 ostream& operator<<(ostream& out,const Point& obj)，用于输出 Point 类对象。

而 Point 类外还需要实现以下的函数：

1. 友元函数 ostream& operator<<(ostream& out,const Point& obj) 的定义。
2. 函数 double distance(const Point& left,const Point& right) 的声明和定义。

1. Point 声明

```c++
Copy Codeclass Point{
public:
    Point(double vx=0,double vy=0);  // 构造函数，支持多种初始化方式
    void set(double vx,double vy);  // 设置点的位置
    static double Parea();  // 静态成员函数：计算点构成的所有矩形区域的面积
    bool operator>(const Pointer& right);  // 重载运算符>, 判断两点距离
    friend ostream& operator<<(ostream& out,const Point& obj);  // 友元函数，用于输出 Point 类对象
    // 公有静态数据成员
    static double Left, Right, Up, Down;  // 点构成的所有矩形区域的最左、最右、最上、最下坐标值
    static int Pcount;  // 点的总个数
private:  
    double x, y;  // 点的横纵坐标
};
// 友元函数，用于输出 Point 类对象
ostream& operator<<(ostream& out,const Point& obj);
// 函数，计算两点之间的距离
double distance(const Point& left,const Point& right);
```

2.Point 相关实现

```c++
Copy Code// 静态成员变量初始化
double Point::Left = 0;
double Point::Right = 0;
double Point::Up = 0;
double Point::Down = 0;
int Point::Pcount = 0;

// 构造函数
Point::Point(double vx, double vy): x(vx), y(vy){
    Pcount++;  // 点数加1
    if(Pcount == 1){  // 第一个点，用它的坐标设置矩形坐标
        Left = Right = x;
        Up = Down = y;
    } else {  // 其他点的坐标更新矩形坐标
        if(x < Left) Left = x;
        if(x > Right) Right = x;
        if(y < Down) Down = y;
        if(y > Up) Up = y;
    }
}

// 设置点的位置
void Point::set(double vx, double vy){
    x = vx;
    y = vy;
    if(x < Left) Left = x;
    if(x > Right) Right = x;
    if(y < Down) Down = y;
    if(y > Up) Up = y;
}

// 静态成员函数，计算点构成的所有矩形区域的面积
static double Point::Parea(){
    return (Right - Left) * (Up - Down);
}

// 重载运算符>, 判断两点距离
bool Point::operator>(const Pointer& right){
    Point temp;  // 创建一个临时变量 temp
    return distance(*this, temp) > distance(right, temp);  // 返回两点距离谁大
}

// 友元函数，用于输出 Point 类对象
ostream& operator<<(ostream& out,const Point& obj){
    out << "(" << obj.x << "," << obj.y << ")" << endl;  // 格式化输出
    return out;
}

// 函数，计算两点之间的距离
double distance(const Point& left,const Point& right){
    double res;
    res=sqrt((left.x-right.x)*(left.x-right.x)+(left.y-right.y)*(left.y-right.y));
    return res;
}
```



