#include"Stu.h"
TCHAR* CharToTCHAR1(char* pChar)
{
	TCHAR* pTchar = nullptr;
	int nLen = strlen(pChar) + 1;
	pTchar = new wchar_t[nLen];
	MultiByteToWideChar(CP_ACP, 0, pChar, nLen, pTchar, nLen);
	return pTchar;
}
void StudentNode::StudentPrint(StudentNode* plist, int h)
{
	StudentNode* cur = plist;
	int i = 0;
	while (cur)
	{
		i++;
		outtextxy(50, i * 22 + h, CharToTCHAR1(cur->data.num));
		outtextxy(150, i * 22 + h, CharToTCHAR1(cur->data.name));
		outtextxy(250, i * 22 + h, CharToTCHAR1(cur->data._course));
		cur = cur->next;
	}
}
StudentNode* StudentNode::createStudent()
{
	ifstream myfile("Student.txt", ios::in | ios::_Nocreate);
	if (!myfile)
	{
		cerr << "文件打开失败!" << endl;
		abort();
	}
	Student student[26] = { 0 };
	//读取文件到内存
	for (int i = 0; i < 26; i++)
	{
		myfile >> student[i].num;
		myfile >> student[i].name;
		myfile >> student[i].password;
		myfile >> student[i]._course;
	}
	myfile.close();
	StudentNode* head = NULL, * tail = NULL, * cur;
	head = new StudentNode;
	if (head == NULL)
	{
		cout << "No memory!" << endl;
		return NULL;
	}
	else
	{
		head->data = student[0];
		head->next = NULL;
		tail = head;
	}
	for (int i = 1; i < N; i++)
	{
		cur = new StudentNode;
		if (cur == NULL)
		{
			cout << "No memory!" << endl;
			return head;
		}
		else
		{
			cur->data = student[i];
			cur->next = NULL;
			tail->next = cur;
			tail = cur;
		}
	}
	return head;
}
bool Student::operator==(Student& right)
{
	return strcmp(num, right.num) == 0 &&
		strcmp(name, right.name) == 0 &&
		strcmp(password, right.password) == 0 &&
		strcmp(_course, right._course) == 0;
}