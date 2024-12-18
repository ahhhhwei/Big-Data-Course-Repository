#include"Vector.hpp"
int main()
{
	//各种测试
	Vector<char> c;
	if (c.empty())
	{
		cout << "Vector<char> c 是空的" << endl;
	}
	char str[] = "I love C++!";
	for (size_t i = 0; i < strlen(str); ++i)
	{
		c.push_back(str[i]);
	}
	for (size_t i = 0; i < c.size(); ++i)
	{
		cout << c.at(i);
	}
	cout << endl;
	c.pop_back();
	for (size_t i = 0; i < c.size(); ++i)
	{
		cout << c[i];
	}
	cout << endl;

	cout << "front():" << c.front() << endl << "back():" << c.back() << endl;

	Vector<char> s;
	char s1[] = "You love Java!";

	for (size_t i = 0; i < strlen(s1); ++i)
	{
		s.push_back(i);
	}
	if (s < c)
	{
		cout << "s<c" << endl;
	}
	Vector<int> v(1);
	for (size_t i = 1; i < 10; ++i)
	{
		v.push_back(i);
	}
	v.pop_back();
	for (size_t i = 0; i < v.size(); ++i)
	{
		cout << v[i] << ' ';
	}
	cout << endl;

	Vector<int> vcopy;
	for (size_t i = 0; i < 9; i++)
	{
		vcopy.push_back(i);
	}

	if (v == vcopy)
	{
		cout << "v和vcopy相等" << endl;
	}
	return 0;
}