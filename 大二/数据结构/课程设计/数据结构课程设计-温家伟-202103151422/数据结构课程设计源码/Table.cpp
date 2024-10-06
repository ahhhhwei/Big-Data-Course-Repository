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
	// ���û�ͼ��ʽ
	setfillcolor(WHITE);

	// ���Ʊ��
	fillrectangle(_x, _y, _x + _width, _y + _height);

	// ������
	for (int i = 130; i <= 370; i += 120)
	{
		line(i, 10, i, 10 + 360);
	}

	// ������
	for (int j = 40; j <= 340; j += 30)
	{
		line(10, j, 10 + 482, j);
	}

	RECT rect;

	// ���Ʊ�ͷ
	wchar_t header[5][5] = { L"�������",L"������", L"�Ҳ�����", L"���"};	// ��ͷ����
	for (int i = 10, j = 0; i < 490 && j < 5; i += 120, j++)
	{
		rect = { i, 10, i + 120, 10 + 30 };
		drawtext(header[j], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	
	// �������������
	
	size_t i = curIndex;
	
	for (int j = 40; j < 370; j += 30)
	{
		if (i < manager.size())	// �ڲ�����������Χ������²Ŷ�ȡ����
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
	
	// ����ҳ����ʾ
	std::wstringstream format;
	setbkmode(OPAQUE);
	format << L"��" << (curIndex + 11) / 11 << L"ҳ" << L"/" << L"��" << (manager.size() + 11) / 11 << L"ҳ";
	outtextxy(127, 383, format.str().c_str());
	setbkmode(TRANSPARENT);
}

void Table::pageUp()
{
	// �������������
	curIndex -= 11;
	if (curIndex > manager.size())	// ��ȡ����һҳֹͣ����
	{
		curIndex += 11;
		return;
	}
	show();
}

void Table::pageDown()
{
	// �������������
	curIndex += 11;
	if (curIndex > manager.size())	// ��ȡ�����һҳֹͣ����
	{
		curIndex -= 11;
		return;
	}
	show();
}

void Table::showEditTable(const wchar_t* searchTerms)
{
	// ���û�ͼ��ʽ
	setfillcolor(WHITE);

	// ���Ʊ��
	fillrectangle(_x, _y, _x + _width, _y + 60);

	// ������
	for (int i = 130; i <= 370; i += 120)
	{
		line(i, 10, i, 10 + 60);
	}

	// ������
	line(10, 40, 490, 40);

	RECT rect;

	// ���Ʊ�ͷ
	wchar_t header[4][3] = { L"ѧ��", L"����", L"�༶", L"�ܷ�" };	// ��ͷ����
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
