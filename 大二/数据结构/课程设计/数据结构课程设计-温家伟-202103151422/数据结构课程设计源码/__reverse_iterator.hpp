#pragma once
template<class iterator, class Ref, class Ptr>
struct __reverse_iterator
{
	typedef __reverse_iterator<iterator, Ref, Ptr> riterator;
	iterator _cur;
	// �������������ʵ�ַ���������Ĺ��캯��
	__reverse_iterator(iterator it)
		: _cur(it)
	{}

	// ��������������Ĳ���ʵ�ַ��������
	// �����������begin
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
		// ��Ϊ�����������begin�Ƿ����end�������end�Ƿ����begin��stl�е�����Ǳ��ֶԳƵ�
		// �������end��_finish����ָ�����һ��Ԫ�ص���һ��λ��
		// ���Է��������ȡԪ��ʱҪ�ȼ����ٽ�����
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