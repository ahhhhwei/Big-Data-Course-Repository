#define _CRT_SECURE_NO_WARNINGS 1
#include "Init.h"
#include"Cour.h"
#include"Stu.h"
#include<string>
int K = 0;
//����ת���� char to wchar_t
wchar_t* char2wchar(const char* cchar)
{
	wchar_t* m_wchar;//�������ָ��
	//ȡ���ֳ���
	int len = MultiByteToWideChar(
		CP_ACP, //������
		0, //��־
		cchar, //�����ַ���
		strlen(cchar),//�����ַ������� 
		NULL,//�����ַ��� 
		0);//�����ַ�������
	m_wchar = new wchar_t[len + 1];//Ϊ����ָ������ڴ�
	MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), m_wchar, len);//���ƶ��ֵ�����
	m_wchar[len] = '\0';//�ַ�����β
	return m_wchar;//����ָ��
}

//����ת���� wchar_t to char

char* wchar2char(const wchar_t* wchar)
{
	char* m_char;//�������ָ��
	int len = WideCharToMultiByte(CP_ACP, 0, wchar, wcslen(wchar), NULL, 0, NULL, NULL);//ȡ���ֳ���
	m_char = new char[len + 1];//Ϊ����ָ������ڴ�
	WideCharToMultiByte(CP_ACP, 0, wchar, wcslen(wchar), m_char, len, NULL, NULL);//���ƿ��ֵ�����
	m_char[len] = '\0';//�ַ�����β
	return m_char;//���ض���
}


//��ʼ������
//����������
void Init::drawBackground()
{
	initgraph(800, 600);	// ������ͼ���ڣ���СΪ 800*600
	float H = 190;		// ɫ��
	float S = 1;		// ���Ͷ�
	float L = 0.7f;		// ����
	for (int y = 0; y < 600; y++)
	{
		L += 0.0005f;
		setlinecolor(HSLtoRGB(H, S, L));
		line(0, y, 800, y);
	}
}


//�����ĳ���η�Χ�ڵļ��
bool Init::Check(int x1, int x2, int y1, int y2, ExMessage* m)
{
	return (m->x <= x2 && m->x >= x1 && m->y <= y2 && m->y >= y1);
}


//�������˳�����
//����---draw2()
void Init::draw1()
{
	drawBackground();
	settextMSG();
	outtextxy(250, 200, _T("ѧ��ѡ��ϵͳ"));
	outtextxy(250, 350, _T("����"));
	outtextxy(434, 350, _T("�˳�"));
	while (true)
	{
		ExMessage m;
		m = getmessage(EM_MOUSE);
		if (Check(250, 348, 350, 398, &m))
		{
			settextcolor(RED);
			outtextxy(250, 350, _T("����"));
			settextcolor(BLACK);
			outtextxy(434, 350, _T("�˳�"));
			if (m.lbutton)
			{
				draw2();
				break;
			}
		}
		else if (Check(434, 530, 350, 398, &m))
		{
			settextcolor(BLACK);
			outtextxy(250, 350, _T("����"));
			settextcolor(RED);
			outtextxy(434, 350, _T("�˳�"));
			if (m.lbutton)
			{
				drawExit();
			}
		}
		else
		{
			settextcolor(BLACK);
			outtextxy(250, 350, _T("����"));
			settextcolor(BLACK);
			outtextxy(434, 350, _T("�˳�"));
		}
	}
}


//ѧ�������Ա
//ѧ��---draw3()
//����Ա---draw4()
void Init::draw2()
{
	drawBackground();
	settextMSG();
	outtextxy(250, 270, _T("ѧ��"));
	outtextxy(434, 270, _T("����Ա"));
	while (true)
	{
		ExMessage m;
		m = getmessage(EM_MOUSE);
		if (Check(250, 348, 270, 318, &m))
		{
			settextcolor(RED);
			outtextxy(250, 270, _T("ѧ��"));
			settextcolor(BLACK);
			outtextxy(434, 270, _T("����Ա"));
			outtextxy(700, 500, _T("����"));
			outtextxy(700, 550, _T("�˳�"));
			if (m.lbutton)
			{
				student = 1;
				draw3();
				break;
			}
		}
		else if (Check(700, 800, 500, 550, &m))
		{
			settextcolor(RED);
			outtextxy(700, 500, _T("����"));
			settextcolor(BLACK);
			outtextxy(700, 550, _T("�˳�"));
			outtextxy(250, 270, _T("ѧ��"));
			outtextxy(434, 270, _T("����Ա"));
			if (m.lbutton)
			{
				draw1();
			}
		}
		else if (Check(700, 800, 550, 600, &m))
		{
			settextcolor(BLACK);
			outtextxy(700, 500, _T("����"));
			outtextxy(250, 270, _T("ѧ��"));
			outtextxy(434, 270, _T("����Ա"));
			settextcolor(RED);
			outtextxy(700, 550, _T("�˳�"));
			if (m.lbutton)
			{
				drawExit();
			}
		}
		else if (Check(434, 578, 270, 318, &m))
		{
			settextcolor(BLACK);
			outtextxy(250, 270, _T("ѧ��"));
			outtextxy(700, 500, _T("����"));
			outtextxy(700, 550, _T("�˳�"));
			settextcolor(RED);
			outtextxy(434, 270, _T("����Ա"));
			if (m.lbutton)
			{
				administrator = 1;
				draw4();
				break;
			}
		}
		else
		{
			settextcolor(BLACK);
			outtextxy(250, 270, _T("ѧ��"));
			settextcolor(BLACK);
			outtextxy(434, 270, _T("����Ա"));
			outtextxy(700, 500, _T("����"));
			outtextxy(700, 550, _T("�˳�"));
			student = 0;
			administrator = 0;
		}
	}
}


//ѧ����ѧ������������
void Init::draw3()
{
again:
	drawBackground();
	// �����ַ������������������û�����
	wchar_t s1[10];
	InputBox(s1, 10, L"������ѧ��", L"ѧ��");
	wchar_t s2[10];
	InputBox(s2, 10, L"����������", L"ѧ��");
	StudentNode _list;
	StudentNode* head = _list.createStudent();
	StudentNode* cur = head;
	int k = 0;
	while (cur)
	{
		if (strcmp(wchar2char(s1), cur->data.num) == 0 && strcmp(wchar2char(s2), cur->data.password) == 0)
		{
			K = k;
			break;
		}
		cur = cur->next;
		k++;
		if (cur == NULL)
		{
			goto again;
		}
	}
}


//����Ա��������
void Init::draw4()
{
	drawBackground();
	// �����ַ������������������û�����
	wchar_t s[10];
	int i = 0;
	while (strcmp(wchar2char(s), "123456") != 0)
	{
		i++;
		InputBox(s, 10, L"����������", L"����Ա");
		if (i == 5)
			exit(-1);
	}
}


//ѧ��ѡ�ν���
void Init::draw5()
{
	drawBackground();
	LOGFONT f;
	gettextstyle(&f);						// ��ȡ��ǰ��������
	f.lfHeight = 22;						// ��������߶�Ϊ 22
	_tcscpy(f.lfFaceName, _T("����"));	// ��������Ϊ�������п���
	f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
	settextstyle(&f);						// ����������ʽ
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	outtextxy(0, 0, _T("���"));
	outtextxy(50, 0, _T("����"));
	outtextxy(150, 0, _T("����"));
	outtextxy(250, 0, _T("ѧʱ"));
	outtextxy(300, 0, _T("ѧ��"));
	outtextxy(350, 0, _T("����ѧ��"));
	outtextxy(500, 0, _T("ѡ��"));
	SListNode list;
	SListNode* phead = list.createSListCourse();
	for (int i = 1; i <= 26; i++)
	{
		TCHAR s[5];
		_stprintf(s, _T("%d"), i);
		outtextxy(0, i * 22, s);
	}
	list.SListPrint(phead);
	for (int i = 1; i <= 26; i++)
	{
		setlinecolor(BLACK);
		fillrectangle(505, i * 22, 535, i * 22 + 15);
	}
	outtextxy(650, 550, _T("��ѡ�ã��˳�"));
	if (student)
	{
		int arr[26] = { 0 };//��ѭ������
		while (true)
		{
			ExMessage m;
			m = getmessage(EM_MOUSE);
			if (Check(650, 780, 550, 570, &m))
			{
				settextcolor(RED);
				outtextxy(650, 550, _T("��ѡ�ã��˳�"));
				if (m.lbutton)
				{
					drawExit();
				}
			}
			else
			{
				settextcolor(BLACK);
				outtextxy(650, 550, _T("��ѡ�ã��˳�"));
			}
			for (int i = 1; i <= 26; i++)
			{
				if (Check(505, 535, i * 22, i * 22 + 20, &m))
				{
					setfillcolor(RED);
					fillrectangle(505, i * 22, 535, i * 22 + 15);
					if (m.lbutton)
					{
						ofstream myfile("Student.txt", ios::out|ios::_Nocreate|ios::app);
						if (!myfile)
						{
							cerr << "�ļ���ʧ��!" << endl;
						}
						char str[26][4] = { "A++","B++","C++","D++","E++","F++","G++","H++","I++","J++","K++","L++",
							"M++","N++","O++","P++","Q++","R++","S++","T++","U++","V++","W++","X++" ,"Y++" ,"Z++" };
						arr[i - 1] ^= 1;//�����λ����
						StudentNode _list;
						StudentNode* phead = _list.createStudent();
						StudentNode* cur = phead;
						while (cur)
						{
							if (cur->next==NULL)
							{
								if (arr[i - 1])
								myfile << str[i - 1];
							}
							cur = cur->next;
						}
						myfile.close();
					}
				}
				else
				{
					for (int j = 1; j <= 26; j++)
					{
						if (arr[j - 1] == 1)
						{
							setfillcolor(RED);
							fillrectangle(505, j * 22, 535, j * 22 + 15);
						}
						else
						{
							setfillcolor(WHITE);
							fillrectangle(505, j * 22, 535, j * 22 + 15);
						}
					}
				}
			}
		}
	}
}


//ѧ����Ϣ���---draw7()
//�γ���Ϣ���---draw8()
//��ѧ�ֲ�ѯ�γ�---draw9()
//ĳ�γ�ѧ��ѡ�����---draw10()
//ĳѧ��ѡ�����---draw11()
//��������---draw12()
void Init::draw6()
{
	drawBackground();
	settextMSG();
	outtextxy(150, 0, _T("ѧ����Ϣ���"));
	outtextxy(150, 100, _T("�γ���Ϣ���"));
	outtextxy(150, 200, _T("��ѧ�ֲ�ѯ�γ�"));
	outtextxy(150, 300, _T("ĳ�γ�ѧ��ѡ�����"));
	outtextxy(150, 400, _T("ĳѧ��ѡ�����"));
	outtextxy(150, 500, _T("��������"));
	if (administrator)
	{
		int arr[6] = { 0,0,0,0,0,0 };
		while (true)
		{
			ExMessage m;
			m = getmessage(EM_MOUSE);
			if (Check(700, 800, 500, 550, &m))
			{
				settextcolor(RED);
				outtextxy(700, 500, _T("����"));
				settextcolor(BLACK);
				outtextxy(700, 550, _T("�˳�"));
				outtextxy(150, 0, _T("ѧ����Ϣ���"));
				outtextxy(150, 100, _T("�γ���Ϣ���"));
				outtextxy(150, 200, _T("��ѧ�ֲ�ѯ�γ�"));
				outtextxy(150, 300, _T("ĳ�γ�ѧ��ѡ�����"));
				outtextxy(150, 400, _T("ĳѧ��ѡ�����"));
				outtextxy(150, 500, _T("��������"));
				if (m.lbutton)
				{
					draw2();
				}
			}
			else if (Check(700, 800, 550, 600, &m))
			{
				settextcolor(BLACK);
				outtextxy(700, 500, _T("����"));
				outtextxy(150, 0, _T("ѧ����Ϣ���"));
				outtextxy(150, 100, _T("�γ���Ϣ���"));
				outtextxy(150, 200, _T("��ѧ�ֲ�ѯ�γ�"));
				outtextxy(150, 300, _T("ĳ�γ�ѧ��ѡ�����"));
				outtextxy(150, 400, _T("ĳѧ��ѡ�����"));
				outtextxy(150, 500, _T("��������"));
				settextcolor(RED);
				outtextxy(700, 550, _T("�˳�"));
				if (m.lbutton)
				{
					drawExit();
				}
			}
			else if (Check(150, 430, 0, 50, &m))
			{
				settextcolor(RED);
				outtextxy(150, 0, _T("ѧ����Ϣ���"));
				settextcolor(BLACK);
				outtextxy(150, 100, _T("�γ���Ϣ���"));
				outtextxy(150, 200, _T("��ѧ�ֲ�ѯ�γ�"));
				outtextxy(150, 300, _T("ĳ�γ�ѧ��ѡ�����"));
				outtextxy(150, 400, _T("ĳѧ��ѡ�����"));
				outtextxy(150, 500, _T("��������"));
				outtextxy(700, 500, _T("����"));
				outtextxy(700, 550, _T("�˳�"));
				if (m.lbutton)
				{
					arr[0] = 1;
					draw7();
					break;
				}
			}
			else if (Check(150, 430, 100, 150, &m))
			{
				settextcolor(RED);
				outtextxy(150, 100, _T("�γ���Ϣ���"));
				settextcolor(BLACK);
				outtextxy(150, 0, _T("ѧ����Ϣ���"));
				outtextxy(150, 200, _T("��ѧ�ֲ�ѯ�γ�"));
				outtextxy(150, 300, _T("ĳ�γ�ѧ��ѡ�����"));
				outtextxy(150, 400, _T("ĳѧ��ѡ�����"));
				outtextxy(150, 500, _T("��������"));
				outtextxy(700, 500, _T("����"));
				outtextxy(700, 550, _T("�˳�"));
				if (m.lbutton)
				{
					arr[1] = 1;
					draw8();
					break;
				}
			}
			else if (Check(150, 480, 200, 250, &m))
			{
				settextcolor(RED);
				outtextxy(150, 200, _T("��ѧ�ֲ�ѯ�γ�"));
				settextcolor(BLACK);
				outtextxy(150, 0, _T("ѧ����Ϣ���"));
				outtextxy(150, 100, _T("�γ���Ϣ���"));
				outtextxy(150, 300, _T("ĳ�γ�ѧ��ѡ�����"));
				outtextxy(150, 400, _T("ĳѧ��ѡ�����"));
				outtextxy(150, 500, _T("��������"));
				outtextxy(700, 500, _T("����"));
				outtextxy(700, 550, _T("�˳�"));
				if (m.lbutton)
				{
					arr[2] = 1;
					draw9();
					break;
				}
			}
			else if (Check(150, 570, 300, 350, &m))
			{
				settextcolor(RED);
				outtextxy(150, 300, _T("ĳ�γ�ѧ��ѡ�����"));
				settextcolor(BLACK);
				outtextxy(150, 0, _T("ѧ����Ϣ���"));
				outtextxy(150, 100, _T("�γ���Ϣ���"));
				outtextxy(150, 200, _T("��ѧ�ֲ�ѯ�γ�"));
				outtextxy(150, 400, _T("ĳѧ��ѡ�����"));
				outtextxy(150, 500, _T("��������"));
				outtextxy(700, 500, _T("����"));
				outtextxy(700, 550, _T("�˳�"));
				if (m.lbutton)
				{
					arr[3] = 1;
					draw10();
					break;
				}
			}
			else if (Check(150, 480, 400, 450, &m))
			{
				settextcolor(RED);
				outtextxy(150, 400, _T("ĳѧ��ѡ�����"));
				settextcolor(BLACK);
				outtextxy(150, 0, _T("ѧ����Ϣ���"));
				outtextxy(150, 100, _T("�γ���Ϣ���"));
				outtextxy(150, 200, _T("��ѧ�ֲ�ѯ�γ�"));
				outtextxy(150, 300, _T("ĳ�γ�ѧ��ѡ�����"));
				outtextxy(150, 500, _T("��������"));
				outtextxy(700, 500, _T("����"));
				outtextxy(700, 550, _T("�˳�"));
				if (m.lbutton)
				{
					arr[4] = 1;
					draw11();
					break;
				}
			}
			else if (Check(150, 330, 500, 550, &m))
			{
				settextcolor(RED);
				outtextxy(150, 500, _T("��������"));
				settextcolor(BLACK);
				outtextxy(150, 0, _T("ѧ����Ϣ���"));
				outtextxy(150, 100, _T("�γ���Ϣ���"));
				outtextxy(150, 200, _T("��ѧ�ֲ�ѯ�γ�"));
				outtextxy(150, 300, _T("ĳ�γ�ѧ��ѡ�����"));
				outtextxy(150, 400, _T("ĳѧ��ѡ�����"));
				outtextxy(700, 500, _T("����"));
				outtextxy(700, 550, _T("�˳�"));
				if (m.lbutton)
				{
					arr[5] = 1;
					draw12();
					break;
				}
			}
			else
			{
				settextcolor(BLACK);
				outtextxy(150, 0, _T("ѧ����Ϣ���"));
				outtextxy(150, 100, _T("�γ���Ϣ���"));
				outtextxy(150, 200, _T("��ѧ�ֲ�ѯ�γ�"));
				outtextxy(150, 300, _T("ĳ�γ�ѧ��ѡ�����"));
				outtextxy(150, 400, _T("ĳѧ��ѡ�����"));
				outtextxy(150, 500, _T("��������"));
				outtextxy(700, 500, _T("����"));
				outtextxy(700, 550, _T("�˳�"));
			}
		}
		if (arr[0])
		{
			draw7();
			while (true)
			{
				ExMessage m;
				m = getmessage(EM_MOUSE);
				if (Check(700, 800, 500, 550, &m))
				{
					settextcolor(RED);
					outtextxy(700, 500, _T("����"));
					settextcolor(BLACK);
					outtextxy(700, 550, _T("�˳�"));
					if (m.lbutton)
					{
						draw6();
					}
				}
				else if (Check(700, 800, 550, 600, &m))
				{
					settextcolor(BLACK);
					outtextxy(700, 500, _T("����"));
					settextcolor(RED);
					outtextxy(700, 550, _T("�˳�"));
					if (m.lbutton)
					{
						drawExit();
					}
				}
				else
				{
					settextcolor(BLACK);
					outtextxy(700, 500, _T("����"));
					outtextxy(700, 550, _T("�˳�"));
				}
			}
		}
		if (arr[1])
		{
			draw8();
			while (true)
			{
				ExMessage m;
				m = getmessage(EM_MOUSE);
				if (Check(700, 800, 500, 550, &m))
				{
					settextcolor(RED);
					outtextxy(700, 500, _T("����"));
					settextcolor(BLACK);
					outtextxy(700, 550, _T("�˳�"));
					if (m.lbutton)
					{
						draw6();
					}
				}
				else if (Check(700, 800, 550, 600, &m))
				{
					settextcolor(BLACK);
					outtextxy(700, 500, _T("����"));
					settextcolor(RED);
					outtextxy(700, 550, _T("�˳�"));
					if (m.lbutton)
					{
						drawExit();
					}
				}
				else
				{
					settextcolor(BLACK);
					outtextxy(700, 500, _T("����"));
					outtextxy(700, 550, _T("�˳�"));
				}
			}
		}
		if (arr[2])
		{
			draw9();
			while (true)
			{
				ExMessage m;
				m = getmessage(EM_MOUSE);
				if (Check(700, 800, 500, 550, &m))
				{
					settextcolor(RED);
					outtextxy(700, 500, _T("����"));
					settextcolor(BLACK);
					outtextxy(700, 550, _T("�˳�"));
					if (m.lbutton)
					{
						draw6();
					}
				}
				else if (Check(700, 800, 550, 600, &m))
				{
					settextcolor(BLACK);
					outtextxy(700, 500, _T("����"));
					settextcolor(RED);
					outtextxy(700, 550, _T("�˳�"));
					if (m.lbutton)
					{
						drawExit();
					}
				}
				else
				{
					settextcolor(BLACK);
					outtextxy(700, 500, _T("����"));
					outtextxy(700, 550, _T("�˳�"));
				}
			}
		}
		if (arr[3])
		{
			draw10();
			while (true)
			{
				ExMessage m;
				m = getmessage(EM_MOUSE);
				if (Check(700, 800, 500, 550, &m))
				{
					settextcolor(RED);
					outtextxy(700, 500, _T("����"));
					settextcolor(BLACK);
					outtextxy(700, 550, _T("�˳�"));
					if (m.lbutton)
					{
						draw6();
					}
				}
				else if (Check(700, 800, 550, 600, &m))
				{
					settextcolor(BLACK);
					outtextxy(700, 500, _T("����"));
					settextcolor(RED);
					outtextxy(700, 550, _T("�˳�"));
					if (m.lbutton)
					{
						drawExit();
					}
				}
				else
				{
					settextcolor(BLACK);
					outtextxy(700, 500, _T("����"));
					outtextxy(700, 550, _T("�˳�"));
				}
			}
		}
		if (arr[4])
		{
			draw11();
			while (true)
			{
				ExMessage m;
				m = getmessage(EM_MOUSE);
				if (Check(700, 800, 500, 550, &m))
				{
					settextcolor(RED);
					outtextxy(700, 500, _T("����"));
					settextcolor(BLACK);
					outtextxy(700, 550, _T("�˳�"));
					if (m.lbutton)
					{
						draw6();
					}
				}
				else if (Check(700, 800, 550, 600, &m))
				{
					settextcolor(BLACK);
					outtextxy(700, 500, _T("����"));
					settextcolor(RED);
					outtextxy(700, 550, _T("�˳�"));
					if (m.lbutton)
					{
						drawExit();
					}
				}
				else
				{
					settextcolor(BLACK);
					outtextxy(700, 500, _T("����"));
					outtextxy(700, 550, _T("�˳�"));
				}
			}
		}
		if (arr[5])
		{
			draw12();
		}
	}
}


//ѧ����Ϣ���
void Init::draw7()
{
	drawBackground();
	LOGFONT f;
	gettextstyle(&f);						// ��ȡ��ǰ��������
	f.lfHeight = 20;						// ��������߶�Ϊ 48
	_tcscpy(f.lfFaceName, _T("����"));	// ��������Ϊ�������п���
	f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
	settextstyle(&f);						// ����������ʽ
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	StudentNode _list;
	StudentNode* head = _list.createStudent();
	_list.StudentPrint(head);
	outtextxy(50, 0, _T("ѧ��"));
	outtextxy(150, 0, _T("����"));
	outtextxy(250, 0, _T("ѡ�����"));
	settextMSG();
	outtextxy(700, 500, _T("����"));
	outtextxy(700, 550, _T("�˳�"));
}


//�γ���Ϣ���
void Init::draw8()
{
	drawBackground();
	settextMSG();
	outtextxy(700, 500, _T("����"));
	outtextxy(700, 550, _T("�˳�"));
	settextMSG();
	settextcolor(BLACK);
	LOGFONT f;
	gettextstyle(&f);						// ��ȡ��ǰ��������
	f.lfHeight = 22;						// ��������߶�Ϊ 22
	_tcscpy(f.lfFaceName, _T("����"));	// ��������Ϊ�������п���
	f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
	settextstyle(&f);						// ����������ʽ
	setbkmode(TRANSPARENT);
	outtextxy(0, 0, _T("���"));
	outtextxy(50, 0, _T("����"));
	outtextxy(150, 0, _T("����"));
	outtextxy(250, 0, _T("ѧʱ"));
	outtextxy(300, 0, _T("ѧ��"));
	outtextxy(350, 0, _T("����ѧ��"));
	outtextxy(500, 0, _T("ѡ������"));
	SListNode list;
	SListNode* phead = list.createSListCourse();
	SListNode* cur = phead;
	TCHAR s2[26][5];
	int ii = 0;
	while (cur)
	{
		ii++;
		_stprintf(s2[ii - 1], _T("%d"), cur->data.studentNum);
		outtextxy(530, ii * 22, s2[ii - 1]);
		cur = cur->next;
	}
	for (int i = 1; i <= 26; i++)
	{
		TCHAR s1[5];
		_stprintf(s1, _T("%d"), i);
		outtextxy(0, i * 22, s1);
	}
	list.SListPrint(phead);
	while (true)
	{
		ExMessage m;
		m = getmessage(EM_MOUSE);
		if (Check(700, 800, 550, 600, &m))
		{
			settextMSG();
			settextcolor(RED);
			outtextxy(700, 550, _T("�˳�"));
			settextcolor(BLACK);
			outtextxy(700, 500, _T("����"));
			if (m.lbutton)
			{
				drawExit();
			}
		}
		else if (Check(700, 800, 500, 550, &m))
		{
			settextMSG();
			settextcolor(RED);
			outtextxy(700, 500, _T("����"));
			settextcolor(BLACK);
			outtextxy(700, 550, _T("�˳�"));
			if (m.lbutton)
			{
				draw6();
			}
		}
		else
		{
			settextMSG();
			settextcolor(BLACK);
			outtextxy(700, 500, _T("����"));
			outtextxy(700, 550, _T("�˳�"));
		}
	}
}


//��ѧ�ֲ�ѯ�γ�
void Init::draw9()
{
	drawBackground();
	settextMSG();
	outtextxy(0, 0, _T("��ѧ�ֲ�ѯ�γ�"));
	wchar_t s[10];
	outtextxy(700, 500, _T("����"));
	outtextxy(700, 550, _T("�˳�"));
	InputBox(s, 10, L"������ѧ��", L"��ѧ�ֲ�ѯ�γ�");
	SListNode list;
	SListNode* phead = list.createSListCourse();
	SListNode* cur = phead;
	int k = 0;
	for (int i = 0; i < 26; i++)
	{
		if (stoi(s) == cur->data.credit)
		{
			settextMSG();
			outtextxy(0, 50, _T("ѧ��Ϊ"));
			outtextxy(165, 50, _T("�Ŀγ���:"));
			TCHAR t[5];
			_stprintf(t, _T("%d"), cur->data.credit);
			outtextxy(140, 50, t);
			LOGFONT f;
			gettextstyle(&f);						// ��ȡ��ǰ��������
			f.lfHeight = 30;						// ��������߶�Ϊ 20
			_tcscpy(f.lfFaceName, _T("����"));	// ��������Ϊ�����塱
			f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
			settextstyle(&f);						// ����������ʽ
			setbkmode(TRANSPARENT);
			settextcolor(BLACK);
			outtextxy(400, 50 + 30 * k, char2wchar(cur->data.name));
			k++;
		}
		cur = cur->next;
	}
}


//ĳ�γ�ѧ��ѡ�����
void Init::draw10()
{
	drawBackground();
	settextMSG();
	outtextxy(0, 0, _T("ĳ�γ�ѧ��ѡ�����"));
	outtextxy(700, 500, _T("����"));
	outtextxy(700, 550, _T("�˳�"));
	wchar_t s[10];
	InputBox(s, 10, L"������γ���", L"ĳ�γ�ѧ��ѡ�����");
	SListNode list;
	SListNode* phead = list.createSListCourse();
	SListNode* cur = phead;
	for (int i = 0; i < 26; i++)
	{
		if (strcmp(wchar2char(s), cur->data.name) == 0)
		{
			TCHAR t[5];
			outtextxy(250, 250, _T("ѡ������:"));
			_stprintf(t, _T("%d"), cur->data.studentNum);
			outtextxy(450, 250, t);
		}
		cur = cur->next;
	}
}


//ĳѧ��ѡ�����
void Init::draw11()
{
	drawBackground();
	settextMSG();
	outtextxy(700, 500, _T("����"));
	outtextxy(700, 550, _T("�˳�"));
	wchar_t s[10];
	InputBox(s, 10, L"������ѧ������", L"ĳѧ��ѡ�����");
	StudentNode _list;
	StudentNode* phead = _list.createStudent();
	StudentNode* cur = phead;
	for (int i = 0; i < 10; i++)
	{
		if (strcmp(wchar2char(s), cur->data.name) == 0)
		{
			settextMSG();
			outtextxy(0, 0, _T("ѡ�����:"));
			LOGFONT f;
			gettextstyle(&f);						// ��ȡ��ǰ��������
			f.lfHeight = 48;						// ��������߶�Ϊ 48
			_tcscpy(f.lfFaceName, _T("����"));	// ��������Ϊ�������п���
			f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
			settextstyle(&f);						// ����������ʽ
			setbkmode(TRANSPARENT);
			settextcolor(BLACK);
			outtextxy(0, 50, char2wchar(cur->data._course));
		}
		settextMSG();
		cur = cur->next;
	}
}


// �����������:
// ѡ����Ϣ��ѧ������---draw13()
// ѡ����Ϣ��ѡ����������---draw14()
// ѡ����Ϣ���γ̱������---draw15()
void Init::draw12()
{
	drawBackground();
	settextMSG();
	outtextxy(0, 0, _T("��������"));
	outtextxy(0, 100, _T("ѡ����Ϣ��ѧ������"));
	outtextxy(0, 300, _T("ѡ����Ϣ��ѡ����������"));
	outtextxy(0, 500, _T("ѡ����Ϣ���γ̱������"));
	outtextxy(700, 500, _T("����"));
	outtextxy(700, 550, _T("�˳�"));
	while (true)
	{
		ExMessage m;
		m = getmessage(EM_MOUSE);
		if (Check(700, 800, 500, 550, &m))
		{
			settextcolor(RED);
			outtextxy(700, 500, _T("����"));
			settextcolor(BLACK);
			outtextxy(700, 550, _T("�˳�"));
			outtextxy(0, 100, _T("ѡ����Ϣ��ѧ������"));
			outtextxy(0, 300, _T("ѡ����Ϣ��ѡ����������"));
			outtextxy(0, 500, _T("ѡ����Ϣ���γ̱������"));
			if (m.lbutton)
			{
				draw6();
			}
		}
		else if (Check(700, 800, 550, 600, &m))
		{
			settextcolor(BLACK);
			outtextxy(700, 500, _T("����"));
			outtextxy(0, 100, _T("ѡ����Ϣ��ѧ������"));
			outtextxy(0, 300, _T("ѡ����Ϣ��ѡ����������"));
			outtextxy(0, 500, _T("ѡ����Ϣ���γ̱������"));
			settextcolor(RED);
			outtextxy(700, 550, _T("�˳�"));
			if (m.lbutton)
			{
				drawExit();
			}
		}
		else if (Check(0, 410, 100, 150, &m))
		{
			settextcolor(RED);
			outtextxy(0, 100, _T("ѡ����Ϣ��ѧ������"));
			if (m.lbutton)
			{
				draw13();
			}
			settextcolor(BLACK);
			outtextxy(0, 0, _T("��������"));
			outtextxy(0, 300, _T("ѡ����Ϣ��ѡ����������"));
			outtextxy(0, 500, _T("ѡ����Ϣ���γ̱������"));
			outtextxy(700, 500, _T("����"));
			outtextxy(700, 550, _T("�˳�"));
		}
		else if (Check(0, 510, 300, 350, &m))
		{
			settextcolor(RED);
			outtextxy(0, 300, _T("ѡ����Ϣ��ѡ����������"));
			if (m.lbutton)
			{
				draw14();
				break;
			}
			settextcolor(BLACK);
			outtextxy(0, 0, _T("��������"));
			outtextxy(0, 100, _T("ѡ����Ϣ��ѧ������"));
			outtextxy(0, 500, _T("ѡ����Ϣ���γ̱������"));
			outtextxy(700, 500, _T("����"));
			outtextxy(700, 550, _T("�˳�"));
		}
		else if (Check(0, 510, 500, 550, &m))
		{
			settextcolor(RED);
			outtextxy(0, 500, _T("ѡ����Ϣ���γ̱������"));
			if (m.lbutton)
			{
				draw15();
				break;
			}
			settextcolor(BLACK);
			outtextxy(0, 0, _T("��������"));
			outtextxy(0, 100, _T("ѡ����Ϣ��ѧ������"));
			outtextxy(0, 300, _T("ѡ����Ϣ��ѡ����������"));
			outtextxy(700, 500, _T("����"));
			outtextxy(700, 550, _T("�˳�"));
		}
		else
		{
			settextcolor(BLACK);
			outtextxy(0, 0, _T("��������"));
			outtextxy(0, 100, _T("ѡ����Ϣ��ѧ������"));
			outtextxy(0, 300, _T("ѡ����Ϣ��ѡ����������"));
			outtextxy(0, 500, _T("ѡ����Ϣ���γ̱������"));
			outtextxy(700, 500, _T("����"));
			outtextxy(700, 550, _T("�˳�"));
		}
	}
}


//ѡ����Ϣ��ѧ������
void Init::draw13()
{
	drawBackground();
	settextMSG();
	outtextxy(700, 500, _T("����"));
	outtextxy(700, 550, _T("�˳�"));
	SListNode list;
	SListNode* phead = list.createSListCourse();
	list.sortByCredit(&phead);
	LOGFONT f;
	gettextstyle(&f);						// ��ȡ��ǰ��������
	f.lfHeight = 20;						// ��������߶�Ϊ 48
	_tcscpy(f.lfFaceName, _T("����"));	// ��������Ϊ�������п���
	f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
	settextstyle(&f);						// ����������ʽ
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	list.SListPrint(phead);
	outtextxy(50, 0, _T("����"));
	outtextxy(150, 0, _T("����"));
	outtextxy(250, 0, _T("ѧʱ"));
	outtextxy(300, 0, _T("ѧ��"));
	outtextxy(350, 0, _T("����ѧ��"));
	while (true)
	{
		ExMessage m;
		m = getmessage(EM_MOUSE);
		settextMSG();
		if (Check(700, 800, 550, 600, &m))
		{
			settextcolor(RED);
			outtextxy(700, 550, _T("�˳�"));
			settextcolor(BLACK);
			outtextxy(700, 500, _T("����"));
			if (m.lbutton)
			{
				drawExit();
			}
		}
		else if (Check(700, 800, 500, 550, &m))
		{
			settextcolor(RED);
			outtextxy(700, 500, _T("����"));
			settextcolor(BLACK);
			outtextxy(700, 550, _T("�˳�"));
			if (m.lbutton)
			{
				draw12();
			}
		}
		else
		{
			settextcolor(BLACK);
			outtextxy(700, 500, _T("����"));
			outtextxy(700, 550, _T("�˳�"));
		}
	}
}


//ѡ����Ϣ��ѡ����������
void Init::draw14()
{
	drawBackground();
	settextMSG();
	outtextxy(700, 500, _T("����"));
	outtextxy(700, 550, _T("�˳�"));
	SListNode list;
	SListNode* phead = list.createSListCourse();
	list.sortByStuNum(&phead);
	LOGFONT f;
	gettextstyle(&f);						// ��ȡ��ǰ��������
	f.lfHeight = 20;						// ��������߶�Ϊ 48
	_tcscpy(f.lfFaceName, _T("����"));	// ��������Ϊ�������п���
	f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
	settextstyle(&f);						// ����������ʽ
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	list.SListPrint(phead);
	outtextxy(50, 0, _T("����"));
	outtextxy(150, 0, _T("����"));
	outtextxy(250, 0, _T("ѧʱ"));
	outtextxy(300, 0, _T("ѧ��"));
	outtextxy(350, 0, _T("����ѧ��"));
	outtextxy(500, 0, _T("ѡ������"));
	TCHAR s3[26][5];
	int i = 0;
	SListNode* cur = phead;
	while (cur)
	{
		i++;
		_stprintf(s3[i - 1], _T("%d"), cur->data.studentNum);
		outtextxy(500, i * 22, s3[i - 1]);
		cur = cur->next;
	}
	while (true)
	{
		ExMessage m;
		m = getmessage(EM_MOUSE);
		settextMSG();
		if (Check(700, 800, 550, 600, &m))
		{
			settextcolor(RED);
			outtextxy(700, 550, _T("�˳�"));
			settextcolor(BLACK);
			outtextxy(700, 500, _T("����"));
			if (m.lbutton)
			{
				drawExit();
			}
		}
		else if (Check(700, 800, 500, 550, &m))
		{
			settextcolor(RED);
			outtextxy(700, 500, _T("����"));
			settextcolor(BLACK);
			outtextxy(700, 550, _T("�˳�"));
			if (m.lbutton)
			{
				draw12();
			}
		}
		else
		{
			settextcolor(BLACK);
			outtextxy(700, 500, _T("����"));
			outtextxy(700, 550, _T("�˳�"));
		}
	}
}


//ѡ����Ϣ���γ̱������
void Init::draw15()
{
	drawBackground();
	settextMSG();
	outtextxy(700, 500, _T("����"));
	outtextxy(700, 550, _T("�˳�"));
	while (true)
	{
		ExMessage m;
		m = getmessage(EM_MOUSE);
		settextMSG();
		settextcolor(BLACK);
		LOGFONT f;
		gettextstyle(&f);						// ��ȡ��ǰ��������
		f.lfHeight = 22;						// ��������߶�Ϊ 22
		_tcscpy(f.lfFaceName, _T("����"));	// ��������Ϊ�������п���
		f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
		settextstyle(&f);						// ����������ʽ
		setbkmode(TRANSPARENT);
		outtextxy(0, 0, _T("���"));
		outtextxy(50, 0, _T("����"));
		outtextxy(150, 0, _T("����"));
		outtextxy(250, 0, _T("ѧʱ"));
		outtextxy(300, 0, _T("ѧ��"));
		outtextxy(350, 0, _T("����ѧ��"));
		SListNode list;
		SListNode* phead = list.createSListCourse();
		for (int i = 1; i <= 26; i++)
		{
			TCHAR s[5];
			_stprintf(s, _T("%d"), i);
			outtextxy(0, 5 + i * 22, s);
		}
		list.SListPrint(phead, 5);
		settextMSG();
		settextcolor(BLACK);
		outtextxy(700, 500, _T("����"));
		outtextxy(700, 550, _T("�˳�"));
		if (Check(700, 800, 550, 600, &m))
		{
			settextMSG();
			settextcolor(RED);
			outtextxy(700, 550, _T("�˳�"));
			settextcolor(BLACK);
			outtextxy(700, 500, _T("����"));
			if (m.lbutton)
			{
				drawExit();
			}
		}
		else if (Check(700, 800, 500, 550, &m))
		{
			settextMSG();
			settextcolor(RED);
			outtextxy(700, 500, _T("����"));
			settextcolor(BLACK);
			outtextxy(700, 550, _T("�˳�"));
			if (m.lbutton)
			{
				draw12();
			}
		}
		else
		{
			settextMSG();
			settextcolor(BLACK);
			outtextxy(700, 500, _T("����"));
			outtextxy(700, 550, _T("�˳�"));
		}
	}
}


//�������ú���
void Init::settextMSG()
{
	LOGFONT f;
	gettextstyle(&f);						// ��ȡ��ǰ��������
	f.lfHeight = 48;						// ��������߶�Ϊ 48
	_tcscpy(f.lfFaceName, _T("�����п�"));	// ��������Ϊ�������п���
	f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
	settextstyle(&f);						// ����������ʽ
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
}


//�˳�����
void Init::drawExit()
{
	cleardevice();
	settextMSG();
	settextcolor(WHITE);
	outtextxy(300, 275, _T("ллʹ�ã�"));
	Sleep(3000);
	exit(0);
}