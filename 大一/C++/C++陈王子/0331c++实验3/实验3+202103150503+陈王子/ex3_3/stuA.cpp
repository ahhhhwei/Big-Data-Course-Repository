#include <iostream>
using namespace std;

//student1.h
class Student {
public:
    Student();//考虑这里为什么不缺省无参构造?
    Student(char* n);
    //Student(const Student & other);
    //Student& operator=(const Student& right);  
    //~Student( );
    char* GetName();  //获取名字
    void  ChangeName(char* n);  //改名
private:
    char name[20];
};

//student11.cpp
Student::Student() {
    name[0] = '\0';
}

Student::Student(char* n)
{
    int i;
    for (i = 0; n[i] != '\0'; i++)
        name[i] = n[i];
    name[i] = '\0';
}


char* Student::GetName()
{
    return name;
}

void Student::ChangeName(char* n)
{
    int i;
    for (i = 0; n[i] != '\0'; i++)
        name[i] = n[i];
    name[i] = '\0';
}



//StudentApp.cpp
int main()
{
    Student stu1, stu2("Jennie Mao"), stu3(stu2), stu4("John Smith");
    cout << "stu1:" << stu1.GetName() << endl;
    cout << "stu2:" << stu2.GetName() << endl;
    cout << "stu3:" << stu3.GetName() << endl;
    cout << "stu4:" << stu4.GetName() << endl;

    stu1 = stu4;

    cout << "stu1:" << stu1.GetName() << endl;

    stu1.ChangeName("Peter");
    cout << "stu1:" << stu1.GetName() << endl;

    stu3.ChangeName("Tom");
    cout << "stu3:" << stu3.GetName() << endl;

    return 0;
}