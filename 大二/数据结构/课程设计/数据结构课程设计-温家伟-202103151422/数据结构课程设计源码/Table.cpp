#include "Table.h"

Table::Table(const Manager& manager, const int& x, const int& y
	, const int& width, const int& height) 
	: Widget(x, y, width, height)
	, manager(manager)
{
	curIndex = 0;
	searchIndex = -1;
}

void Table::show() const
{
	// 设置绘图样式
	setfillcolor(WHITE);

	// 绘制表格
	fillrectangle(_x, _y, _x + _width, _y + _height);

	// 画竖线
	for (int i = 130; i <= 370; i += 120)
	{
		line(i, 10, i, 10 + 360);
	}

	// 画横线
	for (int j = 40; j <= 340; j += 30)
	{
		line(10, j, 10 + 482, j);
	}

	RECT rect;

	// 绘制表头
	wchar_t header[5][5] = { L"左操作数",L"操作符", L"右操作数", L"结果"};	// 表头数据
	for (int i = 10, j = 0; i < 490 && j < 5; i += 120, j++)
	{
		rect = { i, 10, i + 120, 10 + 30 };
		drawtext(header[j], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	
	// 输出大整数数据
	
	size_t i = curIndex;
	
	for (int j = 40; j < 370; j += 30)
	{
		if (i < manager.size())	// 在不超出索引范围的情况下才读取数据
		{
			
			rect = { 10, j, 10 + 120, j + 30 };
			drawtext(manager.getBignums(i)._left.Bignum_wstring().c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			
			rect = { 130, j, 130 + 120, j + 30 };
			drawtext(manager.getBignums(i)._sign, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			rect = { 250, j, 250 + 120, j + 30 };
			drawtext(manager.getBignums(i)._right.Bignum_wstring().c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			rect = { 370, j, 370 + 120, j + 30 };
			drawtext(manager.getBignums(i)._result.Bignum_wstring().c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			
			i++;
		}
		else
		{
			break;
		}
	}
	
	// 绘制页数提示
	std::wstringstream format;
	setbkmode(OPAQUE);
	format << L"第" << (curIndex + 11) / 11 << L"页" << L"/" << L"共" << (manager.size() + 11) / 11 << L"页";
	outtextxy(127, 383, format.str().c_str());
	setbkmode(TRANSPARENT);
}

void Table::pageUp()
{
	// 输出大整数数据
	curIndex -= 11;
	if (curIndex > manager.size())	// 读取到第一页停止操作
	{
		curIndex += 11;
		return;
	}
	show();
}

void Table::pageDown()
{
	// 输出大整数数据
	curIndex += 11;
	if (curIndex > manager.size())	// 读取到最后一页停止操作
	{
		curIndex -= 11;
		return;
	}
	show();
}

void Table::showEditTable(const wchar_t* searchTerms)
{
	// 设置绘图样式
	setfillcolor(WHITE);

	// 绘制表格
	fillrectangle(_x, _y, _x + _width, _y + 60);

	// 画竖线
	for (int i = 130; i <= 370; i += 120)
	{
		line(i, 10, i, 10 + 60);
	}

	// 画横线
	line(10, 40, 490, 40);

	RECT rect;

	// 绘制表头
	wchar_t header[4][3] = { L"学号", L"姓名", L"班级", L"总分" };	// 表头数据
	for (int i = 10, j = 0; i < 490 && j < 4; i += 120, j++)
	{
		rect = { i, 10, i + 120, 10 + 30 };
		drawtext(header[j], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}

const int& Table::getSearchIndex() const
{
	return searchIndex;
}
