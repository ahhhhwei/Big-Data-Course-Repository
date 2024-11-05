
#include <iostream>
#include <cmath>
using namespace std;

class Position {
private:
    double x;  // 横坐标
    double y;  // 纵坐标

public:
    // 默认构造函数，将坐标设置为原点
    Position() {
        x = 0;
        y = 0;
    }

    // 构造函数，根据给定的横、纵坐标进行初始化
    Position(double x_axis, double y_axis=0) {
        x = x_axis;
        y = y_axis;
    }

    // 复制构造函数
    Position(const Position& p) {
        x = p.x;
        y = p.y;
    }

    // 显示当前坐标值
    void show() const {
        cout << "(" << x << "," << y << ")" << endl;
    }

    // 设置坐标值
    void set(double x_axis, double y_axis) {
        x = x_axis;
        y = y_axis;
    }

    // 设置坐标值为原点
    void set() {
        x = 0;
        y = 0;
    }

    friend double Distance(const Position& p1, const Position& p2);
    friend double Distance(const Position& p1);

    // 计算当前点与另一个点之间的斜率
    double slope(const Position& p) const {
        if (x == p.x) {
            cout << "Error: Cannot calculate the slope" << endl;
            return 0;
        }
        double slope = (y - p.y) / (x - p.x);
        return slope;
    }

    // 计算当前点与原点之间的斜率
    double slope() const {
        Position origin(0,0);
        return slope(origin);
    }

    // 沿x轴方向平移指定的距离
    void move(double dist) {
        x += dist;
    }

    // 沿x轴方向平移指定的距离，沿y轴方向平移指定的距离
    void move(double x_dist, double y_dist) {
        x += x_dist;
        y += y_dist;
    }
};

// 计算当前点与另一个点之间的距离
double Distance(const Position& p1, const Position& p2) {
    double dist = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
    return dist;
}

// 计算当前点与原点之间的距离
double Distance(const Position& p1) {
    double dist = sqrt(pow(p1.x - 0, 2) + pow(p1.y - 0, 2));
    return dist;
}


int main() {
    Position a; //默认坐标位置为原点
    Position b(4, 5), c(b), d(0, 0), e(1); //b的位置为x轴值4，y轴值5
    cout << "a(0,0):"; a.show();
    a.set(5, 15);
    cout << "a(5,15):"; a.show();
    cout << "b(4,5):"; b.show();
    b.set(-4.5, 6.7);
    cout << "b(-4.5,6.7):"; b.show();
    cout << "c(4,5):"; c.show();
    c.set(-10, -100);
    cout << "c(-10,-100):"; c.show();
    cout << "d(0,0):"; d.show();
    d.set(20.5, 5.5);
    cout << "d(20.5,5.5):"; d.show();
    cout << "e(1,0):"; e.show();
    e.set();//默认为原点
    cout << "e(0,0):"; e.show();
    cout << Distance(a, b) << endl;
    cout << Distance(c) << endl;//默认求与原点的距离
    cout << a.slope() << endl; //与原点构成直线的斜率
    cout << a.slope(d) << endl;  //与d构成直线的斜率
    a.move(3);//沿x轴平移
    cout << "a(8,15):"; a.show();
    b.move(-4, 5);
    cout << "b(-8.5,11.7):"; b.show();
    c.move(0, 6);//沿y轴平移
    cout << "c(-10,-94):"; c.show();
    return 0;
}