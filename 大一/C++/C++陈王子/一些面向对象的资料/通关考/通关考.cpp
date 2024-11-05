/*
只需要把每五个数字加起来，结果对26取模，
然后用0 对应a，1对应b...以此类推即可

Input
多组输入，每组第一行输入n，接下来n行，每行5个数字，每个数字之间用空格分隔。

Output
输出最终的明文,每行一个小写字母

Sample Input
3
1 2 3 4 5
3 2 5 8 4
6 9 8 5 4
Sample Output
p
w
g
*/

#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
char num2char(int a) {
    return(char('a' + a % 26));
}
int main() {
    double num,array[5];
    while (cin >> num) {
        for (int i = 0; i < num; i++) {
            for (int i = 0; i < 5; i++) {
                cin >> array[i];
            }
            cout<<(num2char(accumulate(array, array + 5, 0)))<<endl;
        }
        continue;
    }
}



/*
Description
根据读入的两个正整数，计算他们的最大公约数，数据有多组。

Input
 第一行是一个正整数n(1<=n<=50),接下来n行每行包括两个正整数a和b(1<=a,b<=10000);

Output
每行输出形式为Case t: x，其中t从1到n，x为运算答案，共n行。
*/
#include <iostream>
#include <vector>
using namespace std;
int gcd(int a, int b) {
    int c;
    while (a % b != 0) {
        c = a % b;
        a = b;
        b = c;
    }
    return b;
}
int main() {
    double num,array[2];
    while (cin >> num) {
        for (int i = 0; i < num; i++) {
            cin >> array[0] >> array[1];
            cout<<"Case "<<i+1<<": "<<gcd(array[0],array[1])<< endl;
        }
        continue;
    }
}

/*
Description
小明是一个很懒的人，比如说，计算1234+69，他只会计算4+9，对于答案也只记录3，简单的说，就是只对个位数进行计算。那么对于一下数据，请输出小明式答案。

Input
有多组数据，每组数据包括a，b（a,b<=10000）；

Output
对每组数据输出小明式答案。
*/
#include <iostream>
#include <string>
using namespace std;
int getEnd(string s) {
    return ((s[s.size() - 1]) - '0');
}
int main() {
    string s1, s2;
    while (cin >> s1>>s2) {
        cout << (getEnd(s1) + getEnd(s2))%10 <<endl;
        continue;
    }
}


//回文串

#include <iostream>
using namespace std;
string palin(string s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == s[s.size() - i-1]) {
            continue;
        }
        else {
            return "No\n";
        }
    }
    return "Yes\n";
}
int main() {
    string s;
    while (cin >> s&&s!="0") {
        cout <<palin(s);
    }
}

/*Description
输入两点坐标（X1,Y1）,（X2,Y2）,计算并输出两点间的距离。

Input
输入数据有多组，每组占一行，由4个实数组成，分别表示x1,y1,x2,y2,数据之间用空格隔开

Output
对于每组输入数据，输出一行，结果保留两位小数。
*/
#include <iostream>
#include <iomanip>
#include <math.h>
#include <string>
using namespace std;
int main() {
    long long x1, y1, x2, y2;
    while(!(cin>>x1).eof()) {
        cin >> y1 >> x2 >> y2;
        cout << setprecision(2) << fixed << pow(pow(abs(x1 - x2), 2) + pow(abs(y1 - y2), 2), 0.5) << endl;
    }
}

#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;
int main() {
    double x1, y1, x2, y2;
    while (cin >> x1 >> y1 >> x2 >> y2) {
        cout << setprecision(2) << fixed << sqrt((x1 - x2)* (x1 - x2) + (y1 - y2)* (y1 - y2)) << endl;
    }
}



/*有好几组测试数据。每一组数据包括两行。
第一行的第一个数表示第一组数据的个数N（0<=N<=1000)。后面N个数表示第一组数据。
第二行第一个数表示第二组数据的个数M（0<=M<=1000）。后面M个数表示第二组数据。

Output
对于每一个测试样例。输出合并后的数据。
两个不同的数据之间用空格隔开。
每两个不同的测试样例之间用空行表示。

Sample Input
2 1 3
4 6 7 3 4
Sample Output
1 3 3 4 6 7*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    vector<int> data;
    int n1, n2, temp;
    while (!(cin>>n1).eof()){
        for (int i = 0; i < n1; i++) {
            cin >> temp;
            data.push_back(temp);

        }
        cin >>n2;
        for (int i = 0; i < n2; i++) {
            cin >> temp;
            data.push_back(temp);

        }
        sort(data.begin(), data.end());
        for (int i = 0; i < data.size(); i++) {
            if (i == 0) {
                cout << data[i];
                continue;
            }
            cout <<" " << data[i];
        }
        cout <<"\n" << endl;
        data.clear();
    }
}
/*
空房间里有N盏灯，编号从1到N.第一个人应该打开所有的灯，第二个人应该按下那些数字是2的倍数的开关（这些灯将被关闭）。第三个人应该按下那些数字是3的倍数的开关（灯将关闭，灯将打开）.以此类推。
结果，哪盏灯最终会亮起？

输入
有几个测试用例。
每个案例都包含 N 和 K.（K<=N<=1000）

输出
指示灯亮起时输出所有数字。
两个不同的数字之间有一个空格。两个不同的案例之间有一个空行。

示例输入
4 2
6 2
示例输出
1 3

1 3 5*/




/*华氏温度和摄氏温度是目前比较常用的温度表示单位，如英国、美国、加拿大、澳大利亚和印度等国多用华氏温度；而世界科技界和工农业生产中，以及我国、法国等国家则多用摄氏温度。
我们知道，水的冰点是0°C或32°F，沸点是100°C或212°F。设计一个程序，将摄氏温度换算为华氏温度。

Input
输入含有一些整数n(-100≤n≤500)，表示摄氏温度，若n为999表示处理结束。

Output
分别计算摄氏温度n所对应的华氏温度值（保留一位小数），每个输出占一行。

Sample Input
150
-23
3
0
999
Sample Output
302.0
-9.4
37.4
32.0*/

#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    const double d = (212 - 32) ;
    int n;
    while (cin >> n&&n!=999) {
        cout << setprecision(1) << fixed << 32 + (d * n)/100  << endl;
    }
}

/*Description
输入一个数字n, 输出’*’字符的直角三角形

Input
输入多组数据，每组数据占一行，为一个整型数字n <30

Output
输出’*’字符的直角三角形，具体看Sample

Sample Input
3
Sample Output
***
**
**/
#include <iostream>
#include <string>
using namespace std;
int main()
{
    int n;
    while (cin >> n) {
        for (int i = 0; i < n; i++) {
            cout << string(n-i, '*') << endl;
        }
    }
}

/*判断一个正整数能不能写成2的k次，k是整数

input

第一行输入一个整数N，表示测试数据的组数(1<N=<20)
每组数据只有一个数M（1<=M<=1000）

output

每组输出一行，如果M可以写成2的k次就输出Yes，否则输出No

Sample Input

3
2
5
16
Sample Output

Yes
No
Yes*/



#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool is2(double a) {
    if (a % 2==0) {
        a = a / 2;
        if (a == 1) {
            return true;
        }
        return is2(a);
    }
    else {
        return false;
    }
    return true;
}
double n;
int main()
{
    cin >> n;
    while (cin >> n) {
        if (is2(n)) {
            cout << "Yes";
        }
        else {
            cout << "No";
        }
        cout<<endl;
    }
}



#include <bits/stdc++.h>
using namespace std;
int n;
int main()
{
    cin >> n;
    while (cin >> n)
    {
        if (int(log2(n)) - log2(n) == 0)
            cout << "Yes";
        else
            cout << "No";
        cout << endl;
    }
}



