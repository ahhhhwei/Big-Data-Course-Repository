#include <iostream>
#include <string>
using namespace std;
class Student{
public:
	Student(int n,string nam)//���幹�캯��
	{
		cout<<"����"<<nam<<endl;
		num=n;
		name=nam;
	}
        Student(const Student& obj)//���忽�����캯��
	{
		name=obj.name;
                num=obj.num;
                cout<<"��������"<<name<<endl;		
	}
	~Student(){
		cout<<"����"<<name<<endl;
	}
	void get_data();
private:
	int num;
	string name;
};

void Student::get_data() //�����Ա����
{
if(num==0) throw num; //��num=0,�׳�int�ͱ���num
else
	cout<<num<<" "<<name<<endl; //��num��0�����num,name
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
{Student stud1(1101,"Tan"); //��������stud1
stud1.get_data( ); //����stud1��get_data����
Student stud2(0,"Li"); //��������stud2
stud2.get_data( ); //����stud2��get_data����
cout << "fun0" << endl;
}

Student stud1(1101,"Tan");
Student stud2(0,"Li"); //��������stud2

int main( )
{
try{//����fun����
	//fun0();
	//fun1(stud1); 
	//fun2(stud2);
} 
catch(int n){//��ʾnum=0����
	cout<<"num="<<n<<",error!"<<endl;
} 
return 0;
}