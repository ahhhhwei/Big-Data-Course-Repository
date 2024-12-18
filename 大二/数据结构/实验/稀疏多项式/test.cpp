#include"Polynomial.hpp"
void test1()
{
	Data<int> d1;
	d1._power = 1;
	d1._val = 1;
	Data<int> d2;
	d2._power = 3;
	d2._val = 2;

	//p1: 2x^3 + 1x^1
	Polynomial<int> p1;
	p1.push_back(d1);
	p1.push_back(d2);
	cout << "p1: ";
	p1.display(cout);
	cout << endl;

	//p2:  4x^3
	Polynomial<int> p2;
	p2.push_back(d2);
	p2.push_back(d2);
	cout << "p2: ";
	p2.display(cout);
	cout << endl;

	cout << "测试+ ：" << endl;
	Polynomial<int> ret1;
	ret1 = p1 + p2;
	cout << "p1+p2的结果为: " << endl;
	ret1.display(cout);
	int data;
	cout << "请输入x的值:" << endl;
	cin >> data;
	cout << "表达式计算结果为" << ret1.cal(data) << endl << endl;


	cout << "测试- ：" << endl;
	Polynomial<int> ret2;
	ret2 = p1 - p2;
	cout << "p1-p2的结果为: " << endl;
	ret2.display(cout);
	cout << "请输入x的值:" << endl;
	cin >> data;
	cout << "表达式计算结果为" << ret2.cal(data) << endl << endl;


	cout << "测试* ：" << endl;
	Polynomial<int> ret3;
	ret3 = p1 * p2;
	cout << "p1*p2的结果为: " << endl;
	ret3.display(cout);
	cout << "请输入x的值:" << endl;
	cin >> data;
	cout << "表达式计算结果为" << ret3.cal(data) << endl << endl;
}
void test2()
{
	Polynomial<int> poly1;
	poly1.read(cin);
	cout << "poly1: ";
	poly1.display(cout);

	Polynomial<int> poly2;
	poly2.read(cin);
	cout << "poly2: ";
	poly2.display(cout);

	Polynomial<int> ret;
	ret = poly1 * poly2;
	cout << "*: ";
	ret.display(cout);
	
}
int main()
{
	test1();
	test2();
	return 0;
}