#include <iostream>
#include <cstring> //需要使用到 C++ 字符串库
using namespace std;

//student2.h
class Student {
public:
    Student(); //默认构造函数
    Student(char* n); //带参数构造函数
    Student(const Student& other); //复制构造函数
    void operator=(const Student& right); //重载赋值运算符
    ~Student(); //析构函数
    char* GetName(); //获取名字
    void  ChangeName(char* n); //改名
private:
    char* name;
};


//student2.cpp
Student::Student() { //默认构造函数
    name = new char[1]; //在堆上为 name 分配一个字节的空间
    *name = '\0'; //将 name 的第一个字节设为空字符
}

Student::Student(char* n) { //带参数构造函数
    int length = strlen(n); //获取字符串 n 的长度
    name = new char[length + 1]; //在堆上为 name 分配长度为 length 加 1 的空间
    strcpy(name, n); //将字符串 n 复制到 name 中
}

Student::Student(const Student& other) { //复制构造函数
    int length = strlen(other.name); //获取 other 的名字长度
    name = new char[length + 1]; //在堆上为 name 分配长度为 length 加 1 的空间
    strcpy(name, other.name); //将 other 的名字复制到 name 中
}

void Student::operator=(const Student& right) { //重载赋值运算符
    if (this != &right) { //判断是否自己给自己赋值
        delete[] name; //先将自己原来的 name 内存释放掉
        int length = strlen(right.name); //获取 right 的名字长度
        name = new char[length + 1]; //在堆上为 name 分配长度为 length 加 1 的空间
        strcpy(name, right.name); //将 right 的名字复制到 name 中
    }
}

Student::~Student() { //析构函数
    delete[] name; //将 name 内存释放掉
}

char* Student::GetName() { //获取名字
    return name;
}

void Student::ChangeName(char* n) { //改名
    int length = strlen(n); //获取字符串 n 的长度
    delete[] name; //将原来的 name 内存释放掉
    name = new char[length + 1]; //在堆上为 name 分配长度为 length 加 1 的空间
    strcpy(name, n); //将字符串 n 复制到 name 中
}


//StudentApp.cpp
int main()
{
    Student stu1, stu2("Jennie Mao"), stu3(stu2), stu4("John Smith"); //创建四个学生，分别使用默认构造函数、带参数构造函数和复制构造函数
    cout << "stu1:" << stu1.GetName() << endl; //输出 stu1 的名字
    cout << "stu2:" << stu2.GetName() << endl; //输出 stu2 的名字
    cout << "stu3:" << stu3.GetName() << endl; //输出 stu3 的名字
    cout << "stu4:" << stu4.GetName() << endl; //输出 stu4 的名字

    stu1 = stu4; //使用赋值运算符将 stu1 的名字改成 stu4 的名字

    cout << "stu1:" << stu1.GetName() << endl; //输出 stu1 的名字

    stu1.ChangeName("Peter"); //将 stu1 的名字改成 Peter
    cout << "stu1:" << stu1.GetName() << endl; //输出 stu1 的名字

    stu3.ChangeName("Tom"); //将 stu3 的名字改成 Tom
    cout << "stu3:" << stu3.GetName() << endl; //输出 stu3 的名字

    return 0;
}