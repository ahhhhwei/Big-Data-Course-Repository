#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include <assert.h>
using namespace std;
namespace wenjiawei
{
	template<class T>
	struct list_node
	{
		T _data;
		list_node<T>* _next;
		list_node<T>* _prev;
		list_node(const T& x = T())
			:_data(x)
			, _next(nullptr)
			, _prev(nullptr)
		{
			
		}
	};
	template<class T, class Ref, class Ptr>
	struct __list_iterator
	{
		typedef list_node<T> Node;
		typedef __list_iterator<T, Ref, Ptr> iterator;
		typedef bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef Ptr pointer;
		typedef Ref reference;
		typedef ptrdiff_t difference_type;
		Node* _node;
		__list_iterator(Node* node)
			:_node(node)
		{
			
		}
		bool operator!=(const iterator& it) const
		{
			return _node != it._node;
		}
		bool operator==(const iterator& it) const
		{
			return _node == it._node;
		}
		Ref operator*()
		{
			return _node->_data;
		}
		Ptr operator->()
		{
			return &(operator*());
		}
		iterator& operator++()
		{
			_node = _node->_next;
			return *this;
		}
		iterator operator++(int)
		{
			iterator tmp(*this);
			_node = _node->_next;
			return tmp;
		}
		iterator& operator--()
		{
			_node = _node->_prev;
			return *this;
		}
		iterator operator--(int)
		{
			iterator tmp(*this);
			_node = _node->_prev;
			return tmp;
		}
	};
	template<class T>
	class list
	{
		typedef list_node<T> Node;
	public:
		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;
		const_iterator begin() const
		{
			return const_iterator(_head->_next);
		}
		const_iterator end() const
		{
			return const_iterator(_head);
		}
		iterator begin()
		{
			return iterator(_head->_next);
		}
		iterator end()
		{
			return iterator(_head);
		}
		list()
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
		}
		size_t size() const
		{
			size_t sz = 0;
			iterator it = begin(); 
			while (it != end()) 
			{
				sz++;
				it++;
			}
			return sz;
		}

		void push_back(const T& x)
		{
			insert(end(), x);
		}
		void push_front(const T& x)
		{
			insert(begin(), x);
		}
		iterator insert(iterator pos, const T& x)
		{
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* newnode = new Node(x);
			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = cur;
			cur->_prev = newnode;
			return iterator(newnode);
		}
		void pop_back()
		{
			erase(--end());
		}
		void pop_front()
		{
			erase(begin());
		}
		iterator erase(iterator pos)
		{
			assert(pos != end());
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* next = cur->_next;
			prev->_next = next;
			next->_prev = prev;
			delete cur;
			return iterator(next);
		}
	private:
		Node* _head;
	};
}