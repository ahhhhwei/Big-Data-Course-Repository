#pragma once
#include <graphics.h>
#include <time.h>
#include <conio.h>

#define BACKGROUND_IMAGE L"background.jpg"
#define maxState 9999
#define N 3

IMAGE	g_Block[N * N];
byte	g_Map[N][N];
byte	g_EmptyX, g_EmptyY;	

using namespace std;

void Draw()
{
    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++)
        {
            if (g_Map[x][y] != 0)
                putimage(x * 100 + 40, y * 100 + 40, &g_Block[g_Map[x][y]]);
            else
            {
                // 最后一片拼图暂时不显示
                setfillcolor(BLACK);
                solidrectangle(x * 100 + 40, y * 100 + 40, x * 100 + 139, y * 100 + 139);
            }
        }

}

bool isEqual(int a[N][N][maxState], int b[N][N], int n)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (a[i][j][n] != b[i][j])
                return false;
        }
    }
    return true;
}

bool isEqual(int a[N][N], int b[N][N]) //检查两矩阵是否完全一致
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (a[i][j] != b[i][j])
                return false;
        }
    }
    return true;
}

int evalute1(int state[N][N], int target[N][N]) //估价函数h-计算不在位的将牌个数
{
    int num = 0; //num表示当前矩阵state中不在目标位置上的将牌个数
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            if (state[i][j] != target[i][j])
                num++; //统计num
    }
    return num; //返回估价
}

int evalute2(int state[N][N], int target[N][N]) {
    int manhattan = 0; // 曼哈顿距离累加

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (state[i][j] != target[i][j]) {
                // 寻找当前元素在目标矩阵中的位置
                for (int x = 0; x < N; x++) {
                    for (int y = 0; y < N; y++) {
                        if (state[i][j] == target[x][y]) {
                            // 计算曼哈顿距离并累加
                            manhattan += abs(i - x) + abs(j - y);
                            break;
                        }
                    }
                }
            }
        }
    }

    return manhattan; // 返回估价
}

void findBrack(int a[N][N], int x, int y)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (a[i][j] == 0)
            {
                x = i;
                y = j;
                return;
            }
        }
    }
}

bool move(int a[N][N], int b[N][N], int dir)
{
    //1 up 2 down 3 left 4 right
    int x = 0, y = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            b[i][j] = a[i][j]; //将原矩阵复制以进行移动操作
            if (a[i][j] == 0)
            {
                x = i;
                y = j; //标记空格位置
            }
        }
    }
    if (x == 0 && dir == 1)
        return false; //四条if语句排除四种不可能的移动方向
    if (x == N - 1 && dir == 2)
        return false; //返回false意指此种移动方式不可行，回到调用函数重新选择移动方向
    if (y == 0 && dir == 3)
        return false;
    if (y == N - 1 && dir == 4)
        return false;
    if (dir == 1) //按照传入的dir将空格往相应的方向移动
    {
        b[x - 1][y] = 0;
        b[x][y] = a[x - 1][y];
    }
    else if (dir == 2)
    {
        b[x + 1][y] = 0;
        b[x][y] = a[x + 1][y];
    }
    else if (dir == 3)
    {
        b[x][y - 1] = 0;
        b[x][y] = a[x][y - 1];
    }
    else if (dir == 4)
    {
        b[x][y + 1] = 0;
        b[x][y] = a[x][y + 1];
    }
    else
        return false;
    return true; //移动空格成功返回true
}

void statecpy(int a[N][N][maxState], int b[N][N], int n)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            a[i][j][n] = b[i][j]; //将移动完的新矩阵复制到close表中，n可以表示第n步搜索结果
        }
    }
}

void getState(int a[N][N][maxState], int b[N][N], int n)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            b[i][j] = a[i][j][n];
        }
    }
}

void statecpy(int a[N][N], int b[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            a[i][j] = b[i][j]; //复制当前矩阵start
    }
}

int checkAdd(int a[N][N][maxState], int b[N][N], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (isEqual(a, b, i))
            return i; //若两矩阵相同则返回对应矩阵的编号
    }
    return -1;
}

int Astar1(int a[N][N][maxState], int start[N][N], int target[N][N], int path[maxState])
{
    bool visited[maxState] = { false }; // true表示矩阵已被遍历
    int fitness[maxState] = { 0 };
    int passLen[maxState] = { 0 };
    int curpos[N][N];
    statecpy(curpos, start);
    int id = 0, Curid = 0;
    int expandedNodes = 0; // 扩展节点数
    int generatedNodes = 1; // 生成节点数，初始为1，因为起始节点已生成
    fitness[id] = evalute1(curpos, target);
    statecpy(a, start, id++);
    while (!isEqual(curpos, target)) // 只要当前矩阵序列curpos与目标矩阵target不相同即执行while循环
    {
        for (int i = 1; i < 5; i++) // 向四周找方向
        {
            int tmp[N][N] = { 0 };
            if (move(curpos, tmp, i)) // 依次按照上下左右顺序尝试移动空格
            {
                int state = checkAdd(a, tmp, id);
                generatedNodes++; // 生成节点数加1

                if (state == -1) // 不添加到close表中
                {
                    path[id] = Curid; // 走到当前第id个节点实际已经走过的路径的花费
                    passLen[id] = passLen[Curid] + 1;
                    fitness[id] = evalute1(tmp, target) + passLen[id]; // 总花费估价
                    statecpy(a, tmp, id++);                           // 将处理得到的新矩阵编号为id复制到open表中a中保存
                }
                else // 添加到close表中
                {
                    int len = passLen[Curid] + 1, fit = evalute1(tmp, target) + len; // 修改估价函数
                    if (fit < fitness[state])
                    {
                        path[state] = Curid;
                        passLen[state] = len;
                        fitness[state] = fit;
                        visited[state] = false;
                    } // 若所得结果小于预期花费则修改多余部分的估价值，并将未遍历过的矩阵标记为false
                }
            }
        }
        visited[Curid] = true; // 第curid个矩阵已被遍历过
        expandedNodes++; // 扩展节点数加1

        int minCur = -1;
        for (int i = 0; i < id; i++) // 从open表中(visited值为false)寻找总估价函数fitness值最小的矩阵作为下一个带搜索节点
            if (!visited[i] && (minCur == -1 || fitness[i] < fitness[minCur]))
                minCur = i;
        Curid = minCur;             // Curid现在表示被选作下一个扩展节点的矩阵的编号
        getState(a, curpos, Curid); // 将被选中的矩阵复制给curpos
        if (id == maxState)
            return -1; // 如果已经搜索节点数达到设定的maxState，则认为目标矩阵不可达，返回-1
    }
    std::cout << "Expanded nodes: " << expandedNodes << std::endl;
    std::cout << "Generated nodes: " << generatedNodes << std::endl;
    return Curid; // 已求得目标矩阵，返回最终矩阵的编号
}

int Astar2(int a[N][N][maxState], int start[N][N], int target[N][N], int path[maxState])
{
    bool visited[maxState] = { false }; // true表示矩阵已被遍历
    int fitness[maxState] = { 0 };
    int passLen[maxState] = { 0 };
    int curpos[N][N];
    statecpy(curpos, start);
    int id = 0, Curid = 0;
    int expandedNodes = 0; // 扩展节点数
    int generatedNodes = 1; // 生成节点数，初始为1，因为起始节点已生成
    fitness[id] = evalute2(curpos, target);
    statecpy(a, start, id++);
    while (!isEqual(curpos, target)) // 只要当前矩阵序列curpos与目标矩阵target不相同即执行while循环
    {
        for (int i = 1; i < 5; i++) // 向四周找方向
        {
            int tmp[N][N] = { 0 };
            if (move(curpos, tmp, i)) // 依次按照上下左右顺序尝试移动空格
            {
                int state = checkAdd(a, tmp, id);
                generatedNodes++; // 生成节点数加1

                if (state == -1) // 不添加到close表中
                {
                    path[id] = Curid; // 走到当前第id个节点实际已经走过的路径的花费
                    passLen[id] = passLen[Curid] + 1;
                    fitness[id] = evalute2(tmp, target) + passLen[id]; // 总花费估价
                    statecpy(a, tmp, id++);                           // 将处理得到的新矩阵编号为id复制到open表中a中保存
                }
                else // 添加到close表中
                {
                    int len = passLen[Curid] + 1, fit = evalute2(tmp, target) + len; // 修改估价函数
                    if (fit < fitness[state])
                    {
                        path[state] = Curid;
                        passLen[state] = len;
                        fitness[state] = fit;
                        visited[state] = false;
                    } // 若所得结果小于预期花费则修改多余部分的估价值，并将未遍历过的矩阵标记为false
                }
            }
        }
        visited[Curid] = true; // 第curid个矩阵已被遍历过
        expandedNodes++; // 扩展节点数加1

        int minCur = -1;
        for (int i = 0; i < id; i++) // 从open表中(visited值为false)寻找总估价函数fitness值最小的矩阵作为下一个带搜索节点
            if (!visited[i] && (minCur == -1 || fitness[i] < fitness[minCur]))
                minCur = i;
        Curid = minCur;             // Curid现在表示被选作下一个扩展节点的矩阵的编号
        getState(a, curpos, Curid); // 将被选中的矩阵复制给curpos
        if (id == maxState)
            return -1; // 如果已经搜索节点数达到设定的maxState，则认为目标矩阵不可达，返回-1
    }
    std::cout << "Expanded nodes: " << expandedNodes << std::endl;
    std::cout << "Generated nodes: " << generatedNodes << std::endl;
    return Curid; // 已求得目标矩阵，返回最终矩阵的编号
}

int BFS(int a[N][N][maxState], int start[N][N], int target[N][N], int path[maxState])
{
    bool visited[maxState] = { false }; // true表示矩阵已被遍历
    int fitness[maxState] = { 0 };
    int passLen[maxState] = { 0 };
    int curpos[N][N];
    statecpy(curpos, start);
    int id = 0, Curid = 0;
    int expandedNodes = 0; // 扩展节点数
    int generatedNodes = 1; // 生成节点数，初始为1，因为起始节点已生成
    statecpy(a, start, id++);
    while (!isEqual(curpos, target)) // 只要当前矩阵序列curpos与目标矩阵target不相同即执行while循环
    {
        for (int i = 1; i < 5; i++) // 向四周找方向
        {
            int tmp[N][N] = { 0 };
            if (move(curpos, tmp, i)) // 依次按照上下左右顺序尝试移动空格
            {
                int state = checkAdd(a, tmp, id);
                generatedNodes++; // 生成节点数加1

                if (state == -1) // 不添加到close表中
                {
                    path[id] = Curid; // 走到当前第id个节点实际已经走过的路径的花费
                    passLen[id] = passLen[Curid] + 1;
                    fitness[id] = passLen[id]; // 总花费估价
                    statecpy(a, tmp, id++);    // 将处理得到的新矩阵编号为id复制到open表中a中保存
                }
                else // 添加到close表中
                {
                    int len = passLen[Curid] + 1, fit = len; // 修改估价函数
                    if (fit < fitness[state])
                    {
                        path[state] = Curid;
                        passLen[state] = len;
                        fitness[state] = fit;
                        visited[state] = false;
                    } // 若所得结果小于预期花费则修改多余部分的估价值，并将未遍历过的矩阵标记为false
                }
            }
        }
        visited[Curid] = true; // 第curid个矩阵已被遍历过
        expandedNodes++; // 扩展节点数加1

        int minCur = -1;
        for (int i = 0; i < id; i++) // 从open表中(visited值为false)寻找总估价函数fitness值最小的矩阵作为下一个带搜索节点
            if (!visited[i] && (minCur == -1 || fitness[i] < fitness[minCur]))
                minCur = i;
        Curid = minCur;             // Curid现在表示被选作下一个扩展节点的矩阵的编号
        getState(a, curpos, Curid); // 将被选中的矩阵复制给curpos
        if (id == maxState)
            return -1; // 如果已经搜索节点数达到设定的maxState，则认为目标矩阵不可达，返回-1
    }
    std::cout << "Expanded nodes: " << expandedNodes << std::endl;
    std::cout << "Generated nodes: " << generatedNodes << std::endl;
    return Curid; // 已求得目标矩阵，返回最终矩阵的编号
}

void show(int a[N][N][maxState], int n)
{
    cout << "-------------------------------\n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            g_Map[j][i] = a[i][j][n];
            
            cout << a[i][j][n] << " ";
        }
        cout << endl;
    }
    Draw();
    Sleep(800);
    cout << "-------------------------------\n";
}

int calDe(int a[N][N])
{
    int sum = 0;
    for (int i = 0; i < N * N; i++)
    {
        for (int j = i + 1; j < N * N; j++)
        {
            int m, n, c, d;
            m = i / N;
            n = i % N;
            c = j / N;
            d = j % N;
            if (a[c][d] == 0)
                continue;
            if (a[m][n] > a[c][d])
                sum++;
        }
    }
    return sum;
}

void autoGenerate(int a[N][N])
{
    int maxMove = 50;            //设置步数上限
    srand((unsigned)time(NULL)); //生成随机数种子
    int tmp[N][N];
    while (maxMove--)
    {                             //随机移动空格五十步可以保证初始状态的矩阵序列不相同
        int dir = rand() % 4 + 1; //dir取值范围1~4，代表空格移动的四个方向
        if (move(a, tmp, dir))
            statecpy(a, tmp); //打乱原目标矩阵的顺序以构造初始矩阵
    }
}

void results_op(int res, int path[maxState], int a[N][N][maxState])
{

    int shortest[maxState] = { 0 }, j = 0;
    while (res != 0)
    {
        shortest[j++] = res;
        res = path[res];
    }
    for (int i = j - 1; i >= 0; i--)
    {
        cout << "第 " << j - i << " 步\n";
        show(a, shortest[i]);
    }
}

void InitBlock()
{
	// 初始化拼图碎片
	wchar_t s[3];
	for (int i = 0; i < N * N; i++)
	{
		g_Block[i].Resize(100, 100);
		SetWorkingImage(&g_Block[i]);

		// 背景
		cleardevice();
		setfillcolor(HSVtoRGB(float(360.0 * i / 9), 1, 0.5));
		solidrectangle(2, 2, 98, 98);
		// 文字
		settextstyle(64, 0, _T("Arial"), 0, 0, 400, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
		setbkmode(TRANSPARENT);
		settextcolor(WHITE);
		_itow_s(i, s, 10);
		outtextxy((100 - textwidth(s)) / 2, 18, s);
	}
	// 恢复绘图目标
	SetWorkingImage(NULL);
}

void MoveTo(int newx, int newy)
{
	g_Map[g_EmptyX][g_EmptyY] = g_Map[newx][newy];
	g_Map[newx][newy] = N * N - 1;
	g_EmptyX = newx;
	g_EmptyY = newy;
}

void RandMap(int(*start)[N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            g_Map[i][j] = start[i][j];
        }
    }
	g_EmptyX = N - 1;
	g_EmptyY = N - 1;
}