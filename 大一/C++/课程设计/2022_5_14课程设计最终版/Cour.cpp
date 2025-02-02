#include"Cour.h"
TCHAR* CharToTCHAR(char* pChar)
{
	TCHAR* pTchar = nullptr;
	int nLen = strlen(pChar) + 1;
	pTchar = new wchar_t[nLen];
	MultiByteToWideChar(CP_ACP, 0, pChar, nLen, pTchar, nLen);
	return pTchar;
}
void SListNode::SListPrint(SListNode* plist, int h)
{
	SListNode* cur = plist;
	int i = 0;
	TCHAR s1[26][5];
	TCHAR s2[26][5];
	TCHAR s3[26][5];
	while (cur)
	{
		i++;
		outtextxy(50, i * 22 + h, CharToTCHAR(cur->data.name));
		outtextxy(150, i * 22 + h, CharToTCHAR(cur->data.kind));
		_stprintf(s1[i - 1], _T("%d"), cur->data.Coursehour);
		outtextxy(260, i * 22 + h, s1[i - 1]);
		_stprintf(s2[i - 1], _T("%d"), cur->data.credit);
		outtextxy(320, i * 22 + h, s2[i - 1]);
		_stprintf(s3[i - 1], _T("%d"), cur->data.semester);
		outtextxy(380, i * 22 + h, s3[i - 1]);
		cur = cur->next;
	}
}
SListNode* SListNode::createSListCourse()
{
	ifstream myfile("Course.txt", ios::in | ios::_Nocreate);
	if (!myfile)
	{
		cerr << "文件打开失败!" << endl;
		abort();
	}
	CMsg cmsg[26];
	//文件内容写入内存
	for (int i = 0; i < 26; i++)
	{
		myfile >> cmsg[i].num;
		myfile >> cmsg[i].name;
		myfile >> cmsg[i].kind;
		myfile >> cmsg[i].Coursehour;
		myfile >> cmsg[i].credit;
		myfile >> cmsg[i].semester;
		myfile >> cmsg[i].studentNum;
	}
	myfile.close();
	SListNode* head = NULL, * tail = NULL, * cur;
	head = new SListNode;
	if (head == NULL)
	{
		cout << "No memory!" << endl;
		return NULL;
	}
	else
	{
		head->data = cmsg[0];
		head->next = NULL;
		tail = head;
	}
	for (int i = 1; i < N; i++)
	{
		cur = new SListNode;
		if (cur == NULL)
		{
			cout << "No memory!" << endl;
			return head;
		}
		else
		{
			cur->data = cmsg[i];
			cur->next = NULL;
			tail->next = cur;
			tail = cur;
		}
	}
	return head;
}
void SListNode::sortByCredit(SListNode** head)
{
	SListNode* cur = *head;
	while (cur->next)
	{
		SListNode* curr = *head;
		while (curr->next)
		{
			if (curr->data.credit > curr->next->data.credit)
			{
				CMsg temp = curr->data;
				curr->data = curr->next->data;
				curr->next->data = temp;
			}
			curr = curr->next;
		}
		cur = cur->next;
	}
}
void SListNode::sortByStuNum(SListNode** head)
{
	SListNode* cur = *head;
	while (cur->next)
	{
		SListNode* curr = *head;
		while (curr->next)
		{
			if (curr->data.studentNum > curr->next->data.studentNum)
			{
				CMsg temp = curr->data;
				curr->data = curr->next->data;
				curr->next->data = temp;
			}
			curr = curr->next;
		}
		cur = cur->next;
	}
}
bool CMsg::operator==(CMsg& right)
{
	return num == right.num &&
		strcmp(name, right.name) == 0 &&
		strcmp(kind, right.kind) == 0 &&
		Coursehour == right.Coursehour &&
		credit == right.credit &&
		studentNum == right.studentNum &&
		semester == right.semester;
}