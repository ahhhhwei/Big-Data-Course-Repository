#define _CRT_SECURE_NO_WARNINGS 1
#include "Init.h"
#include"Cour.h"
#include"Stu.h"
#include<string>
int K = 0;
//多字转宽字 char to wchar_t
wchar_t* char2wchar(const char* cchar)
{
	wchar_t* m_wchar;//定义宽字指针
	//取多字长度
	int len = MultiByteToWideChar(
		CP_ACP, //代码面
		0, //标志
		cchar, //多字字符串
		strlen(cchar),//多字字符串长度 
		NULL,//宽字字符串 
		0);//宽字字符串长度
	m_wchar = new wchar_t[len + 1];//为宽字指针分配内存
	MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), m_wchar, len);//复制多字到宽字
	m_wchar[len] = '\0';//字符串结尾
	return m_wchar;//返回指针
}

//宽字转多字 wchar_t to char

char* wchar2char(const wchar_t* wchar)
{
	char* m_char;//定义多字指针
	int len = WideCharToMultiByte(CP_ACP, 0, wchar, wcslen(wchar), NULL, 0, NULL, NULL);//取宽字长度
	m_char = new char[len + 1];//为多字指针分配内存
	WideCharToMultiByte(CP_ACP, 0, wchar, wcslen(wchar), m_char, len, NULL, NULL);//复制宽字到多字
	m_char[len] = '\0';//字符串结尾
	return m_char;//返回多字
}


//初始化背景
//画渐变的天空
void Init::drawBackground()
{
	initgraph(800, 600);	// 创建绘图窗口，大小为 800*600
	float H = 190;		// 色相
	float S = 1;		// 饱和度
	float L = 0.7f;		// 亮度
	for (int y = 0; y < 600; y++)
	{
		L += 0.0005f;
		setlinecolor(HSLtoRGB(H, S, L));
		line(0, y, 800, y);
	}
}


//鼠标在某矩形范围内的检测
bool Init::Check(int x1, int x2, int y1, int y2, ExMessage* m)
{
	return (m->x <= x2 && m->x >= x1 && m->y <= y2 && m->y >= y1);
}


//进入与退出界面
//进入---draw2()
void Init::draw1()
{
	drawBackground();
	settextMSG();
	outtextxy(250, 200, _T("学生选课系统"));
	outtextxy(250, 350, _T("进入"));
	outtextxy(434, 350, _T("退出"));
	while (true)
	{
		ExMessage m;
		m = getmessage(EM_MOUSE);
		if (Check(250, 348, 350, 398, &m))
		{
			settextcolor(RED);
			outtextxy(250, 350, _T("进入"));
			settextcolor(BLACK);
			outtextxy(434, 350, _T("退出"));
			if (m.lbutton)
			{
				draw2();
				break;
			}
		}
		else if (Check(434, 530, 350, 398, &m))
		{
			settextcolor(BLACK);
			outtextxy(250, 350, _T("进入"));
			settextcolor(RED);
			outtextxy(434, 350, _T("退出"));
			if (m.lbutton)
			{
				drawExit();
			}
		}
		else
		{
			settextcolor(BLACK);
			outtextxy(250, 350, _T("进入"));
			settextcolor(BLACK);
			outtextxy(434, 350, _T("退出"));
		}
	}
}


//学生与管理员
//学生---draw3()
//管理员---draw4()
void Init::draw2()
{
	drawBackground();
	settextMSG();
	outtextxy(250, 270, _T("学生"));
	outtextxy(434, 270, _T("管理员"));
	while (true)
	{
		ExMessage m;
		m = getmessage(EM_MOUSE);
		if (Check(250, 348, 270, 318, &m))
		{
			settextcolor(RED);
			outtextxy(250, 270, _T("学生"));
			settextcolor(BLACK);
			outtextxy(434, 270, _T("管理员"));
			outtextxy(700, 500, _T("返回"));
			outtextxy(700, 550, _T("退出"));
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
			outtextxy(700, 500, _T("返回"));
			settextcolor(BLACK);
			outtextxy(700, 550, _T("退出"));
			outtextxy(250, 270, _T("学生"));
			outtextxy(434, 270, _T("管理员"));
			if (m.lbutton)
			{
				draw1();
			}
		}
		else if (Check(700, 800, 550, 600, &m))
		{
			settextcolor(BLACK);
			outtextxy(700, 500, _T("返回"));
			outtextxy(250, 270, _T("学生"));
			outtextxy(434, 270, _T("管理员"));
			settextcolor(RED);
			outtextxy(700, 550, _T("退出"));
			if (m.lbutton)
			{
				drawExit();
			}
		}
		else if (Check(434, 578, 270, 318, &m))
		{
			settextcolor(BLACK);
			outtextxy(250, 270, _T("学生"));
			outtextxy(700, 500, _T("返回"));
			outtextxy(700, 550, _T("退出"));
			settextcolor(RED);
			outtextxy(434, 270, _T("管理员"));
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
			outtextxy(250, 270, _T("学生"));
			settextcolor(BLACK);
			outtextxy(434, 270, _T("管理员"));
			outtextxy(700, 500, _T("返回"));
			outtextxy(700, 550, _T("退出"));
			student = 0;
			administrator = 0;
		}
	}
}


//学生的学号与密码输入
void Init::draw3()
{
again:
	drawBackground();
	// 定义字符串缓冲区，并接收用户输入
	wchar_t s1[10];
	InputBox(s1, 10, L"请输入学号", L"学生");
	wchar_t s2[10];
	InputBox(s2, 10, L"请输入密码", L"学生");
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


//管理员密码输入
void Init::draw4()
{
	drawBackground();
	// 定义字符串缓冲区，并接收用户输入
	wchar_t s[10];
	int i = 0;
	while (strcmp(wchar2char(s), "123456") != 0)
	{
		i++;
		InputBox(s, 10, L"请输入密码", L"管理员");
		if (i == 5)
			exit(-1);
	}
}


//学生选课界面
void Init::draw5()
{
	drawBackground();
	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfHeight = 22;						// 设置字体高度为 22
	_tcscpy(f.lfFaceName, _T("宋体"));	// 设置字体为“华文行楷”
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
	settextstyle(&f);						// 设置字体样式
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	outtextxy(0, 0, _T("编号"));
	outtextxy(50, 0, _T("名称"));
	outtextxy(150, 0, _T("性质"));
	outtextxy(250, 0, _T("学时"));
	outtextxy(300, 0, _T("学分"));
	outtextxy(350, 0, _T("开课学期"));
	outtextxy(500, 0, _T("选课"));
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
	outtextxy(650, 550, _T("已选好，退出"));
	if (student)
	{
		int arr[26] = { 0 };//放循环外面
		while (true)
		{
			ExMessage m;
			m = getmessage(EM_MOUSE);
			if (Check(650, 780, 550, 570, &m))
			{
				settextcolor(RED);
				outtextxy(650, 550, _T("已选好，退出"));
				if (m.lbutton)
				{
					drawExit();
				}
			}
			else
			{
				settextcolor(BLACK);
				outtextxy(650, 550, _T("已选好，退出"));
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
							cerr << "文件打开失败!" << endl;
						}
						char str[26][4] = { "A++","B++","C++","D++","E++","F++","G++","H++","I++","J++","K++","L++",
							"M++","N++","O++","P++","Q++","R++","S++","T++","U++","V++","W++","X++" ,"Y++" ,"Z++" };
						arr[i - 1] ^= 1;//神奇的位运算
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


//学生信息浏览---draw7()
//课程信息浏览---draw8()
//按学分查询课程---draw9()
//某课程学生选修情况---draw10()
//某学生选课情况---draw11()
//数据整理---draw12()
void Init::draw6()
{
	drawBackground();
	settextMSG();
	outtextxy(150, 0, _T("学生信息浏览"));
	outtextxy(150, 100, _T("课程信息浏览"));
	outtextxy(150, 200, _T("按学分查询课程"));
	outtextxy(150, 300, _T("某课程学生选修情况"));
	outtextxy(150, 400, _T("某学生选课情况"));
	outtextxy(150, 500, _T("数据整理"));
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
				outtextxy(700, 500, _T("返回"));
				settextcolor(BLACK);
				outtextxy(700, 550, _T("退出"));
				outtextxy(150, 0, _T("学生信息浏览"));
				outtextxy(150, 100, _T("课程信息浏览"));
				outtextxy(150, 200, _T("按学分查询课程"));
				outtextxy(150, 300, _T("某课程学生选修情况"));
				outtextxy(150, 400, _T("某学生选课情况"));
				outtextxy(150, 500, _T("数据整理"));
				if (m.lbutton)
				{
					draw2();
				}
			}
			else if (Check(700, 800, 550, 600, &m))
			{
				settextcolor(BLACK);
				outtextxy(700, 500, _T("返回"));
				outtextxy(150, 0, _T("学生信息浏览"));
				outtextxy(150, 100, _T("课程信息浏览"));
				outtextxy(150, 200, _T("按学分查询课程"));
				outtextxy(150, 300, _T("某课程学生选修情况"));
				outtextxy(150, 400, _T("某学生选课情况"));
				outtextxy(150, 500, _T("数据整理"));
				settextcolor(RED);
				outtextxy(700, 550, _T("退出"));
				if (m.lbutton)
				{
					drawExit();
				}
			}
			else if (Check(150, 430, 0, 50, &m))
			{
				settextcolor(RED);
				outtextxy(150, 0, _T("学生信息浏览"));
				settextcolor(BLACK);
				outtextxy(150, 100, _T("课程信息浏览"));
				outtextxy(150, 200, _T("按学分查询课程"));
				outtextxy(150, 300, _T("某课程学生选修情况"));
				outtextxy(150, 400, _T("某学生选课情况"));
				outtextxy(150, 500, _T("数据整理"));
				outtextxy(700, 500, _T("返回"));
				outtextxy(700, 550, _T("退出"));
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
				outtextxy(150, 100, _T("课程信息浏览"));
				settextcolor(BLACK);
				outtextxy(150, 0, _T("学生信息浏览"));
				outtextxy(150, 200, _T("按学分查询课程"));
				outtextxy(150, 300, _T("某课程学生选修情况"));
				outtextxy(150, 400, _T("某学生选课情况"));
				outtextxy(150, 500, _T("数据整理"));
				outtextxy(700, 500, _T("返回"));
				outtextxy(700, 550, _T("退出"));
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
				outtextxy(150, 200, _T("按学分查询课程"));
				settextcolor(BLACK);
				outtextxy(150, 0, _T("学生信息浏览"));
				outtextxy(150, 100, _T("课程信息浏览"));
				outtextxy(150, 300, _T("某课程学生选修情况"));
				outtextxy(150, 400, _T("某学生选课情况"));
				outtextxy(150, 500, _T("数据整理"));
				outtextxy(700, 500, _T("返回"));
				outtextxy(700, 550, _T("退出"));
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
				outtextxy(150, 300, _T("某课程学生选修情况"));
				settextcolor(BLACK);
				outtextxy(150, 0, _T("学生信息浏览"));
				outtextxy(150, 100, _T("课程信息浏览"));
				outtextxy(150, 200, _T("按学分查询课程"));
				outtextxy(150, 400, _T("某学生选课情况"));
				outtextxy(150, 500, _T("数据整理"));
				outtextxy(700, 500, _T("返回"));
				outtextxy(700, 550, _T("退出"));
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
				outtextxy(150, 400, _T("某学生选课情况"));
				settextcolor(BLACK);
				outtextxy(150, 0, _T("学生信息浏览"));
				outtextxy(150, 100, _T("课程信息浏览"));
				outtextxy(150, 200, _T("按学分查询课程"));
				outtextxy(150, 300, _T("某课程学生选修情况"));
				outtextxy(150, 500, _T("数据整理"));
				outtextxy(700, 500, _T("返回"));
				outtextxy(700, 550, _T("退出"));
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
				outtextxy(150, 500, _T("数据整理"));
				settextcolor(BLACK);
				outtextxy(150, 0, _T("学生信息浏览"));
				outtextxy(150, 100, _T("课程信息浏览"));
				outtextxy(150, 200, _T("按学分查询课程"));
				outtextxy(150, 300, _T("某课程学生选修情况"));
				outtextxy(150, 400, _T("某学生选课情况"));
				outtextxy(700, 500, _T("返回"));
				outtextxy(700, 550, _T("退出"));
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
				outtextxy(150, 0, _T("学生信息浏览"));
				outtextxy(150, 100, _T("课程信息浏览"));
				outtextxy(150, 200, _T("按学分查询课程"));
				outtextxy(150, 300, _T("某课程学生选修情况"));
				outtextxy(150, 400, _T("某学生选课情况"));
				outtextxy(150, 500, _T("数据整理"));
				outtextxy(700, 500, _T("返回"));
				outtextxy(700, 550, _T("退出"));
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
					outtextxy(700, 500, _T("返回"));
					settextcolor(BLACK);
					outtextxy(700, 550, _T("退出"));
					if (m.lbutton)
					{
						draw6();
					}
				}
				else if (Check(700, 800, 550, 600, &m))
				{
					settextcolor(BLACK);
					outtextxy(700, 500, _T("返回"));
					settextcolor(RED);
					outtextxy(700, 550, _T("退出"));
					if (m.lbutton)
					{
						drawExit();
					}
				}
				else
				{
					settextcolor(BLACK);
					outtextxy(700, 500, _T("返回"));
					outtextxy(700, 550, _T("退出"));
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
					outtextxy(700, 500, _T("返回"));
					settextcolor(BLACK);
					outtextxy(700, 550, _T("退出"));
					if (m.lbutton)
					{
						draw6();
					}
				}
				else if (Check(700, 800, 550, 600, &m))
				{
					settextcolor(BLACK);
					outtextxy(700, 500, _T("返回"));
					settextcolor(RED);
					outtextxy(700, 550, _T("退出"));
					if (m.lbutton)
					{
						drawExit();
					}
				}
				else
				{
					settextcolor(BLACK);
					outtextxy(700, 500, _T("返回"));
					outtextxy(700, 550, _T("退出"));
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
					outtextxy(700, 500, _T("返回"));
					settextcolor(BLACK);
					outtextxy(700, 550, _T("退出"));
					if (m.lbutton)
					{
						draw6();
					}
				}
				else if (Check(700, 800, 550, 600, &m))
				{
					settextcolor(BLACK);
					outtextxy(700, 500, _T("返回"));
					settextcolor(RED);
					outtextxy(700, 550, _T("退出"));
					if (m.lbutton)
					{
						drawExit();
					}
				}
				else
				{
					settextcolor(BLACK);
					outtextxy(700, 500, _T("返回"));
					outtextxy(700, 550, _T("退出"));
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
					outtextxy(700, 500, _T("返回"));
					settextcolor(BLACK);
					outtextxy(700, 550, _T("退出"));
					if (m.lbutton)
					{
						draw6();
					}
				}
				else if (Check(700, 800, 550, 600, &m))
				{
					settextcolor(BLACK);
					outtextxy(700, 500, _T("返回"));
					settextcolor(RED);
					outtextxy(700, 550, _T("退出"));
					if (m.lbutton)
					{
						drawExit();
					}
				}
				else
				{
					settextcolor(BLACK);
					outtextxy(700, 500, _T("返回"));
					outtextxy(700, 550, _T("退出"));
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
					outtextxy(700, 500, _T("返回"));
					settextcolor(BLACK);
					outtextxy(700, 550, _T("退出"));
					if (m.lbutton)
					{
						draw6();
					}
				}
				else if (Check(700, 800, 550, 600, &m))
				{
					settextcolor(BLACK);
					outtextxy(700, 500, _T("返回"));
					settextcolor(RED);
					outtextxy(700, 550, _T("退出"));
					if (m.lbutton)
					{
						drawExit();
					}
				}
				else
				{
					settextcolor(BLACK);
					outtextxy(700, 500, _T("返回"));
					outtextxy(700, 550, _T("退出"));
				}
			}
		}
		if (arr[5])
		{
			draw12();
		}
	}
}


//学生信息浏览
void Init::draw7()
{
	drawBackground();
	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfHeight = 20;						// 设置字体高度为 48
	_tcscpy(f.lfFaceName, _T("宋体"));	// 设置字体为“华文行楷”
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
	settextstyle(&f);						// 设置字体样式
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	StudentNode _list;
	StudentNode* head = _list.createStudent();
	_list.StudentPrint(head);
	outtextxy(50, 0, _T("学号"));
	outtextxy(150, 0, _T("姓名"));
	outtextxy(250, 0, _T("选课情况"));
	settextMSG();
	outtextxy(700, 500, _T("返回"));
	outtextxy(700, 550, _T("退出"));
}


//课程信息浏览
void Init::draw8()
{
	drawBackground();
	settextMSG();
	outtextxy(700, 500, _T("返回"));
	outtextxy(700, 550, _T("退出"));
	settextMSG();
	settextcolor(BLACK);
	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfHeight = 22;						// 设置字体高度为 22
	_tcscpy(f.lfFaceName, _T("宋体"));	// 设置字体为“华文行楷”
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
	settextstyle(&f);						// 设置字体样式
	setbkmode(TRANSPARENT);
	outtextxy(0, 0, _T("编号"));
	outtextxy(50, 0, _T("名称"));
	outtextxy(150, 0, _T("性质"));
	outtextxy(250, 0, _T("学时"));
	outtextxy(300, 0, _T("学分"));
	outtextxy(350, 0, _T("开课学期"));
	outtextxy(500, 0, _T("选课人数"));
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
			outtextxy(700, 550, _T("退出"));
			settextcolor(BLACK);
			outtextxy(700, 500, _T("返回"));
			if (m.lbutton)
			{
				drawExit();
			}
		}
		else if (Check(700, 800, 500, 550, &m))
		{
			settextMSG();
			settextcolor(RED);
			outtextxy(700, 500, _T("返回"));
			settextcolor(BLACK);
			outtextxy(700, 550, _T("退出"));
			if (m.lbutton)
			{
				draw6();
			}
		}
		else
		{
			settextMSG();
			settextcolor(BLACK);
			outtextxy(700, 500, _T("返回"));
			outtextxy(700, 550, _T("退出"));
		}
	}
}


//按学分查询课程
void Init::draw9()
{
	drawBackground();
	settextMSG();
	outtextxy(0, 0, _T("按学分查询课程"));
	wchar_t s[10];
	outtextxy(700, 500, _T("返回"));
	outtextxy(700, 550, _T("退出"));
	InputBox(s, 10, L"请输入学分", L"按学分查询课程");
	SListNode list;
	SListNode* phead = list.createSListCourse();
	SListNode* cur = phead;
	int k = 0;
	for (int i = 0; i < 26; i++)
	{
		if (stoi(s) == cur->data.credit)
		{
			settextMSG();
			outtextxy(0, 50, _T("学分为"));
			outtextxy(165, 50, _T("的课程有:"));
			TCHAR t[5];
			_stprintf(t, _T("%d"), cur->data.credit);
			outtextxy(140, 50, t);
			LOGFONT f;
			gettextstyle(&f);						// 获取当前字体设置
			f.lfHeight = 30;						// 设置字体高度为 20
			_tcscpy(f.lfFaceName, _T("宋体"));	// 设置字体为“宋体”
			f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
			settextstyle(&f);						// 设置字体样式
			setbkmode(TRANSPARENT);
			settextcolor(BLACK);
			outtextxy(400, 50 + 30 * k, char2wchar(cur->data.name));
			k++;
		}
		cur = cur->next;
	}
}


//某课程学生选修情况
void Init::draw10()
{
	drawBackground();
	settextMSG();
	outtextxy(0, 0, _T("某课程学生选修情况"));
	outtextxy(700, 500, _T("返回"));
	outtextxy(700, 550, _T("退出"));
	wchar_t s[10];
	InputBox(s, 10, L"请输入课程名", L"某课程学生选修情况");
	SListNode list;
	SListNode* phead = list.createSListCourse();
	SListNode* cur = phead;
	for (int i = 0; i < 26; i++)
	{
		if (strcmp(wchar2char(s), cur->data.name) == 0)
		{
			TCHAR t[5];
			outtextxy(250, 250, _T("选课人数:"));
			_stprintf(t, _T("%d"), cur->data.studentNum);
			outtextxy(450, 250, t);
		}
		cur = cur->next;
	}
}


//某学生选课情况
void Init::draw11()
{
	drawBackground();
	settextMSG();
	outtextxy(700, 500, _T("返回"));
	outtextxy(700, 550, _T("退出"));
	wchar_t s[10];
	InputBox(s, 10, L"请输入学生姓名", L"某学生选课情况");
	StudentNode _list;
	StudentNode* phead = _list.createStudent();
	StudentNode* cur = phead;
	for (int i = 0; i < 10; i++)
	{
		if (strcmp(wchar2char(s), cur->data.name) == 0)
		{
			settextMSG();
			outtextxy(0, 0, _T("选课情况:"));
			LOGFONT f;
			gettextstyle(&f);						// 获取当前字体设置
			f.lfHeight = 48;						// 设置字体高度为 48
			_tcscpy(f.lfFaceName, _T("宋体"));	// 设置字体为“华文行楷”
			f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
			settextstyle(&f);						// 设置字体样式
			setbkmode(TRANSPARENT);
			settextcolor(BLACK);
			outtextxy(0, 50, char2wchar(cur->data._course));
		}
		settextMSG();
		cur = cur->next;
	}
}


// 数据整理界面:
// 选课信息按学分排序---draw13()
// 选课信息按选修人数排序---draw14()
// 选课信息按课程编号排序---draw15()
void Init::draw12()
{
	drawBackground();
	settextMSG();
	outtextxy(0, 0, _T("数据整理"));
	outtextxy(0, 100, _T("选课信息按学分排序"));
	outtextxy(0, 300, _T("选课信息按选修人数排序"));
	outtextxy(0, 500, _T("选课信息按课程编号排序"));
	outtextxy(700, 500, _T("返回"));
	outtextxy(700, 550, _T("退出"));
	while (true)
	{
		ExMessage m;
		m = getmessage(EM_MOUSE);
		if (Check(700, 800, 500, 550, &m))
		{
			settextcolor(RED);
			outtextxy(700, 500, _T("返回"));
			settextcolor(BLACK);
			outtextxy(700, 550, _T("退出"));
			outtextxy(0, 100, _T("选课信息按学分排序"));
			outtextxy(0, 300, _T("选课信息按选修人数排序"));
			outtextxy(0, 500, _T("选课信息按课程编号排序"));
			if (m.lbutton)
			{
				draw6();
			}
		}
		else if (Check(700, 800, 550, 600, &m))
		{
			settextcolor(BLACK);
			outtextxy(700, 500, _T("返回"));
			outtextxy(0, 100, _T("选课信息按学分排序"));
			outtextxy(0, 300, _T("选课信息按选修人数排序"));
			outtextxy(0, 500, _T("选课信息按课程编号排序"));
			settextcolor(RED);
			outtextxy(700, 550, _T("退出"));
			if (m.lbutton)
			{
				drawExit();
			}
		}
		else if (Check(0, 410, 100, 150, &m))
		{
			settextcolor(RED);
			outtextxy(0, 100, _T("选课信息按学分排序"));
			if (m.lbutton)
			{
				draw13();
			}
			settextcolor(BLACK);
			outtextxy(0, 0, _T("数据整理"));
			outtextxy(0, 300, _T("选课信息按选修人数排序"));
			outtextxy(0, 500, _T("选课信息按课程编号排序"));
			outtextxy(700, 500, _T("返回"));
			outtextxy(700, 550, _T("退出"));
		}
		else if (Check(0, 510, 300, 350, &m))
		{
			settextcolor(RED);
			outtextxy(0, 300, _T("选课信息按选修人数排序"));
			if (m.lbutton)
			{
				draw14();
				break;
			}
			settextcolor(BLACK);
			outtextxy(0, 0, _T("数据整理"));
			outtextxy(0, 100, _T("选课信息按学分排序"));
			outtextxy(0, 500, _T("选课信息按课程编号排序"));
			outtextxy(700, 500, _T("返回"));
			outtextxy(700, 550, _T("退出"));
		}
		else if (Check(0, 510, 500, 550, &m))
		{
			settextcolor(RED);
			outtextxy(0, 500, _T("选课信息按课程编号排序"));
			if (m.lbutton)
			{
				draw15();
				break;
			}
			settextcolor(BLACK);
			outtextxy(0, 0, _T("数据整理"));
			outtextxy(0, 100, _T("选课信息按学分排序"));
			outtextxy(0, 300, _T("选课信息按选修人数排序"));
			outtextxy(700, 500, _T("返回"));
			outtextxy(700, 550, _T("退出"));
		}
		else
		{
			settextcolor(BLACK);
			outtextxy(0, 0, _T("数据整理"));
			outtextxy(0, 100, _T("选课信息按学分排序"));
			outtextxy(0, 300, _T("选课信息按选修人数排序"));
			outtextxy(0, 500, _T("选课信息按课程编号排序"));
			outtextxy(700, 500, _T("返回"));
			outtextxy(700, 550, _T("退出"));
		}
	}
}


//选课信息按学分排序
void Init::draw13()
{
	drawBackground();
	settextMSG();
	outtextxy(700, 500, _T("返回"));
	outtextxy(700, 550, _T("退出"));
	SListNode list;
	SListNode* phead = list.createSListCourse();
	list.sortByCredit(&phead);
	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfHeight = 20;						// 设置字体高度为 48
	_tcscpy(f.lfFaceName, _T("宋体"));	// 设置字体为“华文行楷”
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
	settextstyle(&f);						// 设置字体样式
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	list.SListPrint(phead);
	outtextxy(50, 0, _T("名称"));
	outtextxy(150, 0, _T("性质"));
	outtextxy(250, 0, _T("学时"));
	outtextxy(300, 0, _T("学分"));
	outtextxy(350, 0, _T("开课学期"));
	while (true)
	{
		ExMessage m;
		m = getmessage(EM_MOUSE);
		settextMSG();
		if (Check(700, 800, 550, 600, &m))
		{
			settextcolor(RED);
			outtextxy(700, 550, _T("退出"));
			settextcolor(BLACK);
			outtextxy(700, 500, _T("返回"));
			if (m.lbutton)
			{
				drawExit();
			}
		}
		else if (Check(700, 800, 500, 550, &m))
		{
			settextcolor(RED);
			outtextxy(700, 500, _T("返回"));
			settextcolor(BLACK);
			outtextxy(700, 550, _T("退出"));
			if (m.lbutton)
			{
				draw12();
			}
		}
		else
		{
			settextcolor(BLACK);
			outtextxy(700, 500, _T("返回"));
			outtextxy(700, 550, _T("退出"));
		}
	}
}


//选课信息按选修人数排序
void Init::draw14()
{
	drawBackground();
	settextMSG();
	outtextxy(700, 500, _T("返回"));
	outtextxy(700, 550, _T("退出"));
	SListNode list;
	SListNode* phead = list.createSListCourse();
	list.sortByStuNum(&phead);
	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfHeight = 20;						// 设置字体高度为 48
	_tcscpy(f.lfFaceName, _T("宋体"));	// 设置字体为“华文行楷”
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
	settextstyle(&f);						// 设置字体样式
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	list.SListPrint(phead);
	outtextxy(50, 0, _T("名称"));
	outtextxy(150, 0, _T("性质"));
	outtextxy(250, 0, _T("学时"));
	outtextxy(300, 0, _T("学分"));
	outtextxy(350, 0, _T("开课学期"));
	outtextxy(500, 0, _T("选课人数"));
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
			outtextxy(700, 550, _T("退出"));
			settextcolor(BLACK);
			outtextxy(700, 500, _T("返回"));
			if (m.lbutton)
			{
				drawExit();
			}
		}
		else if (Check(700, 800, 500, 550, &m))
		{
			settextcolor(RED);
			outtextxy(700, 500, _T("返回"));
			settextcolor(BLACK);
			outtextxy(700, 550, _T("退出"));
			if (m.lbutton)
			{
				draw12();
			}
		}
		else
		{
			settextcolor(BLACK);
			outtextxy(700, 500, _T("返回"));
			outtextxy(700, 550, _T("退出"));
		}
	}
}


//选课信息按课程编号排序
void Init::draw15()
{
	drawBackground();
	settextMSG();
	outtextxy(700, 500, _T("返回"));
	outtextxy(700, 550, _T("退出"));
	while (true)
	{
		ExMessage m;
		m = getmessage(EM_MOUSE);
		settextMSG();
		settextcolor(BLACK);
		LOGFONT f;
		gettextstyle(&f);						// 获取当前字体设置
		f.lfHeight = 22;						// 设置字体高度为 22
		_tcscpy(f.lfFaceName, _T("宋体"));	// 设置字体为“华文行楷”
		f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
		settextstyle(&f);						// 设置字体样式
		setbkmode(TRANSPARENT);
		outtextxy(0, 0, _T("编号"));
		outtextxy(50, 0, _T("名称"));
		outtextxy(150, 0, _T("性质"));
		outtextxy(250, 0, _T("学时"));
		outtextxy(300, 0, _T("学分"));
		outtextxy(350, 0, _T("开课学期"));
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
		outtextxy(700, 500, _T("返回"));
		outtextxy(700, 550, _T("退出"));
		if (Check(700, 800, 550, 600, &m))
		{
			settextMSG();
			settextcolor(RED);
			outtextxy(700, 550, _T("退出"));
			settextcolor(BLACK);
			outtextxy(700, 500, _T("返回"));
			if (m.lbutton)
			{
				drawExit();
			}
		}
		else if (Check(700, 800, 500, 550, &m))
		{
			settextMSG();
			settextcolor(RED);
			outtextxy(700, 500, _T("返回"));
			settextcolor(BLACK);
			outtextxy(700, 550, _T("退出"));
			if (m.lbutton)
			{
				draw12();
			}
		}
		else
		{
			settextMSG();
			settextcolor(BLACK);
			outtextxy(700, 500, _T("返回"));
			outtextxy(700, 550, _T("退出"));
		}
	}
}


//字体设置函数
void Init::settextMSG()
{
	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfHeight = 48;						// 设置字体高度为 48
	_tcscpy(f.lfFaceName, _T("华文行楷"));	// 设置字体为“华文行楷”
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
	settextstyle(&f);						// 设置字体样式
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
}


//退出函数
void Init::drawExit()
{
	cleardevice();
	settextMSG();
	settextcolor(WHITE);
	outtextxy(300, 275, _T("谢谢使用！"));
	Sleep(3000);
	exit(0);
}