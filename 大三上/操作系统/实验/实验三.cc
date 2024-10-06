#include <iostream>
using namespace std;

const int p = 4; // 进程数
const int r = 4; // 资源种类

// 比较函数
int com(int m[r], int n[r]) {
    int i, flag = 0;
    for (i = 0; i < r; i++) {
        if (m[i] < n[i]) {
            flag = 1;
            break;
        }
    }
    if (flag == 1) {
        return 0;
    } else {
        return 1;
    }
}

int test(int need[r]) {
    int i, a, flag = 0;
    for (i = 0, a = 0; i < r; i++) {
        if (need[i] == 0) {
            a++;
        }
    }
    if (a == r) {
        return 1;
    } else {
        return 0;
    }
}

// 安全性检验函数
int stest(int allocations[p][r], int needs[p][r], int availables[r]) {
    int i, j, k, l, flag = 0;
    int need[r], finish[p], available[r];
    for (i = 0; i < p; i++) {
        finish[i] = 0; // finish为1即表示available满足某一进程并让其实现
    }

    cout << "初始available" << '\t';
    for (i = 0; i < r; i++) {
        available[i] = availables[i];
        cout << availables[i] << '\t';
    } // 保存数据
    cout << "\n分配序列：\n";
    for (k = 1; k <= p; k++) { // 全搜索，直至实现或不可能实现
        for (i = 0; i < p; i++) {
            if (finish[i] == 1) {
                continue;
            } else {
                for (j = 0; j < r; j++) {
                    need[j] = needs[i][j];
                }
                if (com(available, need)) {

                    cout << "\n第" << k << "次分配进程为:";
                    finish[i] = 1;
                    cout << i + 1 << '\t';
                    cout << "  此时的available：" << '\t';
                    for (l = 0; l < r; l++) {
                        available[l] = available[l] + allocations[i][l];
                        cout << available[l] << '\t';
                    }
                    break;
                }
            }
        }
    }
    cout << endl;
    for (l = 0; l < p; l++) {
        if (finish[l] == 0) {
            flag = 1;
        }
    }
    if (flag == 0) {
        return 1; // flag为记录finish是否有0存在的标记，当flag=0时，安全
    } else {
        return 0;
    }
}

// 申请进程后的安全性检验函数
void rtest(int b[p][r], int c[p][r], int d[r], int req[r], int n) { // req-request，n-第n个进程申请资源
    int i, j;
    int t[r];
    n = n - 1;
    for (i = 0; i < r; i++) {
        t[i] = c[n][i];
    }
    if (com(t, req)) { // 对request和need进行比较
        cout << "第" << n + 1 << "个进程申请资源通过(request<=need)\n";

        if (com(d, req)) { // 对request和available进行比较
            for (j = 0; j < r; j++) {
                b[n][j] = b[n][j] + req[j];
                c[n][j] = c[n][j] - req[j];
                d[j] = d[j] - req[j];
            }
            if (stest(b, c, d)) {
                cout << "第" << n + 1 << "个进程申请资源成功(request<=available)\n";
                int a = test(d);
                if (a == 1) {
                    for (i = 0; i < r; i++) {
                        d[i] = b[n][i] + d[i]; // 资源回归available
                    }
                }
            } else {
                cout << "第" << n + 1 << "个进程申请资源失败，恢复以前状态。安全队列寻找失败\n";
                for (j = 0; j < r; j++) {
                    b[n][j] = b[n][j] - req[j];
                    c[n][j] = c[n][j] + req[j];
                    d[j] = d[j] + req[j];
                }
            }
        } else {
            cout << "进程等待…(request>available)…\n";
        }
    } else {
        cout << "第" << n + 1 << "个进程申请资源失败，恢复以前状态。安全队列寻找失败\n";
    }
}

 
int main()
{
    int j, n, i, t; // n-第n个资源申请
    int flag1 = 1;  // flag1作为循环条件
    int ALL[4] = {16, 5, 2, 8};
    int max[4][4] = {4, 4, 2, 1, 4, 3, 1, 1, 13, 5, 2, 7, 6, 1, 1, 1};
    int allocation[4][4] = {4, 0, 0, 1, 1, 2, 1, 0, 1, 1, 0, 2, 3, 1, 1, 0};
    int need[4][4] = {0, 4, 2, 0, 3, 1, 0, 1, 12, 4, 2, 5, 3, 0, 0, 1};
    int available[4];
    int request[4];
 
    for (i = 0; i < r; i++)
    {
        t = 0;
        for (j = 0; j < p; j++)
        {
            t = t + allocation[j][i];
        }
        available[i] = ALL[i] - t;
    }
    //	input(max, allocation, c, available);
    printf("max\tallocation\tneed\tavailable\n");
    for (i = 0; i < p; i++)
    {
        for (j = 0; j < r; j++)
        {
            cout << max[i][j] << " ";
        }
        cout << '\t';
        for (j = 0; j < r; j++)
        {
            cout << allocation[i][j] << " ";
        }
        cout << '\t' << '\t';
        for (j = 0; j < r; j++)
        {
            cout << need[i][j] << " ";
        }
        cout << '\t';
        if (i == 0)
        {
            for (j = 0; j < r; j++)
            {
                cout << available[j] << " ";
            }
        }
        cout << endl;
    }
 
    cout << endl;
    if (stest(allocation, need, available) == 1)
        cout << "初始状态安全！\n";
    else
    {
        cout << "初始状态不安全，请仔细检查！\n";
        return 0;
    }
 
    while (flag1)
    {
        cout << "输入申请资源的进程的序号：\n";
        cin >> n;
 
        cout << "输入request数据：\n";
        for (j = 0; j < r; j++)
            cin >> request[j];
 
        rtest(allocation, need, available, request, n);
        printf("max\tallocation\tneed\tavailable\n");
        for (i = 0; i < p; i++)
        {
            for (j = 0; j < r; j++)
            {
                cout << max[i][j] << " ";
            }
            cout << '\t';
            for (j = 0; j < r; j++)
            {
                cout << allocation[i][j] << " ";
            }
            cout << '\t' << '\t';
            for (j = 0; j < r; j++)
            {
                cout << need[i][j] << " ";
            }
            cout << '\t';
            if (i == 0)
            {
                for (j = 0; j < r; j++)
                {
                    cout << available[j] << " ";
                }
            }
            cout << endl;
        }
        cout << "\n继续分配输入1，退出输入0：\n";
        cin >> flag1;
    }
 
    return 0;
}