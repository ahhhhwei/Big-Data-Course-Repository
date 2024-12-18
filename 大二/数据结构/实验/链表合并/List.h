#pragma once
#include<iostream>
#include<cassert>
using namespace std;
template<class T>
class List
{
private:
	class Node
	{
	public:
		Node* _next;
		T _data;
		Node(const T& x = T())
			:_next(nullptr)
			, _data(x)
		{

		}

	};
public:
	List()
	{
		createHead();
		_size = 0;
	}
	List(int n, const T& value = T())
	{
		createHead();
		for (size_t i = 0; i < n; ++i)
		{
			push_back(value);
		}
		_size = n;
	}
	List(Node* first)
	{
		createHead();
		while (first)
		{
			push_back(first->_data);
			first = first->_next;
		}
	}
	List(const List<T>& lt)
	{
		//拷贝构造函数的现代写法，参考自《剑指offer》
		createHead();
		// 用lt中的元素构造临时的temp,然后与当前对象交换
		List<T> temp(lt._head->_next);
		this->swap(temp);
	}
	List<T>& operator=(List<T>& lt)
	{
		//赋值运算符重载函数的现代写法，参考自《剑指offer》
		this->swap(lt);
		return *this;
	}
	~List()
	{
		List<T>::release();
	}
	void release()
	{
		Node* prev = _head, * ptr;
		while (prev)
		{
			ptr = prev->_next;
			delete prev;
			prev = ptr;
		}
	}
	bool empty()
	{
		return _size == 0;
	}
	void push_back(const T& val)
	{
		insert(val, _size);
	}
	void pop_back()
	{
		erase(_size);
	}
	void insert(const T& data, int index)
	{
		assert(!(index < 0 || index > _size));
		Node* tmp = new Node(data);
		if (_size == 0)
		{
			_head->_next = tmp;
			tmp->_next = nullptr;
		}
		else
		{
			Node* prev = _head;
			Node* cur = prev->_next;
			for (int i = 0; i < index; i++)
			{
				prev = prev->_next;
				cur = prev->_next;
			}
			tmp->_next = cur;
			prev->_next = tmp;
		}
		++_size;
	}
	void erase(int index)
	{
		Node* prev = _head;
		Node* cur = prev->_next;
		for (int i = 1; i < index; i++)
		{
			prev = prev->_next;
			cur = prev->_next;
		}
		prev->_next = cur->_next;
		delete cur;
		--_size;
	}
	void reverse()
	{
		size_t N = nodeCount();
		for (size_t i = 0; i < N; ++i)
		{
			Node* cur = _head->_next;
			while (cur->_next)
			{
				cur = cur->_next;
			}
			T val = cur->_data;
			pop_back();
			insert(val, i);
		}
	}
	Node* search(const T& val)
	{
		Node* cur = _head;
		while (cur)
		{
			if (cur->_data == val)
			{
				return cur;
			}
			else
			{
				cur = cur->_next;
			}
		}
		return nullptr;
	}
	void display(ostream& out)const
	{
		Node* cur = _head->_next;
		while (cur)
		{
			out << cur->_data << ' ';
			cur = cur->_next;
		}
		cout << endl;
	}
	int nodeCount()const
	{
		return _size;
	}
	bool ascendingOrder()
	{
		assert(_size > 0);
		if (_size == 1)
		{
			return true;
		}
		Node* cur = _head->_next;
		while (cur->_next)
		{
			if (cur->_data > cur->_next->_data)
			{
				return false;
			}
			cur = cur->_next;
		}
		return true;
	}
	void MergeList(List<T>& ltA, List<T>& ltB)
	{
		release();
		createHead();
		this->ListMerge(ltA);
		this->ListMerge(ltB);
	}
	void ListMerge(List<T>& lt)
	{
		Node* cur = _head;
		while (cur->_next)
		{
			cur = cur->_next;
		}
		Node* curlt = lt._head->_next;
		while (curlt)
		{
			Node* temp = new Node(curlt->_data);
			cur->_next = temp;
			cur = cur->_next;
			curlt = curlt->_next;
		}
	}
	T get(Node* temp)
	{
		return temp->_data;
	}
	friend ostream& operator<<(ostream& out, const List<T>& lt)
	{
		lt.display(out);
		return out;
	}
	friend istream& operator>>(istream& in, List<T>& lt)
	{
		T val;
		in >> val;
		lt.push_back(val);
		return in;
	}
private:
	void createHead()
	{
		_head = new Node;
		_head->_next = nullptr;
	}
	void swap(List<T>& lt)
	{
		std::swap(_head, lt._head);
		std::swap(_size, lt._size);
	}
	Node* _head;
	int _size;
};