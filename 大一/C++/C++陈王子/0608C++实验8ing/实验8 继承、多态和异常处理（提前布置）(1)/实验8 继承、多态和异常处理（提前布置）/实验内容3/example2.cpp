#include <iostream>
#include <string>
using namespace std;
class Student{
public:
	Student(int n,string nam)//定义构造函数
	{
		cout<<"构造"<<nam<<endl;
		num=n;
		name=nam;
	}
        Student(const Student& obj)//定义拷贝构造函数
	{
		name=obj.name;
                num=obj.num;
                cout<<"拷贝构造"<<name<<endl;		
	}
	~Student(){
		cout<<"析构"<<name<<endl;
	}
	void get_data();
private:
	int num;
	string name;
};

void Student::get_data() //定义成员函数
{
if(num==0) throw num; //如num=0,抛出int型变量num
else
	cout<<num<<" "<<name<<endl; //若num≠0，输出num,name
}
void fun1(Student stud) {
	stud.get_data();
	cout << "fun1" << endl;
}

void fun2(Studnet& stud) {
	stud.get_data();
	cout << "fun2" << endl;
}

void fun0( )
{Student stud1(1101,"Tan"); //建立对象stud1
stud1.get_data( ); //调用stud1的get_data函数
Student stud2(0,"Li"); //建立对象stud2
stud2.get_data( ); //调用stud2的get_data函数
cout << "fun0" << endl;
}

Student stud1(1101,"Tan");
Student stud2(0,"Li"); //建立对象stud2

int main( )
{
try{//调用fun函数
	//fun0();
	//fun1(stud1); 
	//fun2(stud2);
} 
catch(int n){//表示num=0出错
	cout<<"num="<<n<<",error!"<<endl;
} 
return 0;
}