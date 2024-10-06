#include "Window.h"

// 宽字符串转大整数
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

	// 创建表格
	table = new Table(_manager, 10, 10, 502 - 20, 420 - 60);
	if (!_manager.read("data.txt"))
	{
		MessageBox(GetHWnd(), L"文件打开失败，无法对其进行操作！", L"错误", MB_OK | MB_ICONERROR);
		exit(-1);
	}

	// 设置绘图样式
	LOGFONT f;						// 字的属性结构体
	gettextstyle(&f);				// 获取当前文字样式
	f.lfQuality = DEFAULT_QUALITY;	// 指定文字的输出质量，指定输出质量不重要
	settextstyle(&f);				// 设置当前文字样式
	settextcolor(BLACK);			// 设置当前文字颜色
	setbkmode(TRANSPARENT);			// 设置当前设备图案填充和文字输出时的背景模式，背景是透明的
	setlinecolor(BLACK);			// 设置当前设备画线颜色

	// 创建按钮
	mainWindow_leftnum = new Button((502 - 150) / 2, 105, 150, 40, L"左操作数");
	mainWindow_rightnum = new Button((502 - 150) / 2, 165, 150, 40, L"右操作数");
	mainWindow_sign = new Button((502 - 150) / 2, 225, 150, 40, L"操作符");
	mainWindow_RWfile = new Button((502 - 150) / 2, 285, 150, 40, L"文件操作");
	mainWindow_exit = new Button((502 - 150) / 2, 345, 150, 40, L"退出程序");
	// 显示主界面
	showMainWindow();

	RWfile_pageUp = new Button(10, 380, 100, 30, L"上一页");
	RWfile_pageDown = new Button(250, 380, 100, 30, L"下一页");
	RWfile_back = new Button(380, 380, 100, 30, L"返回");
	// 进制选择
	while (_base != 2 && _base != 10)
		// 当输入进制不为2或10时，持续输入
	{
		wchar_t base[100];
		// 以对话框形式获取用户输入
		if (InputBox(base, 100, L"请选择进制(2/10)：", L"进制选择", NULL, 0, 0, false))
		{
			std::wstringstream format(base);
			format >> _base;
		}
	}
}

void Window::messageLoop()
{
	ExMessage msg;			//保存鼠标消息的结构体
	// 开启消息循环
	while (true)
	{
		// 获取并判断消息
		msg = getmessage();
		//showMainWindow();  
		// 放到构造函数里去了，不然闪烁太严重
		//https://tieba.baidu.com/p/2242135590
		//解决InputBox弹两次的问题	&& msg.message != WM_LBUTTONUP

		// 判断显示界面
		if (state == WindowState::mainWindow)		// 主窗口显示
		{
			// 输入左操作数
			if (mainWindow_leftnum->state(msg) && msg.message != WM_LBUTTONUP)
			{
				wchar_t leftnum[999];
				if (InputBox(leftnum, 999, L"请输入左操作数：", L"左操作数", NULL, 0, 0, false))
				{
					wstring temp(leftnum);
					_left = wstring2Bignum(temp);
					//temp += ' ';
					//sstream这个类太好用了qwq
					// 不不不太难用了 sad
					//std::wstringstream format(temp);
					//format.putback(' ');
					//format >> _left;
					//_left = wchar_t2Bignum(leftnum);
				}
			}
			// 输入右操作数
			else if (mainWindow_rightnum->state(msg) && msg.message != WM_LBUTTONUP)
			{
				wchar_t rightnum[999];
				if (InputBox(rightnum, 999, L"请输入右操作数：", L"右操作数", NULL, 0, 0, false))
				{
					wstring temp(rightnum);
					_right = wstring2Bignum(temp);
				}
			}
			// 输入操作符
			else if (mainWindow_sign->state(msg) && msg.message != WM_LBUTTONUP)
			{
				wchar_t sign[10];
				if (InputBox(sign, 10, L"请输入操作符：", L"操作符", NULL, 0, 0, false))
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
					arr_bignum.append(wstring(L"  (大整数位数:"));
					arr_bignum.append(temp);
					arr_bignum.append(wstring(L")"));
					MessageBox(GetHWnd(), arr_bignum.c_str(), L"计算结果为", MB_OK | MB_ICONINFORMATION);
					time_t time = end_time - start_time;
					wstring arr_second = to_wstring(int(time));
					arr_second.append(wstring(L"秒"));
					MessageBox(GetHWnd(), arr_second.c_str(), L"计算所用时间", MB_OK | MB_ICONINFORMATION);
					_manager.write("file.txt",_ret.Bignum_string());
				}
			}
			else if (mainWindow_RWfile->state(msg))
			{
				showViewBignums();
			}
			// 退出程序
			else if (mainWindow_exit->state(msg))
			{
				MessageBox(GetHWnd(), L"感谢使用！", L"退出", MB_OK | MB_ICONINFORMATION);
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
	// 加载背景图片
	loadimage(NULL, BACKGROUND_IMAGE, 502, 420);
	// 绘制提示文字
	RECT rect = { 0, 0, _width, 100 };
	settextstyle(50, 0, L"微软雅黑");
	drawtext(L"WJW的大整数计算器", &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void Window::showViewBignums()
{
	state = WindowState::viewBigums;
	cleardevice();
	// 加载背景图片
	loadimage(NULL, BACKGROUND_IMAGE, 502, 420);
	
	// 显示控件
	table->show();
	RWfile_pageUp->show();
	RWfile_pageDown->show();
	RWfile_back->show();
}

void Window::show() const
{
	// 新建窗口
	SetWindowText(initgraph(_width, _height, EW_NOCLOSE), L"WJW的大整数计算器");
	setbkcolor(WHITE);
	cleardevice();
}

void Window::close()
{
	closegraph();
}