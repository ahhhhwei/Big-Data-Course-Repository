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
	cout << "�����������������:" << endl;
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
	//�޸������1 2�ֱ�����3�� �� ���е����ɺ���
	//ʱ����Ⱦ�û��ģ��
	test2();
	return 0;
}