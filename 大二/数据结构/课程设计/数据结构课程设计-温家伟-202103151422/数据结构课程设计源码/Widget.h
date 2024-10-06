#pragma once
#include "EasyX\Include\graphics.h"
#include <time.h>
#include <conio.h>
#include <string>
#include "Vector.hpp"
#include "List.hpp"

using std::wstring;

// 部件抽象基类
class Widget
{
public:
	Widget(const int& x = 0, const int& y = 0, const int& width = 100, const int& height = 60);
	virtual void show() const = 0;           // 纯虚函数，显示函数用多态来实现
protected:
	int _x;        // X 坐标
	int _y;        // Y 坐标
	int _width;    // 宽度
	int _height;   // 高度
};
