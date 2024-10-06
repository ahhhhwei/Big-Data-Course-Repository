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
    cout << "ԭʼ����Ϊ��" << endl;
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
        cout << "�ڴ˳�ʼ״̬��Ŀ����������£��޽�\n";
        system("pause");
        return 0;
    }
    int path[maxState] = { 0 };
    // double begin = GetTickCount();
    cout << "ʹ�ü򵥴��ŵ�A*�㷨�������£�" << endl;
    int res = Astar1(a, start, target, path);
    if (res == -1)
    {
        cout << "�˴������Ѿ���������" << maxState << "���ڵ㣬��ΪĿ����󲻿ɴ�\n";
        system("pause");
        return 0;
    }
    results_op(res, path, a);
    Sleep(3000);
    // cout << "����ʱ��" << GetTickCount() - begin << endl;

    // begin = GetTickCount();
    cout << "ʹ�������پ����A*�㷨�������£�" << endl;
    for (int i = 0; i < maxState; i++)
    {
        path[0] = 0;
    }
    res = Astar2(a, start, target, path);
    if (res == -1)
    {
        cout << "�˴������Ѿ���������" << maxState << "���ڵ㣬��ΪĿ����󲻿ɴ�\n";
        system("pause");
        return 0;
    }
    results_op(res, path, a);
    Sleep(3000);
    for (int i = 0; i < maxState; i++)
    {
        path[0] = 0;
    }
    // cout << "����ʱ��" << GetTickCount() - begin << endl;

    // begin = GetTickCount();
    cout << "\n��ʹ��·��������Ϊ����������A*�㷨(BFS)���������£�" << endl;
    res = BFS(a, start_demo, target_demo, path);
    if (res == -1)
    {
        cout << "�˴������Ѿ���������" << maxState << "���ڵ㣬��ΪĿ����󲻿ɴ�\n";

        system("pause");
        exit(0);
    }
    results_op(res, path, a);
    // cout << "����ʱ��" << GetTickCount() - begin << endl;
    system("pause");
    return 0;
}