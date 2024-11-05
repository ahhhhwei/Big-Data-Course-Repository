#include <iostream>
#include <algorithm>
using namespace std;

void Display(int* p,unsigned n) {
    for (int i = 0; i < n; i++) {
        cout << p[i] << " ";
    }
    cout << endl;
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
    for (int i = 0; i < n; i++) {
        int num = p[i];
        num = digitReverse(num);
        p[i] = num;
    }
    sort(p, p + n);
}


void DestroyArray(int* arr) {
    delete arr;
}


int main()
{
    int groupNo;
    while (cin >> groupNo) {
        //二维矩阵 result，行为组数目，列为数据个数
        int GroupNo = groupNo;
        int** result = new int*[GroupNo];
        int* DataNo=new int[GroupNo];
        while (groupNo--) {
            int dataNo;//当前组数据个数
            cin >> dataNo;
            DataNo[groupNo] = dataNo;
            result[groupNo] = new int[dataNo];
            int* input = new int[dataNo];
            int* sorted = new int[dataNo];//特别排序后的结果
            for (int i = 0; i < dataNo; i++) {
                cin >> input[i];
                sorted[i] = input[i];
            }
            //仅按照定义顺序排列sorted
            SortArray(sorted, dataNo);
            for (int i = 0; i < dataNo; i++) {
                for (int j = 0; j < dataNo; j++) {
                    if (digitReverse(input[i]) == sorted[j]) {
                        result[groupNo][j] = input[i];
                    }
                }
            }
        }
        cout << "The result is:" << endl;
        for(int i=GroupNo;i>0;i--)
            Display(result[i-1], DataNo[i-1]);
    }
}