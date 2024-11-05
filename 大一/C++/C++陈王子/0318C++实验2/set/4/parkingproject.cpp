#include <iostream>
using namespace std;

//clock.hpp
class Clock {
public:
    void show_time();
    void set_time();
    double diff(Clock& T);
private:
    long normalize();
    int hour;
    int minute;
    int second;
};
//clock.cpp
void Clock::show_time()
{
    cout << hour << ":" << minute << ":"
        << second;
    cout << endl;
}

void Clock::set_time()
{
    do {
        cin >> hour >> minute >> second;
    } while (hour < 0 || hour>24 ||
        minute < 0 || minute>59 ||
        second < 0 || second>59);
}

double Clock::diff(Clock& T)
{
    long d = this->normalize() - T.normalize();
    if (d < 0) return 0;
    int h = d / 60, m = d % 60;
    if (m < 15) return h;
    if (m >= 15 && m < 30) return h + 0.5;
    if (m >= 30 && m < 60) return h + 1;
}

long Clock::normalize()
{
    return (this->hour * 60 + this->minute);
}

//parkingcost.cpp
double parkingFee(double parkingHour) {
    int parkingFeePerHour = 4;
    if (parkingHour <= 1) return 0;
    else if (parkingHour > 1.25 && parkingHour <= 1.5) return 0.5 * parkingFeePerHour;
    else if (parkingHour > 1.5 && parkingHour <= 2) return parkingFeePerHour;
    else if (parkingHour > 2) return (parkingHour) * parkingFeePerHour;
}


int main()
{
    while (1) {
        Clock arriveTime, leaveTime;
        double parkingTime, Fee;
        arriveTime.set_time();
        arriveTime.show_time();
        leaveTime.set_time();
        leaveTime.show_time();
        parkingTime = leaveTime.diff(arriveTime);
        Fee = parkingFee(parkingTime);
        cout << "收费：" << Fee << endl;
    }
}