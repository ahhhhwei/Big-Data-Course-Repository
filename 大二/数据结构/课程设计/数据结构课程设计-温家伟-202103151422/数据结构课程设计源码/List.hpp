#pragma once
#include "__reverse_iterator.hpp"
template<class T>
struct list_node
{
	T _data;

	list_node<T>* _next;
	list_node<T>* _prev;
	// �ڵ�Ĺ��캯��
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
	// �������Ĺ��캯��
	__list_iterator(Node* node)
		:_node(node)
	{

	}
	// ����!=
	bool operator!=(const iterator& it) const
	{
		return _node != it._node;
	}
	// ����==
	bool operator==(const iterator& it) const
	{
		return _node == it._node;
	}
	// ���ؽ����ò�����
	Ref operator*()
	{
		return _node->_data;
	}
	// ����->������
	Ptr operator->()
	{
		return &(operator*());
	}
	// ����+������
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
	// ����ǰ��++������
	iterator& operator++()
	{
		_node = _node->_next;
		return *this;
	}
	// ���غ���++������
	iterator operator++(int)
	{
		iterator tmp(*this);
		_node = _node->_next;
		return tmp;
	}
	// ����ǰ��--������
	iterator& operator--()
	{
		_node = _node->_prev;
		return *this;
	}
	// ���غ���--������
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
	// const��������ͷ
	const_iterator begin() const
	{
		return const_iterator(_head->_next);
	}
	// const��������β
	const_iterator end() const
	{
		return const_iterator(_head);
	}
	// ��������ͷ
	iterator begin()
	{
		return iterator(_head->_next);
	}
	// ��������β
	iterator end()
	{
		return iterator(_head);
	}
	// �����������ͷ
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
	// �����ĵ�һ��Ԫ��
	T& first()
	{
		return *begin();
	}
	// ����Ĺ��캯��
	List()
	{
		_head = new Node;
		_head->_next = _head;
		_head->_prev = _head;
	}
	// ����Ŀ������캯��
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
	// ����ĸ�ֵ��������غ���
	List<T>& operator=(List<T> lt)
	{
		swap(lt);
		return *this;
	}
	// ��������
	~List()
	{
		clear();
		delete _head;
		_head = nullptr;
	}
	// ������
	void clear()
	{
		iterator it = begin();
		while (it != end())
		{
			it = erase(it);
		}
	}
	// �����Ĵ�С
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
	// β��
	void push_back(const T& x)
	{
		insert(end(), x);
	}
	// ͷ��
	void push_front(const T& x)
	{
		insert(begin(), x);
	}
	// ����λ�õĲ��뺯��
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
	// βɾ
	void pop_back()
	{
		erase(--end());
	}
	// ͷɾ
	void pop_front()
	{
		erase(begin());
	}
	// ����λ�õ�ɾ������
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
	// ��������
	void swap(List<T>& lt)
	{
		std::swap(_head, lt._head);
	}
private:
	Node* _head;
};