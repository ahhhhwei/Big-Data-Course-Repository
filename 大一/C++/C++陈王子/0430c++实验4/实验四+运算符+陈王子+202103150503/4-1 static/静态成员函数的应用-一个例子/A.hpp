#include <iostream>
using namespace std;

class A{
public:
	A(){cout<<"�޲ι��죺"<<endl;   c++;}
	A(const A& other){cout<<"�������죺"<<endl;c++;}
	void ff(A obj)
	{	cout<<"ff:";
                		obj.get_obj_num();
	 }
	A gg()
	{	return (*this);
	}
	void get_obj_num()
	{	cout<<c<<endl;
	}
	~A()
	{	c--;
	}
private:
	static int c;
};