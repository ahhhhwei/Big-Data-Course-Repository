#pragma once
#include<cmath>
#include<algorithm>
#include"list.hpp"
#include<list>
#include<vector>
#include<string>
#include<iostream>
using namespace std;

template<typename T>
struct Data
{
	int _power;
	T _val;
	Data(T val = 0, int power = 0)
		:_val(val)
		, _power(power)
	{

	}
	friend ostream& operator<<(ostream& out, const Data<T>& r)
	{
		out << r._val;
		if (r._power)
		{
			out << "x^" << r._power;
		}
		return out;
	}
	//因为Data是自定义类型，重载 < 和 > 以支持仿函数
	bool operator<(const Data<T>& r)const
	{
		return this->_power > r._power;
	}
	bool operator>(const Data<T>& r)const
	{
		return this->_power < r._power;
	}
};
////仿函数
//template<typename T>
//class greater
//{
//public:
//	bool operator()(Data<T> d1, Data<T> d2)
//	{
//		return d1._power > d2._power;
//	}
//};

//template<typename T>
//class less
//{
//public:
//	bool operator()(Data<T> d1, Data<T> d2)
//	{
//		return d1._power < d2._power;
//	}
//};
template<typename T>
class Polynomial
{
public:
	void delete_0()
	{
		auto it = _lt.begin();
		while (it != _lt.end())
		{
			if (it->_val == 0)
			{
				it = _lt.erase(it);
			}
			else
			{
				it++;
			}
		}
	}
	void merge_terms()
	{
		auto it = _lt.begin();
		auto it_fast = (++_lt.begin());
		while (it_fast != _lt. end())
		{
			if (it->_power == it_fast->_power)
			{
				it_fast->_val += it->_val;
				it->_val = 0;
			}
			it++;
			it_fast++;
		}
	}
	Polynomial operator+(Polynomial& val)
	{
		Polynomial ret;
		auto itleft = _lt.begin();
		auto itright = val._lt.begin();
		/*while (itleft != _lt.end() && itright != val._lt.end())
		{
			if (itleft->_power == itright->_power)
			{
				ret.push_back(Data<T>(itright->_val + itleft->_val, itright->_power));
				++itleft;
				++itright;
			}
			else if (itleft->_power < itright->_power)
			{
				ret.push_back(Data<T>(itleft->_val , itleft->_power));
				++itleft;
			}
			else
			{
				ret.push_back(Data<T>(itright->_val, itright->_power));
				++itright;
			}
		}
		while (itright == val._lt.end() && itleft != _lt.end())
		{
			ret.push_back(Data<T>(itleft->_val, itleft->_power));
			++itleft;
		}
		while (itleft == _lt.end() && itright != val._lt.end())
		{
			ret.push_back(Data<T>(itright->_val, itleft->_power));
			++itright;
		}*/
		while (itleft != _lt.end())
		{
			ret.push_back(Data<T>(itleft->_val, itleft->_power));
			++itleft;
		}
		while (itright != val._lt.end())
		{
			ret.push_back(Data<T>(itright->_val, itright->_power));
			++itright;
		}
		ret._lt.sort();
		ret.merge_terms();
		ret.delete_0();
		return ret;
	}
	//Polynomial& operator+=(Polynomial& val)
	//{
	//	*this = *this + val;
	//	return *this;
	//}
	Polynomial operator-(Polynomial& val)
	{
		//val中每项*-1，再调用operator+
		Polynomial temp;
		temp.push_back(Data<T>(-1, 0));
		Polynomial ret;
		val = val * temp;
		ret = val + *this;
		if (ret._lt.size() == 0)
		{
			ret.push_back(Data<T>(0, 0));
			return ret;
		}
		ret._lt.sort();
		ret.merge_terms();
		ret.delete_0();
		return ret;
	}
	Polynomial operator*(const Polynomial& val)
	{
		Polynomial ret;
		for (auto e : _lt)
		{
			for (auto ee : val._lt)
			{
				ret.push_back(Data<T>(e._val * ee._val, e._power + ee._power));
			}
		}
		ret._lt.sort();
		ret.merge_terms();
		ret.delete_0();
		return ret;
	}
	void push_back(const Data<T>& val)
	{
		_lt.push_back(val);
	}
	void read(istream& in)
	{
		bool exit = 0;
		int i = 0;
		while (1)
		{
			i++;
			cout << "请输入第" << i << "项的系数：" << endl;
			T temp_val;
			in >> temp_val;
			cout << "请输入第" << i << "项的次数：" << endl;
			int temp_power;
			in >> temp_power;
			cout << "是否停止输入?(1/0)" << endl;
			in >> exit;
			Data<T> temp(temp_val, temp_power);
			_lt.push_back(temp);
			if (exit)
			{
				break;
			}
		}
	}
	void display(ostream& out)
	{
		_lt.sort();
		merge_terms();
		delete_0();
		if (_lt.size() == 0)
		{
			out << "0" << endl;
		}
		int count = 0;
		for (const auto& e : _lt)
		{
			out << e;
			if (count++ != _lt.size()-1)
			{
				out << " + ";
			}
		}
		out << endl;
	}
	T cal(const T& val)
	{
		T ret = 0;
		for (auto e : _lt)
		{
			ret += (e._val * pow(val, e._power));
		}
		return ret;
	}
private:
	list<Data<T>> _lt;
};