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
                // ���һƬƴͼ��ʱ����ʾ
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

bool isEqual(int a[N][N], int b[N][N]) //����������Ƿ���ȫһ��
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

int evalute1(int state[N][N], int target[N][N]) //���ۺ���h-���㲻��λ�Ľ��Ƹ���
{
    int num = 0; //num��ʾ��ǰ����state�в���Ŀ��λ���ϵĽ��Ƹ���
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            if (state[i][j] != target[i][j])
                num++; //ͳ��num
    }
    return num; //���ع���
}

int evalute2(int state[N][N], int target[N][N]) {
    int manhattan = 0; // �����پ����ۼ�

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (state[i][j] != target[i][j]) {
                // Ѱ�ҵ�ǰԪ����Ŀ������е�λ��
                for (int x = 0; x < N; x++) {
                    for (int y = 0; y < N; y++) {
                        if (state[i][j] == target[x][y]) {
                            // ���������پ��벢�ۼ�
                            manhattan += abs(i - x) + abs(j - y);
                            break;
                        }
                    }
                }
            }
        }
    }

    return manhattan; // ���ع���
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
            b[i][j] = a[i][j]; //��ԭ�������Խ����ƶ�����
            if (a[i][j] == 0)
            {
                x = i;
                y = j; //��ǿո�λ��
            }
        }
    }
    if (x == 0 && dir == 1)
        return false; //����if����ų����ֲ����ܵ��ƶ�����
    if (x == N - 1 && dir == 2)
        return false; //����false��ָ�����ƶ���ʽ�����У��ص����ú�������ѡ���ƶ�����
    if (y == 0 && dir == 3)
        return false;
    if (y == N - 1 && dir == 4)
        return false;
    if (dir == 1) //���մ����dir���ո�����Ӧ�ķ����ƶ�
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
    return true; //�ƶ��ո�ɹ�����true
}

void statecpy(int a[N][N][maxState], int b[N][N], int n)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            a[i][j][n] = b[i][j]; //���ƶ�����¾����Ƶ�close���У�n���Ա�ʾ��n���������
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
            a[i][j] = b[i][j]; //���Ƶ�ǰ����start
    }
}

int checkAdd(int a[N][N][maxState], int b[N][N], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (isEqual(a, b, i))
            return i; //����������ͬ�򷵻ض�Ӧ����ı��
    }
    return -1;
}

int Astar1(int a[N][N][maxState], int start[N][N], int target[N][N], int path[maxState])
{
    bool visited[maxState] = { false }; // true��ʾ�����ѱ�����
    int fitness[maxState] = { 0 };
    int passLen[maxState] = { 0 };
    int curpos[N][N];
    statecpy(curpos, start);
    int id = 0, Curid = 0;
    int expandedNodes = 0; // ��չ�ڵ���
    int generatedNodes = 1; // ���ɽڵ�������ʼΪ1����Ϊ��ʼ�ڵ�������
    fitness[id] = evalute1(curpos, target);
    statecpy(a, start, id++);
    while (!isEqual(curpos, target)) // ֻҪ��ǰ��������curpos��Ŀ�����target����ͬ��ִ��whileѭ��
    {
        for (int i = 1; i < 5; i++) // �������ҷ���
        {
            int tmp[N][N] = { 0 };
            if (move(curpos, tmp, i)) // ���ΰ�����������˳�����ƶ��ո�
            {
                int state = checkAdd(a, tmp, id);
                generatedNodes++; // ���ɽڵ�����1

                if (state == -1) // ����ӵ�close����
                {
                    path[id] = Curid; // �ߵ���ǰ��id���ڵ�ʵ���Ѿ��߹���·���Ļ���
                    passLen[id] = passLen[Curid] + 1;
                    fitness[id] = evalute1(tmp, target) + passLen[id]; // �ܻ��ѹ���
                    statecpy(a, tmp, id++);                           // ������õ����¾�����Ϊid���Ƶ�open����a�б���
                }
                else // ��ӵ�close����
                {
                    int len = passLen[Curid] + 1, fit = evalute1(tmp, target) + len; // �޸Ĺ��ۺ���
                    if (fit < fitness[state])
                    {
                        path[state] = Curid;
                        passLen[state] = len;
                        fitness[state] = fit;
                        visited[state] = false;
                    } // �����ý��С��Ԥ�ڻ������޸Ķ��ಿ�ֵĹ���ֵ������δ�������ľ�����Ϊfalse
                }
            }
        }
        visited[Curid] = true; // ��curid�������ѱ�������
        expandedNodes++; // ��չ�ڵ�����1

        int minCur = -1;
        for (int i = 0; i < id; i++) // ��open����(visitedֵΪfalse)Ѱ���ܹ��ۺ���fitnessֵ��С�ľ�����Ϊ��һ���������ڵ�
            if (!visited[i] && (minCur == -1 || fitness[i] < fitness[minCur]))
                minCur = i;
        Curid = minCur;             // Curid���ڱ�ʾ��ѡ����һ����չ�ڵ�ľ���ı��
        getState(a, curpos, Curid); // ����ѡ�еľ����Ƹ�curpos
        if (id == maxState)
            return -1; // ����Ѿ������ڵ����ﵽ�趨��maxState������ΪĿ����󲻿ɴ����-1
    }
    std::cout << "Expanded nodes: " << expandedNodes << std::endl;
    std::cout << "Generated nodes: " << generatedNodes << std::endl;
    return Curid; // �����Ŀ����󣬷������վ���ı��
}

int Astar2(int a[N][N][maxState], int start[N][N], int target[N][N], int path[maxState])
{
    bool visited[maxState] = { false }; // true��ʾ�����ѱ�����
    int fitness[maxState] = { 0 };
    int passLen[maxState] = { 0 };
    int curpos[N][N];
    statecpy(curpos, start);
    int id = 0, Curid = 0;
    int expandedNodes = 0; // ��չ�ڵ���
    int generatedNodes = 1; // ���ɽڵ�������ʼΪ1����Ϊ��ʼ�ڵ�������
    fitness[id] = evalute2(curpos, target);
    statecpy(a, start, id++);
    while (!isEqual(curpos, target)) // ֻҪ��ǰ��������curpos��Ŀ�����target����ͬ��ִ��whileѭ��
    {
        for (int i = 1; i < 5; i++) // �������ҷ���
        {
            int tmp[N][N] = { 0 };
            if (move(curpos, tmp, i)) // ���ΰ�����������˳�����ƶ��ո�
            {
                int state = checkAdd(a, tmp, id);
                generatedNodes++; // ���ɽڵ�����1

                if (state == -1) // ����ӵ�close����
                {
                    path[id] = Curid; // �ߵ���ǰ��id���ڵ�ʵ���Ѿ��߹���·���Ļ���
                    passLen[id] = passLen[Curid] + 1;
                    fitness[id] = evalute2(tmp, target) + passLen[id]; // �ܻ��ѹ���
                    statecpy(a, tmp, id++);                           // ������õ����¾�����Ϊid���Ƶ�open����a�б���
                }
                else // ��ӵ�close����
                {
                    int len = passLen[Curid] + 1, fit = evalute2(tmp, target) + len; // �޸Ĺ��ۺ���
                    if (fit < fitness[state])
                    {
                        path[state] = Curid;
                        passLen[state] = len;
                        fitness[state] = fit;
                        visited[state] = false;
                    } // �����ý��С��Ԥ�ڻ������޸Ķ��ಿ�ֵĹ���ֵ������δ�������ľ�����Ϊfalse
                }
            }
        }
        visited[Curid] = true; // ��curid�������ѱ�������
        expandedNodes++; // ��չ�ڵ�����1

        int minCur = -1;
        for (int i = 0; i < id; i++) // ��open����(visitedֵΪfalse)Ѱ���ܹ��ۺ���fitnessֵ��С�ľ�����Ϊ��һ���������ڵ�
            if (!visited[i] && (minCur == -1 || fitness[i] < fitness[minCur]))
                minCur = i;
        Curid = minCur;             // Curid���ڱ�ʾ��ѡ����һ����չ�ڵ�ľ���ı��
        getState(a, curpos, Curid); // ����ѡ�еľ����Ƹ�curpos
        if (id == maxState)
            return -1; // ����Ѿ������ڵ����ﵽ�趨��maxState������ΪĿ����󲻿ɴ����-1
    }
    std::cout << "Expanded nodes: " << expandedNodes << std::endl;
    std::cout << "Generated nodes: " << generatedNodes << std::endl;
    return Curid; // �����Ŀ����󣬷������վ���ı��
}

int BFS(int a[N][N][maxState], int start[N][N], int target[N][N], int path[maxState])
{
    bool visited[maxState] = { false }; // true��ʾ�����ѱ�����
    int fitness[maxState] = { 0 };
    int passLen[maxState] = { 0 };
    int curpos[N][N];
    statecpy(curpos, start);
    int id = 0, Curid = 0;
    int expandedNodes = 0; // ��չ�ڵ���
    int generatedNodes = 1; // ���ɽڵ�������ʼΪ1����Ϊ��ʼ�ڵ�������
    statecpy(a, start, id++);
    while (!isEqual(curpos, target)) // ֻҪ��ǰ��������curpos��Ŀ�����target����ͬ��ִ��whileѭ��
    {
        for (int i = 1; i < 5; i++) // �������ҷ���
        {
            int tmp[N][N] = { 0 };
            if (move(curpos, tmp, i)) // ���ΰ�����������˳�����ƶ��ո�
            {
                int state = checkAdd(a, tmp, id);
                generatedNodes++; // ���ɽڵ�����1

                if (state == -1) // ����ӵ�close����
                {
                    path[id] = Curid; // �ߵ���ǰ��id���ڵ�ʵ���Ѿ��߹���·���Ļ���
                    passLen[id] = passLen[Curid] + 1;
                    fitness[id] = passLen[id]; // �ܻ��ѹ���
                    statecpy(a, tmp, id++);    // ������õ����¾�����Ϊid���Ƶ�open����a�б���
                }
                else // ��ӵ�close����
                {
                    int len = passLen[Curid] + 1, fit = len; // �޸Ĺ��ۺ���
                    if (fit < fitness[state])
                    {
                        path[state] = Curid;
                        passLen[state] = len;
                        fitness[state] = fit;
                        visited[state] = false;
                    } // �����ý��С��Ԥ�ڻ������޸Ķ��ಿ�ֵĹ���ֵ������δ�������ľ�����Ϊfalse
                }
            }
        }
        visited[Curid] = true; // ��curid�������ѱ�������
        expandedNodes++; // ��չ�ڵ�����1

        int minCur = -1;
        for (int i = 0; i < id; i++) // ��open����(visitedֵΪfalse)Ѱ���ܹ��ۺ���fitnessֵ��С�ľ�����Ϊ��һ���������ڵ�
            if (!visited[i] && (minCur == -1 || fitness[i] < fitness[minCur]))
                minCur = i;
        Curid = minCur;             // Curid���ڱ�ʾ��ѡ����һ����չ�ڵ�ľ���ı��
        getState(a, curpos, Curid); // ����ѡ�еľ����Ƹ�curpos
        if (id == maxState)
            return -1; // ����Ѿ������ڵ����ﵽ�趨��maxState������ΪĿ����󲻿ɴ����-1
    }
    std::cout << "Expanded nodes: " << expandedNodes << std::endl;
    std::cout << "Generated nodes: " << generatedNodes << std::endl;
    return Curid; // �����Ŀ����󣬷������վ���ı��
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
    int maxMove = 50;            //���ò�������
    srand((unsigned)time(NULL)); //�������������
    int tmp[N][N];
    while (maxMove--)
    {                             //����ƶ��ո���ʮ�����Ա�֤��ʼ״̬�ľ������в���ͬ
        int dir = rand() % 4 + 1; //dirȡֵ��Χ1~4������ո��ƶ����ĸ�����
        if (move(a, tmp, dir))
            statecpy(a, tmp); //����ԭĿ������˳���Թ����ʼ����
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
        cout << "�� " << j - i << " ��\n";
        show(a, shortest[i]);
    }
}

void InitBlock()
{
	// ��ʼ��ƴͼ��Ƭ
	wchar_t s[3];
	for (int i = 0; i < N * N; i++)
	{
		g_Block[i].Resize(100, 100);
		SetWorkingImage(&g_Block[i]);

		// ����
		cleardevice();
		setfillcolor(HSVtoRGB(float(360.0 * i / 9), 1, 0.5));
		solidrectangle(2, 2, 98, 98);
		// ����
		settextstyle(64, 0, _T("Arial"), 0, 0, 400, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
		setbkmode(TRANSPARENT);
		settextcolor(WHITE);
		_itow_s(i, s, 10);
		outtextxy((100 - textwidth(s)) / 2, 18, s);
	}
	// �ָ���ͼĿ��
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