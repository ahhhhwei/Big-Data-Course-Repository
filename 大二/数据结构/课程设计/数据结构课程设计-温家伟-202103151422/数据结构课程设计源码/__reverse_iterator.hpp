#pragma once
template<class iterator, class Ref, class Ptr>
struct __reverse_iterator
{
	typedef __reverse_iterator<iterator, Ref, Ptr> riterator;
	iterator _cur;
	// 利用正向迭代器实现反向迭代器的构造函数
	__reverse_iterator(iterator it)
		: _cur(it)
	{}

	// 复用正向迭代器的操作实现反向迭代器
	// 正向迭代器的begin
	riterator operator++()
	{
		_cur--;
		return *this;
	}

	riterator operator++(int)
	{
		riterator tmp(*this);
		_cur--;
		return tmp;
	}

	riterator operator--()
	{
		_cur++;
		return *this;
	}

	riterator operator--(int)
	{
		riterator tmp(*this);
		_cur++;
		return tmp;
	}

	Ref operator*()
	{
		// 因为正向迭代器的begin是反向的end，正向的end是反向的begin，stl中的设计是保持对称的
		// 而正向的end是_finish，是指向最后一个元素的下一个位置
		// 所以方向迭代器取元素时要先减减再解引用
		iterator tmp = _cur;
		tmp--;
		return *tmp;
	}

	Ptr operator->()
	{
		return &(operator*());
	}

	bool operator!=(const riterator& it)
	{
		return _cur != it._cur;
	}

	bool operator==(const riterator& it)
	{
		return _cur == it._cur;
	}
};