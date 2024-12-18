#pragma once
#include <time.h>
using namespace std;
#include<vector>
template<class T>
class Sort
{
public:
	Sort()
	{
		exchange_time = 0;
		compare_time = 0;
	}
	void selectsort(vector<T>& data)
	{
		for (size_t next = 1; next < data.size(); next++)
		{
			int j = 0;
			T temp = data[next];
			for (j = next - 1; j >= 0 && temp < data[j]; j--)
			{
				compare_time++;
				data[j + 1] = data[j];
			}
			exchange_time++;
			data[j + 1] = temp;
		}
	}
	void bubblesort(vector<T>& data)
	{
		int exchange = 1;
		for (int top = data.size() - 1; top > 0 && exchange; top--)
		{
			exchange = 0;
			for (int i = 0; i < top; i++)
			{
				if (data[i + 1] < data[i])
				{
					std::swap(data[i + 1], data[i]);
					exchange_time++;
					exchange = 1;
				}
				compare_time++;
			}
		}
	}
	void insertsort(vector<int>& data)
	{
		{
			for (size_t i = 0; i < data.size() - 1; ++i)
			{
				int end = i;
				T tmp = data[end + 1];
				while (end >= 0)
				{
					if (tmp < data[end])
					{
						compare_time++;
						data[end + 1] = data[end];
						exchange_time++;
						--end;
					}
					else
					{
						compare_time++;
						break;
					}
				}
				data[end + 1] = tmp;
				exchange_time++;
			}
		}
	}
	void quicksort(vector<T>& data)
	{
		qsort(0, data.size() - 1, data);
	}
	void heapsort(vector<int>& data)
	{
		for (int i = (data.size() - 2) / 2; i >= 0; --i)
		{
			AdjustDown(data, data.size(), i);
		}
		size_t end = data.size() - 1;
		while (end > 0)
		{
			std::swap(data[0], data[end]);
			exchange_time++;
			AdjustDown(data, end, 0);
			--end;
		}
	}
	void mergesort(vector<int>& data)
	{
		bool order = 0;
		while (!order)
		{
			vector<vector<T>> v1;
			vector<vector<T>> v2;
			size_t pos = 0;
			while (pos != data.size())
			{
				v1.push_back(split(pos, data));
				if(pos != data.size())
					v2.push_back(split(pos, data));
			}
			vector<T> ret;
			int i = 0;
			while (i != std::min(v1.size(), v2.size()))
			{
				vector<T> temp = merge(v1[i], v2[i]);
				for (auto e : temp)
				{
					ret.push_back(e);
				}
				++i;
			}
			if (i != v1.size())
			{
				for (auto e : v1[i])
				{
					ret.push_back(e);
				}
				
			}
			if (i != v2.size())
			{
				for (auto e : v2[i])
				{
					ret.push_back(e);
				}
			}
			data = ret;
			size_t j = 0;
			for (j = 0; j < data.size() - 1; ++j)
			{
				if (data[j] > data[j + 1])
					break;
			}
			if (j + 1 == data.size())
				order = 1;
		}
	}
	void radixsort(vector<int>& data)
	{
		vector<int> bucket(data.size());
		vector<int> count(10);
		for (int j = 1; j <= MaxBit(data); ++j) 
		{
			for (int i = 0; i < 10; ++i)
			{
				count[i] = 0;
			}
			for (size_t i = 0; i < data.size(); ++i) 
			{
				count[GetNum(data[i], j)]++;
			}
			for (int i = 1; i < 10; i++) 
			{
				count[i] += count[i - 1];
			}
			for (int i = data.size() - 1; i >= 0; --i) {  
				int k = GetNum(data[i], j);
				bucket[count[k] - 1] = data[i];
				count[k]--;
			}
			for (size_t j = 0; j < data.size(); j++) 
			{
				data[j] = bucket[j];
			}
		}
	}
	size_t get_exchange_time()const
	{
		return exchange_time;
	}
	size_t get_compare_time()const
	{
		return compare_time;
	}
	void clear()
	{
		exchange_time = 0;
		compare_time = 0;
	}
private:
	void AdjustDown(vector<T>& data, size_t size, size_t root)
	{
		size_t parent = root;
		size_t child = parent * 2 + 1;
		while (child < size)
		{
			compare_time++;
			if (child + 1 < size && data[child + 1] > data[child])
			{
				++child;
			}
			if (data[child] > data[parent])
			{
				std::swap(data[child], data[parent]);
				exchange_time++;
				parent = child;
				child = parent * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}
	void qsort(int low, int high, vector<T>& data)
	{
		if (low >= high) 
			return;
		int mindex = partition(low, high, data); 
		qsort(low, mindex - 1, data);
		qsort(mindex + 1, high, data);
	}
	int partition(int low, int high, vector<T>& data)
	{
		T pivot = data[low]; 
		while (low < high) 
		{
			while (low < high && data[high] >= pivot)
			{
				high--;
				compare_time++;
			}
			if (low < high) 
			{
				exchange_time++;
				data[low] = data[high]; 
				low++;
			}
			while (low < high && data[low] <= pivot)
			{
				low++;
				compare_time++;
			}
			if (low < high)
			{
				exchange_time++;
				data[high] = data[low];
				high--;
			}
		}
		data[high] = pivot;
		return high;
	}
	vector<T> split(size_t& pos, vector<T>& data)
	{
		vector<T> temp;
		temp.push_back(data[pos]);
		pos++;
		while (pos < data.size() && data[pos] >= data[pos - 1] && pos < data.size())
		{
			temp.push_back(data[pos]);
			++pos;
		}
		return temp;
	}
	vector<T> merge(vector<T>& v1, vector<T>& v2)
	{
		vector<T> ret;
		int pos1 = 0, pos2 = 0;
		while (pos1 != v1.size() && pos2 != v2.size())
		{
			if (v1[pos1] < v2[pos2])
			{
				ret.push_back(v1[pos1]);
				++pos1;
			}
			else
			{
				ret.push_back(v2[pos2]);
				++pos2;
			}
		}
		while (pos1 == v1.size() && pos2 != v2.size())
		{
			ret.push_back(v2[pos2]);
			++pos2;
		}
		while (pos2 == v2.size() && pos1 != v1.size())
		{
			ret.push_back(v1[pos1]);
			++pos1;
		}
		return ret;
	}
	int MaxBit(vector<int> input)
	{
		int max_num = input[0];
		for (size_t i = 0; i < input.size(); i++)
		{
			if (input[i] > max_num)
			{
				max_num = input[i];
			}
		}
		int p = 0;
		while (max_num > 0)
		{
			p++;
			max_num /= 10;
		}
		return p;
	}
	int GetNum(int num, int d)
	{
		int p = 1;
		while (d - 1 > 0)
		{
			p *= 10;
			d--;
		}
		return num / p % 10;
	}
	size_t exchange_time;
	size_t compare_time;
};

class Test_data
{
public:
	vector<int> order_data(size_t n)
	{
		for (size_t i = 0; i < n; ++i)
		{
			_v.push_back(i + 1);
		}
		return _v;
	}
	vector<int> reverse_data(size_t n)
	{
		for (size_t i = 0; i < n; ++i)
		{
			_v.push_back(n - i);
		}
		return _v;
	}
	vector<int> random_data(size_t n)
	{
		srand((unsigned int)time(nullptr));
		for (size_t i = 0; i < n; i++) 
		{
			_v.push_back(rand() % 30000); 
		}
		return _v;
	}
	vector<int> _v;
};