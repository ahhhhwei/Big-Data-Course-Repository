#include "sort.h"
#include<iostream>
void test_bubble(vector<int> test)
{
	cout << "冒泡排序：" << endl;
	Sort<int> sort;
	sort.bubblesort(test);
	cout << endl;
	cout << "乱序：" << endl;
	cout << "交换次数：" << sort.get_exchange_time() << endl;
	cout << "比较次数" << sort.get_compare_time() << endl;
	for (auto e : test)
	{
		cout << e << ' ';
	}

	sort.clear();
	Test_data temp1;
	temp1.order_data(100);
	sort.bubblesort(temp1._v);
	cout << endl;
	cout << "顺序：" << endl;
	cout << "交换次数：" << sort.get_exchange_time() << endl;
	cout << "比较次数：" << sort.get_compare_time() << endl;
	for (auto e : temp1._v)
	{
		cout << e << ' ';
	}

	sort.clear();
	Test_data temp2;
	temp2.reverse_data(100);
	sort.bubblesort(temp2._v);
	cout << "逆序：" << endl;
	cout << "交换次数：" << sort.get_exchange_time() << endl;
	cout << "比较次数：" << sort.get_compare_time() << endl;
	for (auto e : temp2._v)
	{
		cout << e << ' ';
	}
	cout << endl << endl;
}
void test_select(vector<int> test)
{
	Sort<int> sort;
	sort.selectsort(test);
	cout << endl << "选择排序：" << endl;
	cout << "乱序：" << endl;
	cout << "交换次数：" << sort.get_exchange_time() << endl;
	cout << "比较次数：" << sort.get_compare_time() << endl;
	for (auto e : test)
	{
		cout << e << ' ';
	}

	sort.clear();
	Test_data temp1;
	temp1.order_data(100);
	sort.selectsort(temp1._v);
	cout << endl;
	cout << "顺序：" << endl;
	cout << "交换次数：" << sort.get_exchange_time() << endl;
	cout << "比较次数：" << sort.get_compare_time() << endl;
	for (auto e : temp1._v)
	{
		cout << e << ' ';
	}

	sort.clear();
	Test_data temp2;
	temp2.reverse_data(100);
	sort.selectsort(temp2._v);
	cout << endl;
	cout << "逆序：" << endl;
	cout << "交换次数：" << sort.get_exchange_time() << endl;
	cout << "比较次数：" << sort.get_compare_time() << endl;
	for (auto e : temp2._v)
	{
		cout << e << ' ';
	}
	cout << endl << endl;
}
void test_insert(vector<int> test)
{
	Sort<int> sort;
	sort.insertsort(test);
	cout << endl << "插入排序：" << endl;
	cout << "乱序：" << endl;
	cout << "交换次数：" << sort.get_exchange_time() << endl;
	cout << "比较次数：" << sort.get_compare_time() << endl;
	for (auto e : test)
	{
		cout << e << ' ';
	}

	sort.clear();
	Test_data temp1;
	temp1.order_data(100);
	sort.insertsort(temp1._v);
	cout << endl;
	cout << "顺序：" << endl;
	cout << "交换次数：" << sort.get_exchange_time() << endl;
	cout << "比较次数：" << sort.get_compare_time() << endl;
	for (auto e : temp1._v)
	{
		cout << e << ' ';
	}

	sort.clear();
	Test_data temp2;
	temp2.reverse_data(100);
	sort.insertsort(temp2._v);
	cout << endl;
	cout << "逆序：" << endl;
	cout << "交换次数：" << sort.get_exchange_time() << endl;
	cout << "比较次数：" << sort.get_compare_time() << endl;
	for (auto e : temp2._v)
	{
		cout << e << ' ';
	}
	cout << endl << endl;
}
void test_heap(vector<int> test)
{
	Sort<int> sort;
	sort.heapsort(test);
	cout << endl << "堆排序：" << endl;
	cout << "乱序：" << endl;
	cout << "交换次数：" << sort.get_exchange_time() << endl;
	cout << "比较次数：" << sort.get_compare_time() << endl;
	for (auto e : test)
	{
		cout << e << ' ';
	}

	sort.clear();
	Test_data temp1;
	temp1.order_data(100);
	sort.heapsort(temp1._v);
	cout << endl;
	cout << "顺序：" << endl;
	cout << "交换次数：" << sort.get_exchange_time() << endl;
	cout << "比较次数：" << sort.get_compare_time() << endl;
	for (auto e : temp1._v)
	{
		cout << e << ' ';
	}

	sort.clear();
	Test_data temp2;
	temp2.reverse_data(100);
	sort.heapsort(temp2._v);
	cout << endl;
	cout << "逆序：" << endl;
	cout << "交换次数：" << sort.get_exchange_time() << endl;
	cout << "比较次数：" << sort.get_compare_time() << endl;
	for (auto e : temp2._v)
	{
		cout << e << ' ';
	}
	cout << endl << endl;
}
void test_quick(vector<int> test)
{
	Sort<int> sort;
	sort.quicksort(test);
	cout << endl << "快速排序：" << endl;
	cout << "乱序：" << endl;
	cout << "交换次数：" << sort.get_exchange_time() << endl;
	cout << "比较次数：" << sort.get_compare_time() << endl;
	for (auto e : test)
	{
		cout << e << ' ';
	}
	sort.clear();
	Test_data temp1;
	temp1.order_data(100);
	sort.quicksort(temp1._v);
	cout << endl;
	cout << "顺序：" << endl;
	cout << "交换次数：" << sort.get_exchange_time() << endl;
	cout << "比较次数：" << sort.get_compare_time() << endl;
	for (auto e : temp1._v)
	{
		cout << e << ' ';
	}

	sort.clear();
	Test_data temp2;
	temp2.reverse_data(100);
	sort.quicksort(temp2._v);
	cout << endl;
	cout << "逆序：" << endl;
	cout << "交换次数：" << sort.get_exchange_time() << endl;
	cout << "比较次数：" << sort.get_compare_time() << endl;
	for (auto e : temp2._v)
	{
		cout << e << ' ';
	}
	cout << endl << endl;
}
void test_merge(vector<int> test)
{
	Sort<int> sort;
	sort.mergesort(test);
	cout << endl << "归并排序：" << endl;
	cout << "乱序：" << endl;
	for (auto e : test)
	{
		cout << e << ' ';
	}

	sort.clear();
	Test_data temp1;
	temp1.order_data(100);
	sort.mergesort(temp1._v);
	cout << endl;
	cout << "顺序：" << endl;
	for (auto e : temp1._v)
	{
		cout << e << ' ';
	}

	sort.clear();
	Test_data temp2;
	temp2.reverse_data(100);
	sort.mergesort(temp2._v);
	cout << endl;
	cout << "逆序：" << endl;
	for (auto e : temp2._v)
	{
		cout << e << ' ';
	}
	cout << endl << endl;
}
void test_radix(vector<int> test)
{
	Sort<int> sort;
	sort.radixsort(test);
	cout << endl << "基数排序：" << endl;
	cout << "乱序：" << endl;
	for (auto e : test)
	{
		cout << e << ' ';
	}

	sort.clear();
	Test_data temp1;
	temp1.order_data(100);
	sort.radixsort(temp1._v);
	cout << endl;
	cout << "顺序：" << endl;
	for (auto e : temp1._v)
	{
		cout << e << ' ';
	}

	sort.clear();
	Test_data temp2;
	temp2.reverse_data(100);
	sort.radixsort(temp2._v);
	cout << endl;
	cout << "逆序：" << endl;
	for (auto e : temp2._v)
	{
		cout << e << ' ';
	}
}
int main(void)
{
	
	Test_data arr;
	arr.random_data(100);
	vector<int> test = arr._v;
	test_bubble(test);
	test_insert(test);
	test_heap(test);
	test_quick(test);
	test_select(test);
	test_merge(test);
	test_radix(test);
	
	return 0;
}