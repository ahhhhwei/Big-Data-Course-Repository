#include"Queue.hpp"

void yanghui(int n)
{
	cout << 1;
	Queue q;
	int s = 0, t = 1;
	q.enqueue(1);
	q.enqueue(1);
	for (int i = 1; i <= n; i++)
	{
		cout << endl;
		q.enqueue(0);
		for (int j = 1; j <= i + 2; j++)
		{
			t = q.Front();
			q.dequeue();
			q.enqueue(s + t);
			s = t;
			if (j != i + 2)
			{
				cout << s << ' ';
			}
		}
	}
}
void test1()
{
	int n = 0;
	cout << "请输入杨辉三角行数:" << endl;
	cin >> n;
	cout << endl;
	yanghui(n - 1);
}
void test2()
{
	Queue q;
	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);
	Queue r = q;
	Queue e(q);
	r.display(cout);
	r.display(cout);
}
int main()
{
	//修改这里的1 2分别测杨辉3角 和 队列的若干函数
	//时间紧迫就没用模板
	test2();
	return 0;
}