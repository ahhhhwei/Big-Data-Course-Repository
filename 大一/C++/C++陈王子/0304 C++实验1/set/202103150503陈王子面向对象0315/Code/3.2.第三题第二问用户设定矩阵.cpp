#include <iostream>
#include <cstdlib>
using namespace std;

// 初始化矩阵
void InitMatrix(int** matrix, int rows, int cols) {
    srand(time(NULL));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
}

//乘法
int** Multiply(int** a, int** b, int rows_a, int cols_a, int cols_b) {
    int** c=new int*[rows_a];
    for (int i = 0; i < rows_a; i++) {
        c[i] = new int[cols_b];
    }
    for (int i = 0; i < rows_a; i++) {
        for (int j = 0; j < cols_b; j++) {
            c[i][j] = 0;
            for (int k = 0; k < cols_a; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

// 显示矩阵
void Display(int** matrix, int rows, int cols)
{
    cout << "Displaying" << endl;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << matrix[i][j] << "\t ";
        }
        cout << endl;
    }
    cout << "Displayed" << endl;
}

int main()
{
    int n, k, m;
    int i, j;
    cout << "row of matrix a:" ;
    cin >> n;
    cout << "column of matrix a and row of matrix b:";
    cin >> k;
    cout << "column of matrix b:";
    cin >> m;
    int** a = new int*[n];
    for (i = 0; i < n; i++) {
        a[i] = new int[k];
    }
    int** b = new int* [k];
    for (i = 0; i < k; i++) {
        b[i] = new int[m];
    }
    int** c = new int* [n];
    for (i = 0; i < n; i++) {
        c[i] = new int[m];
    }
    InitMatrix(a, n, k); //初始化矩阵 a
    Display(a, n, k);
    InitMatrix(b, k, m); //初始化矩阵 b
    Display(b, k, m);
    c = Multiply(a, b, n, k, m); //计算 aXb ，实际设计可以省略一个参数 k
    Display(c, n, m); //输出计算结果, 有可能还需要其他参数，根据自己定义的 c 调整
}


