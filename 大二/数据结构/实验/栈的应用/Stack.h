#pragma once
#include<iostream>
using namespace std;
template<class T>
class Stack
{
private:
	class Node
	{
	public:
		T _data;
		Node* _next;
		Node(T value, Node* link = nullptr)
			:_data(value)
			, _next(link)
		{

		}
	};
	typedef Node* Nodepointer;
	Nodepointer _myTop;
	void swap(Stack<T>& r)
	{
		std::swap(_myTop, r._myTop);
	}
public:
	Stack()
		:_myTop(0)
	{

	}
	Stack(const Stack<T>& r)
	{
		_myTop = 0;
		if (!r.empty())
		{
			_myTop = new Node(r);
			Nodepointer lastPtr = _myTop, origPtr = r._myTop->_next;
			while (origPtr)
			{
				lastPtr->_next = new Node(origPtr->_data);
				lastPtr = lastPtr->_next;
				origPtr = origPtr->_next;
			}
		}
	}
	~Stack()
	{
		Nodepointer cur = _myTop, _next;
		while (cur)
		{
			_next = cur->_next;
			delete cur;
			cur = _next;
		}
	}
	Stack<T>& operator=(Stack<T>& r)
	{
		this->swap(r);
		return *this;
	}
	void display(ostream& out)const
	{
		Nodepointer ptr;
		for (ptr = _myTop; ptr != nullptr; ptr = ptr->_next)
		{
			out << ptr->_data << ' ';
		}
	}
	void push(const T& value)
	{
		_myTop = new Node(value, _myTop);
	}
	T top()const
	{
		if (!empty())
		{
			return _myTop->_data;
		}
		else
		{
			cerr << "***Stack is empty***" << endl;
			T* temp = new T();
			T garbage = *temp;
			delete temp;
			return garbage;
		}
	}
	void pop()
	{
		if (!empty())
		{
			Nodepointer ptr = _myTop;
			_myTop = _myTop->_next;
			delete ptr;
		}
		else
		{
			cerr << "***Stack is empty***" << endl;
		}
	}
	bool empty()const
	{
		return _myTop == 0;
	}
};