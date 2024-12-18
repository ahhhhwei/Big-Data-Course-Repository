#pragma once
#include<iostream>
#include<cassert>
using namespace std;
template<class T>
class Vector
{
public:
	//无参构造
	Vector()
		: _start(nullptr)
		, _finish(nullptr)
		, _endofstorage(nullptr)
	{

	}

	//带参构造
	Vector(int n, const T& value = T())
		: _start(nullptr)
		, _finish(nullptr)
		, _endofstorage(nullptr)
	{
		reserve(n);
		while (n--)
		{
			push_back(value);
		}
	}

	//拷贝构造
	Vector(const Vector<T>& v)
		: _start(nullptr)
		, _finish(nullptr)
		, _endofstorage(nullptr)
	{
		reserve(v.capacity());
		T* it = _start;
		const T* vit = _start;
		while (vit != _finish)
		{
			*it++ = *vit++;
		}
	}


	size_t size()const
	{
		return _finish - _start;
	}
	size_t capacity()const
	{
		return _endofstorage - _start;
	}
	bool empty()
	{
		return _start == _finish;
	}
	void reserve(size_t n)
	{
		size_t sz = size();
		if (n > capacity())
		{
			T* temp = new T[n];//开新空间
			//把原有的数据拷入
			if (_start)
			{
				memcpy(temp, _start, sizeof(T) * size());
				delete[] _start;
			}
			_start = temp;
		}
		_finish = _start + sz;
		_endofstorage = _start + n;
	}
	void push_back(const T& x)
	{
		//满了的话就先开空间
		if (_endofstorage == _finish)
		{
			size_t newCapacity = capacity() == 0 ? 4 : 2 * capacity();
			reserve(newCapacity);
		}

		*_finish = x;
		++_finish;
	}
	void pop_back()
	{
		if (_finish > _start)
		{
			--_finish;
		}
	}
	T& operator[](size_t pos)
	{
		assert(pos < size());
		return _start[pos];
	}
	void swap(Vector<T> v)
	{
		std::swap(_start, v._start);
		std::swap(_finish, v._finish);
		std::swap(_endofstorage, v._endofstorage);
	}
	Vector<T>& operator=(Vector<T>& v)
	{
		swap(v);
		return *this;
	}
	~Vector()
	{
		delete[] _start;
		_start = _finish = _endofstorage = nullptr;
	}
	T& front()const
	{
		return _start[0];
	}
	T& back()const
	{
		return _start[size() - 1];
	}
	T& at(size_t pos)const
	{
		assert(pos < size());
		return _start[pos];
	}
	bool operator==(const Vector<T>& r)const
	{
		if (r.size() != size())
		{
			return false;
		}
		for (size_t i = 0; i < size(); ++i)
		{
			if (this->at(i) != r.at(i))
			{
				return false;
			}
		}
		return true;
	}
	bool operator<(const Vector<T>& r)const
	{
		size_t length = size() < r.size() ? size() : r.size();
		for (size_t i = 0; i < length; ++i)
		{
			if (this->at(i) != r.at(i))
			{
				return this->at(i) < r.at(i);
			}
		}
		return size() < r.size();
	}
private:
	T* _start;
	T* _finish;
	T* _endofstorage;
};