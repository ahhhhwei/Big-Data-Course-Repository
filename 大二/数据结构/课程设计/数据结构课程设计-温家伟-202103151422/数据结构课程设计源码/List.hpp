#pragma once
#include "__reverse_iterator.hpp"
template<class T>
struct list_node
{
	T _data;

	list_node<T>* _next;
	list_node<T>* _prev;
	// 节点的构造函数
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
	typedef T value_type;
	typedef Ptr pointer;
	typedef Ref reference;
	Node* _node;
	// 迭代器的构造函数
	__list_iterator(Node* node)
		:_node(node)
	{

	}
	// 重载!=
	bool operator!=(const iterator& it) const
	{
		return _node != it._node;
	}
	// 重载==
	bool operator==(const iterator& it) const
	{
		return _node == it._node;
	}
	// 重载解引用操作符
	Ref operator*()
	{
		return _node->_data;
	}
	// 重载->操作符
	Ptr operator->()
	{
		return &(operator*());
	}
	// 重载+操作符
	iterator operator+(int pos)
	{
		Node* tmp = this->_node;
		for (int i = 0; i < pos; ++i)
		{
			tmp = tmp->_next;
		}
		iterator ret(tmp);
		return ret;
	}
	// 重载前置++操作符
	iterator& operator++()
	{
		_node = _node->_next;
		return *this;
	}
	// 重载后置++操作符
	iterator operator++(int)
	{
		iterator tmp(*this);
		_node = _node->_next;
		return tmp;
	}
	// 重载前置--操作符
	iterator& operator--()
	{
		_node = _node->_prev;
		return *this;
	}
	// 重载后置--操作符
	iterator operator--(int)
	{
		iterator tmp(*this);
		_node = _node->_prev;
		return tmp;
	}
};
template<class T>
class List
{
	typedef list_node<T> Node;
public:
	typedef __list_iterator<T, T&, T*> iterator;
	typedef __list_iterator<T, const T&, const T*> const_iterator;
	typedef __reverse_iterator<iterator, T&, T*> reverse_iterator;
	typedef __reverse_iterator<const_iterator, const T&, const T*> const_reverse_iterator;
	// const迭代器的头
	const_iterator begin() const
	{
		return const_iterator(_head->_next);
	}
	// const迭代器的尾
	const_iterator end() const
	{
		return const_iterator(_head);
	}
	// 迭代器的头
	iterator begin()
	{
		return iterator(_head->_next);
	}
	// 迭代器的尾
	iterator end()
	{
		return iterator(_head);
	}
	// 反向迭代器的头
	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}
	// const反向迭代器的头
	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(end());
	}
	// 反向迭代器的尾
	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}
	// const反向迭代器的尾
	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(begin());
	}
	// 容器的第一个元素
	T& first()
	{
		return *begin();
	}
	// 链表的构造函数
	List()
	{
		_head = new Node;
		_head->_next = _head;
		_head->_prev = _head;
	}
	// 链表的拷贝构造函数
	List(const List<T>& lt)
	{
		_head = new Node();
		_head->_next = _head;
		_head->_prev = _head;

		for (auto e : lt)
		{
			push_back(e);
		}
	}
	// 链表的赋值运算符重载函数
	List<T>& operator=(List<T> lt)
	{
		swap(lt);
		return *this;
	}
	// 析构函数
	~List()
	{
		clear();
		delete _head;
		_head = nullptr;
	}
	// 清理函数
	void clear()
	{
		iterator it = begin();
		while (it != end())
		{
			it = erase(it);
		}
	}
	// 容器的大小
	size_t size() const
	{
		size_t sz = 0;
		auto it = begin();
		while (it != end())
		{
			sz++;
			it++;
		}
		return sz;
	}
	// 尾插
	void push_back(const T& x)
	{
		insert(end(), x);
	}
	// 头插
	void push_front(const T& x)
	{
		insert(begin(), x);
	}
	// 任意位置的插入函数
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
	// 尾删
	void pop_back()
	{
		erase(--end());
	}
	// 头删
	void pop_front()
	{
		erase(begin());
	}
	// 任意位置的删除函数
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
	// 交换函数
	void swap(List<T>& lt)
	{
		std::swap(_head, lt._head);
	}
private:
	Node* _head;
};