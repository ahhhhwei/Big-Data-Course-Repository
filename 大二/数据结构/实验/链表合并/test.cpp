#include"list.h"
void f(List<char> lt)
{
	cout << "���Կ������캯��" << endl;
}
int main()
{
	List<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	cout << "������" << lt.nodeCount() << "���ڵ�" << endl;
	lt.display(cout);
	if (lt.ascendingOrder())
	{
		cout << "������������" << endl;
	}
	else
	{
		cout << "��������������" << endl;
	}
	lt.erase(2);
	cout << "������" << lt.nodeCount() << "���ڵ�" << endl;
	lt.display(cout);
	lt.push_back(1);
	if (lt.ascendingOrder())
	{
		cout << "������������" << endl;
	}
	else
	{
		cout << "��������������" << endl;
	}
	List<int>* plt = new List<int>();
	List<int> lt1;
	lt1.push_back(2);
	lt = lt1;
	lt.display(cout);
	List<char> ltc;
	ltc.push_back('c');
	List<char> ltc1;
	ltc1.push_back('+');
	ltc1.push_back('+');
	ltc.ListMerge(ltc1);
	//ltc1.release();
	//f(ltc1);
	ltc.display(cout);
	cout << ltc.get(ltc.search('c')) << endl;

	List<int> lti;
	lti.push_back(1);
	lti.push_back(2);
	lti.push_back(3);
	lti.push_back(4);
	lti.pop_back();
	lti.display(cout);
	cout << lti.nodeCount() << endl;
	lti.reverse();
	lti.display(cout);
	cout << ltc;
	List<int> lti2;
	lti2.push_back(2);
	List<int> lti3;
	lti3.push_back(5);
	lti3.push_back(6);
	lti3.MergeList(lti, lti2);
	lti3.display(cout);
	List<char> ccc;
	for (size_t i = 0; i < 5; i++)
	{
		cout << "�����������ֵ:" << endl;
		cin >>  ccc;
	}
	cout << ccc;
	return 0;
}