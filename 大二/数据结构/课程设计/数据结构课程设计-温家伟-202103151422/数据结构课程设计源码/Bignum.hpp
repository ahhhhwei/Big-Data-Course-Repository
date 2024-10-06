#pragma once
#include <list>
#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include "Vector.hpp"
#include "List.hpp"
#include "Algorithm.hpp"
using namespace std;
template<class Container = List<int>>
//考虑用容器适配器封装，顺序容器的迭代器全部实现以此统一成员函数的实现逻辑
class Bignum
{
public:

	//正向迭代器的头
	typename Container::iterator begin()
	{
		return _con.begin();
	}

	//反向迭代器的头
	typename Container::reverse_iterator rbegin()
	{
		return _con.rbegin();
	}

	//正向迭代器的尾
	typename Container::iterator end()
	{
		return _con.end();
	}

	//反向迭代器的尾
	typename Container::reverse_iterator rend()
	{
		return _con.rend();
	}

	//大整数的长度
	size_t length()const
	{
		return _con.size();
	}

	//输入
	void push_back(int val)
	{
		_con.push_back(val);
	}

	//重载>
	bool operator>(const Bignum& right)const
	{
		//先比较长度，长度大的数值大
		if (length() > right.length())
		{
			return true;
		}
		else if (length() < right.length())
		{
			return false;
		}
		//再逐个比较，相等就接着比
		else
		{
			auto it = _con.begin();
			auto right_it = right._con.begin();
			while (it != _con.end())
			{
				if (*it < *right_it)
				{
					return false;
				}
				else if (*it > *right_it)
				{
					return true;
				}
				else
				{
					++it;
					++right_it;
				}
			}
			return false;//循环结束的话说明两者相等
		}
	}

	//重载>=
	bool operator>=(const Bignum& right)const
	{
		return (*this > right) || (*this == right);
	}

	//重载<
	bool operator<(const Bignum& right)const
	{
		return !(*this >= right);
	}

	//重载<=
	bool operator<=(const Bignum& right)const
	{
		return (*this < right) || (*this == right);
	}

	//重载==
	bool operator==(const Bignum& right)const
	{
		if (length() != right.length())
		{
			return false;
		}
		else
		{
			auto it_con = _con.begin();
			auto it_right = right._con.begin();
			while (it_con != _con.end())
			{
				if (*it_con != *it_right)
				{
					return false;
				}
				else
				{
					++it_con;
					++it_right;
				}
			}
		}
		return true;
	}

	//重载!=
	bool operator!=(const Bignum& right)const
	{
		return !(*this == right);
	}

	//重载+
	Bignum operator+(const Bignum& right)const
	{
		int carry = 0;										// 进位
		Bignum ret;
		auto it_con = _con.rbegin();
		auto it_right = right._con.rbegin();
		while (it_con != _con.rend() || it_right != right._con.rend())
		{
			if (it_con == _con.rend())
			{
				ret.push_back((*it_right + carry) % 10);
				carry = (*it_right + carry) / 10;
				it_right++;
			}
			else if (it_right == right._con.rend())
			{
				ret.push_back((*it_con + carry) % 10);
				carry = (*it_con + carry) / 10;
				it_con++;
			}
			else
			{
				ret.push_back((*it_con + *it_right + carry) % 10);
				carry = (*it_con + *it_right + carry) / 10;
				it_con++;
				it_right++;
			}
		}
		if (carry)
		{
			ret.push_back(carry);
		}
		Reverse(ret.begin(), ret.end());
		return ret;
	}

	//重载+=
	Bignum& operator+=(const Bignum& right)
	{
		*this = *this + right;
		return *this;
	}

	//重载-
	Bignum operator-(const Bignum& right)
	{
		Bignum ret;
		if (*this == right)
		{
			Bignum zero;
			zero.push_back(0);
			return zero;
		}
		else if (*this > right)
		{
			for (auto e : right._con)
			{
				ret.push_back(e * -1);
			}
			ret += *this;
			while (*ret._con.begin() == 0)
			{
				ret._con.erase(ret.begin());
			}
			auto it = ret._con.rbegin();
			int borrow = 0;
			while (it != ret._con.rend())
			{
				if (*it < 0)
				{
					*it = 10 - borrow + *it;
					borrow = 1;
				}
				else if (*it > 0)
				{
					*it = *it - borrow;
					borrow = 0;
				}
				else
				{
					if (borrow)
					{
						*it = 10 - borrow + *it;
					}
				}
				++it;
			}
			while (*ret._con.begin() == 0)
			{
				ret._con.erase(ret.begin());
			}
		}
		else
		{
			ret = right - *this;
			*ret._con.begin() *= -1;
		}
		return ret;
	}

	Bignum operator-(const Bignum& right)const
	{
		Bignum ret;
		if (*this == right)
		{
			Bignum zero;
			zero.push_back(0);
			return zero;
		}
		else if (*this > right)
		{
			for (auto e : right._con)
			{
				ret.push_back(e * -1);
			}
			ret += *this;
			while (*ret._con.begin() == 0)
			{
				ret._con.erase(ret.begin());
			}
			auto it = ret._con.rbegin();
			int borrow = 0;
			while (it != ret._con.rend())
			{
				if (*it < 0)
				{
					*it = 10 - borrow + *it;
					borrow = 1;
				}
				else if (*it > 0)
				{
					*it = *it - borrow;
					borrow = 0;
				}
				else
				{
					if (borrow)
					{
						*it = 10 - borrow + *it;
					}
				}
				++it;
			}
			while (*ret._con.begin() == 0)
			{
				ret._con.erase(ret.begin());
			}
		}
		else
		{
			ret = right - *this;
			*ret._con.begin() *= -1;
		}
		return ret;
	}

	//重载-=
	Bignum& operator-=(const Bignum& right)
	{
		*this = *this - right;
		return *this;
	}

	//重载*
	Bignum operator*(const Bignum& right)
	{
		Bignum ret;
		auto it = right._con.rbegin();
		int N = 0;
		while (it != right._con.rend())
		{
			//调用工具函数
			Bignum temp = (_miniMul(*it, *this));
			for (int i = 0; i < N; ++i)
			{
				temp.push_back(0);
			}
			N++;
			ret += temp;
			++it;
		}
		return ret;
	}

	//重载*=
	Bignum& operator*=(const Bignum& right)
	{
		*this = *this * right;
		return *this;
	}

	//重载/
	Bignum operator/(const Bignum& right)
	{
		Bignum ret;
		Bignum zero;
		zero.push_back(0);
		if (*this < right)
		{
			ret.push_back(0);
		}
		else if (*this == right)
		{
			ret.push_back(1);
		}
		else
		{
			//模拟竖式除法
			Bignum temp;
			auto it = _con.begin();
			for (size_t i = 0; i < right.length() - 1; ++i)
			{
				temp.push_back(*it);
				++it;
			}
			temp.push_back(*it);
			while (it != _con.end())
			{
				for (int i = 9; i >= 0; --i)
				{
					if (_miniMul(i, right) <= temp)
					{
						{
							ret.push_back(i);
						}
						temp -= _miniMul(i, right);
						if (it + 1 != _con.end())
							//if (it != --_con.end())
						{
							if (temp == zero)
							{
								//temp._con.erase(temp.begin(), temp.begin() + 1);
								temp._con.erase(temp.begin());
							}
							temp.push_back(*(it + 1));
						}
						break;
					}
				}
				++it;
			}
			/*if (temp == zero)
			{
				ret._con.erase(--ret.end());
			}*/
		}
		if (*ret.begin() == 0 && ret._con.size() != 1)
			//if (ret._con[0] == 0 && ret._con.size() != 1)
		{
			ret._con.erase(ret.begin());
			//ret._con.erase(ret.begin(), ret.begin() + 1);
		}
		return ret;
	}

	//重载/=
	Bignum& operator/=(const Bignum& right)
	{
		*this = *this / right;
		return *this;
	}

	//重载%
	Bignum operator%(const Bignum& right)
	{
		Bignum ret;
		ret = *this - (*this / right) * right;
		return ret;
	}

	//重载%=
	Bignum& operator%=(const Bignum& right)
	{
		*this = *this % right;
		return *this;
	}

	//重载^
	Bignum operator^(const Bignum& right)
	{
		Bignum zero;
		zero.push_back(0);
		Bignum one;
		one.push_back(1);
		Bignum two;
		two.push_back(2);
		if (right == zero)
		{
			return one;
		}
		else if (right == one)
		{
			return *this;
		}
		else if (right == two)
		{
			return square(*this);
		}
		Bignum ret = *this;
		Bignum pow;
		pow.push_back(1);
		while (pow * two < right)
		{
			ret = square(ret);
			pow *= two;
		}
		ret *= ((*this) ^ (right - pow));
		return ret;
	}

	//重载^=
	Bignum& operator^=(const Bignum& right)
	{
		*this = *this ^ right;
		return *this;
	}

	friend std::wstringstream& operator>>(std::wstringstream& in, Bignum& right)
	{
		char temp = 0;
		while (true)
		{
			temp = getchar();					//神奇的getchar
			if (temp == ' ' || temp == '\n')
			{
				break;
			}
			right.push_back(temp - '0');
		}
		return in;
	}

	//重载<<
	friend ostream& operator<<(ostream& out, const Bignum& right)
	{
		for (auto e : right._con)
			//这里又犯了低级错误
			//for(auto e : _con)
			//友元函数已不属于这个类了，只是能访问到这个类的数据而已
			//所以直接_con里面是没有数据的
		{
			out << e;
		}
		return out;
	}

	// 显示函数
	void display(ostream& out)const
	{
		for (auto e : _con)
		{
			out << e;
		}
		out << endl;
	}

	// 大整数转wstring
	wstring Bignum2wstring()
	{
		wstring ret;
		auto it = _con.begin();
		if (*it < 0)
		{
			*it *= -1;
			ret.push_back('-');
		}
		for (auto e : _con)
		{
			ret.push_back(e + '0');
		}
		//const wchar_t* arr = ret.c_str();
		return ret;
	}

	wstring Bignum_wstring()const
	{
		wstring ret;
		auto it = _con.begin();
		if (*it < 0)
		{
			ret.push_back('-');
			ret.push_back(*it * (-1) + '0');
		}
		for (auto e : _con)
		{
			if (e >= 0)
			ret.push_back(e + '0');
		}
		return ret;
	}

	// 大整数转string
	string Bignum_string()const
	{
		string ret;
		auto it = _con.begin();
		if (*it < 0)
		{
			ret.push_back('-');
		}
		for (auto e : _con)
		{
			ret.push_back(e + '0');
		}
		return ret;
	}

	//2进制转10进制
	void bin2dec()
	{
		Bignum ret;
		ret.push_back(0);
		Bignum pow;
		pow.push_back(0);
		Bignum one;
		one.push_back(1);
		Bignum two;
		two.push_back(2);
		auto it = _con.rbegin();
		while (it != _con.rend())
		{
			ret += _miniMul(*it, two ^ pow);
			pow += one;
			it++;
		}
		*this = ret;
	}

	//10进制转2进制
	void dec2bin()
	{
		Bignum ret;
		Bignum zero;
		zero.push_back(0);
		Bignum two;
		two.push_back(2);
		while (*this != zero)
		{
			Bignum temp = *this % two;
			ret.push_back(temp._con.first());
			*this /= two;
		}
		Reverse(ret.begin(), ret.end());
		*this = ret;
	}

private:
	//工具函数，实现一位数乘大整数
	Bignum _miniMul(int num, const Bignum& bignum)
	{
		Bignum ret;
		Bignum zero;
		zero.push_back(0);
		if (num == 0)
		{
			return zero;
		}
		int carry = 0;//进位
		//这里出现过忘记用反向迭代器，直接用语法糖遍历的错误
		auto it = bignum._con.rbegin();
		while (it != bignum._con.rend())
		{
			ret.push_back((*it * num + carry) % 10);
			carry = (*it * num + carry) / 10;
			++it;
		}
		if (carry)
		{
			ret.push_back(carry);
		}
		Reverse(ret.begin(), ret.end());
		return ret;
	}
	//工具函数，计算平方
	Bignum square(Bignum& right)
	{
		return right * right;
	}
	Container _con;			//适配大整数
};
