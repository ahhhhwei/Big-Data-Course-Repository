#pragma once
#include "EasyX\Include\graphics.h"
#include <time.h>
#include <conio.h>
#include <string>
#include "Vector.hpp"
#include "List.hpp"

using std::wstring;

// �����������
class Widget
{
public:
	Widget(const int& x = 0, const int& y = 0, const int& width = 100, const int& height = 60);
	virtual void show() const = 0;           // ���麯������ʾ�����ö�̬��ʵ��
protected:
	int _x;        // X ����
	int _y;        // Y ����
	int _width;    // ���
	int _height;   // �߶�
};
