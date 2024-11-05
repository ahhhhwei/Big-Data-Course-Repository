#include <iostream>
using namespace std;

void InitMatrix(int matrix[2][3], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = (i+1)*(j+1);
        }
    }
}

void InitMatrix(int matrix[3][4], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] =i+j+1;
        }
    }
}

//乘法
int** Multiply(int a[2][3], int b[3][4], int rows_a, int cols_a, int cols_b) {
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
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    const int n = 2;
    const int k = 3;
    const int m = 4;
    int a[n][k], b[k][m];
    int** c;
    InitMatrix(a, n, k); //初始化矩阵 a
    InitMatrix(b, k, m); //初始化矩阵 b
    c = Multiply(a, b, n, k, m); //计算 aXb ，实际设计可以省略一个参数 k
    Display(c, n, m); //输出计算结果, 有可能还需要其他参数，根据自己定义的 c 调整
}