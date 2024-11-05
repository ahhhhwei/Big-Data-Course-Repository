#include <iostream>
using namespace std;

class node
{
public:
	int data;
	node *next;
};

//建立链表
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

//遍历链表
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

//查找指定整数
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

//将输入的整数从小到大插入链表
node* insertData(int n, node *head)
{
	node *curNode = head;//插入点的后节点
	node *preNode = NULL;//插入点的前节点
	node *newNode = NULL;//新节点
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
	if (preNode == NULL)//插入到链表头
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

//删除节点
node *deleteData(int n, node* head)
{
	node *curNode = head;//指向当前节点
	node *preNode = NULL;//指向前节点
	while (curNode && curNode->data != n)
	{
		preNode = curNode;//当前节点变前节点
		curNode = curNode->next;
	}
	if (curNode == NULL)
	{
		cout << "Can't find " << n << " in the list" << endl;
		return head;
	}
	if (preNode == NULL)//删除首节点
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
	outputList(ListHead);//遍历链表
	cin >> n;
	node *Findn;
	Findn =	findData(n, ListHead);//查找整数n
	cin >> n;
	ListHead = insertData(n, ListHead);//从小到大插入整数n
	outputList(ListHead);//遍历链表

	system("pause");
	return 0;
}