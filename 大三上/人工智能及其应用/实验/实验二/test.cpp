#include <iostream>
#include <ctime>
#include <cstdlib>
#include "game.h"

int main()
{
    HWND wnd = initgraph(400, 400);
    InitBlock();
    loadimage(NULL, BACKGROUND_IMAGE, 400, 400);
    int a[N][N][maxState] = { 0 };                     
    int start[N][N] = { 1, 2, 3, 8, 0, 4, 7, 6, 5 };    
    autoGenerate(start);
    RandMap(start);                     
    cout << "原始矩阵为：" << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++) 
        {
            cout << start[i][j] << ' ';
        }
        cout << endl;
    }
    int target[N][N] = { 1, 2, 3, 8, 0, 4, 7, 6, 5 }; 
    int start_demo[N][N] = { 0 }, target_demo[N][N] = { 0 };
    statecpy(start_demo, start);
    statecpy(target_demo, target);
    if (!(calDe(start) % 2 == calDe(target) % 2))
    {
        cout << "在此初始状态及目标序列情况下，无解\n";
        system("pause");
        return 0;
    }
    int path[maxState] = { 0 };
    // double begin = GetTickCount();
    cout << "使用简单错排的A*算法处理如下：" << endl;
    int res = Astar1(a, start, target, path);
    if (res == -1)
    {
        cout << "此次搜索已经搜索超过" << maxState << "个节点，认为目标矩阵不可达\n";
        system("pause");
        return 0;
    }
    results_op(res, path, a);
    Sleep(3000);
    // cout << "运行时间" << GetTickCount() - begin << endl;

    // begin = GetTickCount();
    cout << "使用曼哈顿距离的A*算法处理如下：" << endl;
    for (int i = 0; i < maxState; i++)
    {
        path[0] = 0;
    }
    res = Astar2(a, start, target, path);
    if (res == -1)
    {
        cout << "此次搜索已经搜索超过" << maxState << "个节点，认为目标矩阵不可达\n";
        system("pause");
        return 0;
    }
    results_op(res, path, a);
    Sleep(3000);
    for (int i = 0; i < maxState; i++)
    {
        path[0] = 0;
    }
    // cout << "运行时间" << GetTickCount() - begin << endl;

    // begin = GetTickCount();
    cout << "\n仅使用路径花费作为启发函数的A*算法(BFS)处理结果如下：" << endl;
    res = BFS(a, start_demo, target_demo, path);
    if (res == -1)
    {
        cout << "此次搜索已经搜索超过" << maxState << "个节点，认为目标矩阵不可达\n";

        system("pause");
        exit(0);
    }
    results_op(res, path, a);
    // cout << "运行时间" << GetTickCount() - begin << endl;
    system("pause");
    return 0;
}