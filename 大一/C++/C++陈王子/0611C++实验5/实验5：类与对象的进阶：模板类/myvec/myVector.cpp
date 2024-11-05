#include <iostream>
#include <algorithm> //用于sort函数
#include <string>

using namespace std;

const int CAPACITY = 1000;

class myVector
{
public:
	// 构造系列
	myVector(unsigned n = 10, int value = 0); // 用指定值value初始化n个单元, n <= CAPACITY
	myVector(const myVector& obj);           // 拷贝构造

	// 赋值重载
	myVector& operator=(const myVector& right);

	// 下标运算
	int& operator[](unsigned index);

	// 调整容量
	void set_size(unsigned newsize); // 调整容量到newsize ,newsize<=CAPACITY

	// 获取容量
	int get_size() const;

	// 返回元素逆置存放的向量
	myVector operator-();

	// 升序排序
	void sort();

	// 从0开始显示向量元素，以逗号分隔每个单元值
	void display() const;

	// 前置增量重载，将vector内每个单元值增加1，并返回修改后的vector
	myVector operator++();

	// 后置增量重载，将vector内每个单元值增加1，并返回修改前的vector
	myVector operator++(int);
	//加法运算符重载
	myVector operator+(const myVector& vec)const;
	//减法运算符重载
	myVector operator-(const myVector& vec)const;
	// 输入输出流重载
	friend ostream& operator<<(ostream& out, const myVector& vec);
	friend istream& operator>>(istream& in, myVector& vec);
private:
	int data[CAPACITY];
	int size; // 有效单元个数
};

// 构造函数
myVector::myVector(unsigned n, int value)
{
	size = n > CAPACITY ? CAPACITY : n;
	std::fill(data, data + size, value);
}

// 拷贝构造函数
myVector::myVector(const myVector& obj)
{
	std::copy(obj.data, obj.data + obj.size, data);
	size = obj.size;
}

// 赋值操作符重载
myVector& myVector::operator=(const myVector& right)
{
	if (this == &right)
		return *this;

	std::copy(right.data, right.data + right.size, data);
	size = right.size;
	return *this;
}

// 下标运算符重载
int& myVector::operator[](unsigned index)
{
	if (index >= size || index < 0)
		throw "Index out of bounds";
	return data[index];
}

// 调整容量
void myVector::set_size(unsigned newsize)
{
	if (newsize > CAPACITY)
		newsize = CAPACITY;
	if (newsize < size)
		size = newsize;
	else
		std::fill(data + size, data + newsize, 0);
	size = newsize;
}

// 获取容量
int myVector::get_size() const
{
	return size;
}

// 返回元素逆置存放的向量
myVector myVector::operator-()
{
	myVector ret(*this);
	for (int i = 0; i < size / 2; ++i)
	{
		swap(ret.data[i], ret.data[size - i - 1]);
	}
	return ret;
}

// 升序排序
void myVector::sort()
{
	std::sort(data, data + size);
}

// 从0开始显示向量元素，以逗号分隔每个单元值
void myVector::display() const
{
	if (size == 0)
	{
		cout << "[]" << endl;
		return;
	}
	cout << "[" << data[0];
	for (int i = 1; i < size; ++i)
	{
		cout << "," << data[i];
	}
	cout << "]" << endl;
}

// 前置增量重载
myVector myVector::operator++()
{
	for (int i = 0; i < size; ++i)
	{
		++data[i];
	}
	return *this;
}

// 后置增量重载
myVector myVector::operator++(int)
{
	myVector ret(*this);
	++(*this);
	return ret;
}



//加号运算符重载
myVector myVector::operator+(const myVector& vec) const {
	// 根据两个向量中元素数量较小的那个来创建新的向量
	int newSize = (size > vec.size) ? vec.size : size;
	myVector result(newSize);

	// 对相应位置上的元素进行相加
	for (int i = 0; i < newSize; ++i) {
		result.data[i] = data[i] + vec.data[i];
	}

	return result;
}

// 减号运算符重载
myVector myVector::operator-(const myVector& vec) const {
	// 根据两个向量中元素数量较小的那个来创建新的向量
	int newSize = (size > vec.size) ? vec.size : size;
	myVector result(newSize);

	// 对相应位置上的元素进行相减
	for (int i = 0; i < newSize; ++i) {
		result.data[i] = data[i] - vec.data[i];
	}

	return result;
}



// 输出流重载
ostream& operator<<(ostream& out, const myVector& vec)
{
	if (vec.size == 0)
		return out << "[]";
	out << "[" << vec.data[0];
	for (int i = 1; i < vec.size; ++i)
		out << ", " << vec.data[i];
	out << "]";
	return out;
}
// 输入流重载
istream& operator>>(istream& in, myVector& vec)
{
	string str;
	int val = 0; // 实际读取到的整数值
	int i = 0;   // 当前向量元素的索引
	// 从输入流中读取一行字符串
	getline(in, str);
	// 解析向量字符串
	for (auto it = str.begin(); it != str.end(); ++it)
	{
		// 如果可以读取到一个整数值
		if (isdigit(*it))
		{
			val = val * 10 + (*it - '0'); // 多位数情况下，对读取到的字符进行拼凑
		}
		// 如果遇到分隔符或者字符串结束符，则将当前读取到的整数值添加到向量中
		if (!isdigit(*it) || it == str.end() - 1)
		{
			vec.data[i++] = val;
			val = 0; // 重置 val 为 0
			if (i >= CAPACITY)
			{
				// 如果向量已经满了，设置向量大小并返回输入流
				vec.size = i;
				return in;
			}
		}
	}
	// 设置向量大小并返回输入流
	vec.size = i;
	return in;
}