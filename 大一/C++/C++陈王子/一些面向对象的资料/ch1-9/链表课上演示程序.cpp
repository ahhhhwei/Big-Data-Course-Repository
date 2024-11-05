#include <iostream>
using namespace std;

class node
{
public:
	int data;
	node *next;
};

//��������
node* createlist(int n)
{
	node *temp, *head = NULL, *tail = NULL;
	int num;
	cin >> num;
	head = new node;
	if (head == NULL)
	{
		cout << "No memory available!";
		return NULL;
	}
	else
	{
		head->data = num;
		head->next = NULL;
		tail = head;
	}
	for (int i = 0; i < n - 1; i++)
	{
		cin >> num;
		temp = new node;
		if (temp == NULL)
		{
			cout << "No memory available!";
			return NULL;
		}
		else
		{
			temp->data = num;
			temp->next = NULL;
			tail->next = temp;
			tail = temp;
		}
	}
	return head;
}

//��������
void outputList(node *head)
{
	cout << "List: ";
	node *curNode = head;
	while (curNode)
	{
		cout << curNode->data;
		if (curNode->next)
			cout << "->";
		curNode = curNode->next;
	}
	cout << endl;
}

//����ָ������
node* findData(int n, node *head)
{
	node *curNode = head;
	while (curNode)
	{
		if (curNode->data == n)
		{
			cout << "Find " << n << " in the list." << endl;
			return curNode;
		}
		curNode = curNode->next;
	}
	cout << "can't find " << n << " int the list." << endl;
	return NULL;
}

//�������������С�����������
node* insertData(int n, node *head)
{
	node *curNode = head;//�����ĺ�ڵ�
	node *preNode = NULL;//������ǰ�ڵ�
	node *newNode = NULL;//�½ڵ�
	while ((curNode != NULL) && (curNode->data < n))
	{
		preNode = curNode;
		curNode = curNode->next;
	}
	newNode = new node;
	if (newNode == NULL)
	{
		cout << "No memory available!";
		return head;
	}
	newNode->data = n;
	if (preNode == NULL)//���뵽����ͷ
	{
		newNode->next = curNode;
		return newNode;
	}
	else
	{
		preNode->next = newNode;
		newNode->next = curNode;
		return head;
	}

}

//ɾ���ڵ�
node *deleteData(int n, node* head)
{
	node *curNode = head;//ָ��ǰ�ڵ�
	node *preNode = NULL;//ָ��ǰ�ڵ�
	while (curNode && curNode->data != n)
	{
		preNode = curNode;//��ǰ�ڵ��ǰ�ڵ�
		curNode = curNode->next;
	}
	if (curNode == NULL)
	{
		cout << "Can't find " << n << " in the list" << endl;
		return head;
	}
	if (preNode == NULL)//ɾ���׽ڵ�
		head = head->next;
	else
		preNode->next = curNode->next;

	delete curNode;
	return head;

}

int main()
{
	int n;
	node *ListHead = NULL;
	cout << "please enter the number of nodes:" << endl;
	cin >> n;
	if (n > 0)
		ListHead = createlist(n);
	outputList(ListHead);//��������
	cin >> n;
	node *Findn;
	Findn =	findData(n, ListHead);//��������n
	cin >> n;
	ListHead = insertData(n, ListHead);//��С�����������n
	outputList(ListHead);//��������

	system("pause");
	return 0;
}