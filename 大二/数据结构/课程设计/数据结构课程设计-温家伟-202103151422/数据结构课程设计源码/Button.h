#pragma once
#include "Widget.h"
#include "Vector.hpp"
#include "List.hpp"

class Button :public Widget
{
public:
	Button(const int& x, const int& y, const int& width, 
	const int& height, const wstring& text);
	void show() const;
	bool state(const ExMessage& msg) const;
	const wstring& getText() const;
	void setText(const std::wstring& text);
	bool isIn(const ExMessage& msg) const;

private:
	wstring _text;                      // °´Å¥ÎÄ±¾
};