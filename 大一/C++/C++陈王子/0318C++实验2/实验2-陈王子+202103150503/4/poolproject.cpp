//pool.hpp
#include <iostream>
using namespace std;
class pool {
public:
    void build();
    double rail_length();
    double rail_area();
private:
    double radius;
    double c;
};
//pool.cpp
#define pi 3.14
//#include "pool.hpp"
void pool::build()
{
    cin >> radius >> c;
}
double pool::rail_area()
{
    return pi * ((radius + c) * (radius + c)- radius * radius);
}
double pool::rail_length()
{
    return 2 * pi * radius;
}
//pooltest.cpp
int main()
{
    const double zddj = 167.5;//走道单价
    const double wldj = 36.4;//围栏单价
    double r;//池直径
    double c;//走道宽
    pool apool;
    for (int I = 1; I <= 5; I++)
    {
        cout << "建造第"<< I << "号泳池:";
        apool.build();
        cout << "第"<< I << "号泳池造价为"
            << (apool.rail_length() * wldj + apool.rail_area() * zddj) << "元" << endl;
    }
}
