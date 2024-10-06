#pragma once

#include<iostream>
#include<cassert>
#include "List.hpp"
#include "__reverse_iterator.hpp"

using namespace std;
template<class T>
class Vector
{
public:
	typedef T* iterator;//��ͨ������
	typedef const T* const_iterator;//const������
	typedef __reverse_iterator<iterator, T&, T*> reverse_iterator;//���������
	typedef __reverse_iterator<const_iterator, const T&, const T*> const_reverse_iterator;//const���������

	// �޲ι���
	Vector()
		:_start(nullptr)
		, _finish(nullptr)
		, _endofstorage(nullptr)
	{

	}
	// ��������
	Vector(const Vector<T>& v)
		:_start(nullptr)
		, _finish(nullptr)
		, _endofstorage(nullptr)
	{
		_start = new T[v.capacity()]; //����һ�������v��С��ͬ�Ŀռ�
		for (size_t i = 0; i < v.size(); i++) //������v���е�����һ������������
		{
			_start[i] = v[i];
		}
		_finish = _start + v.size(); // ������Ч���ݵ�β
		_endofstorage = _start + v.capacity(); // ����������β
	}
	// ��ֵ��������غ���
	Vector<T>& operator=(const Vector<T>& v)
	{
		if (this != &v)
		{
			delete[]_start; // �ͷ�ԭ�ռ�
			_start = new T[v.capacity()]; // �����¿ռ�
			for (size_t i = 0; i < v.size(); i++) // ��������
			{
				_start[i] = v[i];
			}
			_finish = _start + v.size(); // ����_finish
			_endofstorage = _start + v.capacity(); // ����_capacity
		}
		return *this;
	}
	// ��������
	~Vector()
	{
		delete[] _start;
	}
	// ��������ͷ
	iterator begin() 
	{ 
		return _start; 
	}
	// const��������ͷ
	const_iterator begin() const 
	{ 
		return _start; 
	}
	// ��������β
	iterator end() 
	{ 
		return _finish; 
	}
	// const��������β
	const_iterator end() const 
	{ 
		return _finish;
	} 
	// �����������ͷn
	reverse_iterator rbegin() 
	{ 
		return reverse_iterator(end()); 
	}
	// const�����������ͷ
	const_reverse_iterator rbegin() const 
	{
		return const_reverse_iterator(end());
	}
	// �����������β
	reverse_iterator rend() 
	{ 
		return reverse_iterator(begin()); 
	}
	// const�����������β
	const_reverse_iterator rend() const 
	{
		return const_reverse_iterator(begin());
	}
	// ������С
	size_t size()const
	{
		return _finish - _start;
	}
	// ��������
	size_t capacity()const
	{
		return _endofstorage - _start;
	}
	// ��ǰ���ռ�
	void reserve(size_t n)
	{
		size_t sz = size();
		if (n > capacity())
		{
			T* temp = new T[n];//���¿ռ�
			//��ԭ�е����ݿ���
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
	// ���ռ䲢��ʼ��
	void resize(size_t n, const T& val = T())
	{
		//���ռ�
		if (n > capacity())
		{
			reserve(n);
		}
		//��ʼ��
		if (n > size())
		{
			while (_finish < _start + n)
			{
				*_finish = val;
				++_finish;
			}
		}
		else
		{
			_finish = _start + n;
		}
	}
	// ɾ��
	iterator erase(iterator pos)
	{
		assert(pos >= _start && pos < _finish);
		iterator cur = pos + 1;
		while (cur < _finish)
		{
			*(cur - 1) = *cur;
			cur++;
		}
		_finish--;
		return pos;//����posλ��
	}
	// β��
	void push_back(const T& x)
	{
		//���˵Ļ����ȿ��ռ�
		if (_endofstorage == _finish)
		{
			size_t newCapacity = capacity() == 0 ? 4 : 2 * capacity();
			reserve(newCapacity);
		}

		*_finish = x;
		++_finish;
	}
	// βɾ
	void pop_back()
	{
		if (_finish > _start)
		{
			--_finish;
		}
	}
	// �����ĵ�һ��Ԫ��
	T& first()
	{
		return _start[0];
	}
	// �����±���ʲ�����
	T& operator[](size_t pos)
	{
		assert(pos < size());
		return _start[pos];
	}
	// �����±���ʲ�������const�汾
	const T& operator[](size_t pos) const
	{
		assert(pos < size());
		return _start[pos];
	}
	// ����
	void insert(iterator pos, const T& x)
	{
		//���Խ��
		assert(pos >= _start && pos <= _finish);
		//���˾�����
		if (_finish == _endofstorage)
		{
			//���ݺ�pos��ʧЧ�ˣ���Ҫ����
			size_t n = pos - _start;
			size_t newCapacity = capacity() == 0 ? 4 : 2 * capacity();
			reserve(newCapacity);
			pos = _start + n;
		}
		//Ų������
		iterator end = _finish - 1;
		while (end >= pos)
		{
			*(end + 1) = *end;
			--end;
		}
		*pos = x;
		++_finish;
	}
private:
	iterator _start;
	iterator _finish;
	iterator _endofstorage;
};
