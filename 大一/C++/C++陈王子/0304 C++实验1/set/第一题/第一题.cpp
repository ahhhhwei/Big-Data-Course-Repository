#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;

int* InitArray(unsigned n) {
    int num;
    int* arr=new int[n];
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        do {
            num = rand() % 10000;
        } while (find(arr, arr + i, num) != arr + i);
        arr[i] = num;
    }
    cout << "Initialized" << endl;
    return arr;
}

void Display(int* p,unsigned n) {
    cout << "Displaying" << endl;
    for (int i = 0; i < n; i++) {
        cout << p[i] << " ";
    }
    cout << "Displayed" << endl;
}

int digitReverse(int num) {
    int reversedNum = 0;
    int pow10 = 100;
    while (num != 0) {
        int digit = num % 10;
        reversedNum += digit * pow10;
        pow10 /= 10;
        num /= 10;
    }
    return reversedNum;
}

void SortArray(int* p, unsigned n) {
    cout << "Sorting" << endl;
    for (int i = 0; i < n; i++) {
        int num = p[i];
        num = digitReverse(num);
        p[i] = num;
    }
    sort(p, p + n);
    cout << "Sorted" << endl;
}


void DestroyArray(int* arr) {
    delete arr;
    cout << "Deleted" << endl;
}

int main()
{
    unsigned n;
    int* p;
    while (cin >> n)
    {
        p = InitArray(n);
        //初始化一个规模为 n 的一维整型数组，并给出随机互异的值进行初始化。
        Display(p, n); //显示数据的初始化情况
        SortArray(p, n);//根据每个数包含的数字按个位、十位和百位和组成的新数值进行升序整理；如 123 对应的新数值为 321，12 的对应的新数值为 210
        Display(p, n); //显示排序后的结果
        DestroyArray(p); //根据需要使用
    }
}