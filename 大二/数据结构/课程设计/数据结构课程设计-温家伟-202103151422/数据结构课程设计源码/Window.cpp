#include "Window.h"

// ���ַ���ת������
Bignum<List<int>> Window::wstring2Bignum(wstring str)
{
	Bignum<List<int>> ret;
	for (auto e : str)
	{
		ret.push_back(e - '0');
	}
	return ret;
}

Window::Window(const int& width, const int& height) : Widget(0, 0, width, height)
{
	show();

	// �������
	table = new Table(_manager, 10, 10, 502 - 20, 420 - 60);
	if (!_manager.read("data.txt"))
	{
		MessageBox(GetHWnd(), L"�ļ���ʧ�ܣ��޷�������в�����", L"����", MB_OK | MB_ICONERROR);
		exit(-1);
	}

	// ���û�ͼ��ʽ
	LOGFONT f;						// �ֵ����Խṹ��
	gettextstyle(&f);				// ��ȡ��ǰ������ʽ
	f.lfQuality = DEFAULT_QUALITY;	// ָ�����ֵ����������ָ�������������Ҫ
	settextstyle(&f);				// ���õ�ǰ������ʽ
	settextcolor(BLACK);			// ���õ�ǰ������ɫ
	setbkmode(TRANSPARENT);			// ���õ�ǰ�豸ͼ�������������ʱ�ı���ģʽ��������͸����
	setlinecolor(BLACK);			// ���õ�ǰ�豸������ɫ

	// ������ť
	mainWindow_leftnum = new Button((502 - 150) / 2, 105, 150, 40, L"�������");
	mainWindow_rightnum = new Button((502 - 150) / 2, 165, 150, 40, L"�Ҳ�����");
	mainWindow_sign = new Button((502 - 150) / 2, 225, 150, 40, L"������");
	mainWindow_RWfile = new Button((502 - 150) / 2, 285, 150, 40, L"�ļ�����");
	mainWindow_exit = new Button((502 - 150) / 2, 345, 150, 40, L"�˳�����");
	// ��ʾ������
	showMainWindow();

	RWfile_pageUp = new Button(10, 380, 100, 30, L"��һҳ");
	RWfile_pageDown = new Button(250, 380, 100, 30, L"��һҳ");
	RWfile_back = new Button(380, 380, 100, 30, L"����");
	// ����ѡ��
	while (_base != 2 && _base != 10)
		// ��������Ʋ�Ϊ2��10ʱ����������
	{
		wchar_t base[100];
		// �ԶԻ�����ʽ��ȡ�û�����
		if (InputBox(base, 100, L"��ѡ�����(2/10)��", L"����ѡ��", NULL, 0, 0, false))
		{
			std::wstringstream format(base);
			format >> _base;
		}
	}
}

void Window::messageLoop()
{
	ExMessage msg;			//���������Ϣ�Ľṹ��
	// ������Ϣѭ��
	while (true)
	{
		// ��ȡ���ж���Ϣ
		msg = getmessage();
		//showMainWindow();  
		// �ŵ����캯����ȥ�ˣ���Ȼ��˸̫����
		//https://tieba.baidu.com/p/2242135590
		//���InputBox�����ε�����	&& msg.message != WM_LBUTTONUP

		// �ж���ʾ����
		if (state == WindowState::mainWindow)		// ��������ʾ
		{
			// �����������
			if (mainWindow_leftnum->state(msg) && msg.message != WM_LBUTTONUP)
			{
				wchar_t leftnum[999];
				if (InputBox(leftnum, 999, L"���������������", L"�������", NULL, 0, 0, false))
				{
					wstring temp(leftnum);
					_left = wstring2Bignum(temp);
					//temp += ' ';
					//sstream�����̫������qwq
					// ������̫������ sad
					//std::wstringstream format(temp);
					//format.putback(' ');
					//format >> _left;
					//_left = wchar_t2Bignum(leftnum);
				}
			}
			// �����Ҳ�����
			else if (mainWindow_rightnum->state(msg) && msg.message != WM_LBUTTONUP)
			{
				wchar_t rightnum[999];
				if (InputBox(rightnum, 999, L"�������Ҳ�������", L"�Ҳ�����", NULL, 0, 0, false))
				{
					wstring temp(rightnum);
					_right = wstring2Bignum(temp);
				}
			}
			// ���������
			else if (mainWindow_sign->state(msg) && msg.message != WM_LBUTTONUP)
			{
				wchar_t sign[10];
				if (InputBox(sign, 10, L"�������������", L"������", NULL, 0, 0, false))
				{
					time_t start_time;
					time(&start_time);
					if (_base == 2)
					{
						_left.bin2dec();
						_right.bin2dec();
					}
					if (sign[0] == '+')
					{
						_ret = _left + _right;
					}
					else if (sign[0] == '-')
					{
						_ret = _left - _right;
					}
					else if (sign[0] == '*')
					{
						_ret = _left * _right;
					}
					else if (sign[0] == '/')
					{
						_ret = _left / _right;
					}
					else if (sign[0] == '%')
					{
						_ret = _left % _right;
					}
					else if (sign[0] == '^')
					{
						_ret = _left ^ _right;
					}
					if (_base == 2)
					{
						_ret.dec2bin();
					}
					time_t end_time;
					time(&end_time);
					wstring arr_bignum = _ret.Bignum2wstring();
					wstring temp = to_wstring(int(_ret.length()));
					arr_bignum.append(wstring(L"  (������λ��:"));
					arr_bignum.append(temp);
					arr_bignum.append(wstring(L")"));
					MessageBox(GetHWnd(), arr_bignum.c_str(), L"������Ϊ", MB_OK | MB_ICONINFORMATION);
					time_t time = end_time - start_time;
					wstring arr_second = to_wstring(int(time));
					arr_second.append(wstring(L"��"));
					MessageBox(GetHWnd(), arr_second.c_str(), L"��������ʱ��", MB_OK | MB_ICONINFORMATION);
					_manager.write("file.txt",_ret.Bignum_string());
				}
			}
			else if (mainWindow_RWfile->state(msg))
			{
				showViewBignums();
			}
			// �˳�����
			else if (mainWindow_exit->state(msg))
			{
				MessageBox(GetHWnd(), L"��лʹ�ã�", L"�˳�", MB_OK | MB_ICONINFORMATION);
				return;
			}
		}

		else if (state == Window::viewBigums)
		{
			if (RWfile_back->state(msg) && msg.message != WM_LBUTTONUP)
			{
				showMainWindow();
			}
			else if (RWfile_pageUp->state(msg) && msg.message != WM_LBUTTONUP)
			{
				table->pageUp();
			}
			else if (RWfile_pageDown->state(msg) && msg.message != WM_LBUTTONUP)
			{
				table->pageDown();
			}
		}
	}
}

void Window::showMainWindow()
{
	state = WindowState::mainWindow;
	cleardevice();
	// ���ر���ͼƬ
	loadimage(NULL, BACKGROUND_IMAGE, 502, 420);
	// ������ʾ����
	RECT rect = { 0, 0, _width, 100 };
	settextstyle(50, 0, L"΢���ź�");
	drawtext(L"WJW�Ĵ�����������", &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void Window::showViewBignums()
{
	state = WindowState::viewBigums;
	cleardevice();
	// ���ر���ͼƬ
	loadimage(NULL, BACKGROUND_IMAGE, 502, 420);
	
	// ��ʾ�ؼ�
	table->show();
	RWfile_pageUp->show();
	RWfile_pageDown->show();
	RWfile_back->show();
}

void Window::show() const
{
	// �½�����
	SetWindowText(initgraph(_width, _height, EW_NOCLOSE), L"WJW�Ĵ�����������");
	setbkcolor(WHITE);
	cleardevice();
}

void Window::close()
{
	closegraph();
}