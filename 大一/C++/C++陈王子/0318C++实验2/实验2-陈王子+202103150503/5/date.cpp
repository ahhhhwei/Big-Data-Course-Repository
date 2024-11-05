#include <iostream>
using namespace std;

class Date {
public:
    void show_date();
    void set_date();
    int days_in_month();
    void add_day();
    double diff(Date& T);
private:
    int year;
    int month;
    int day;
};

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

void Date::show_date() {
    cout << year << "-" << month << "-" << day << endl;
}

void Date::set_date() {
    cout << "Enter year: ";
    cin >> year;
    cout << "Enter month: ";
    cin >> month;
    cout << "Enter day: ";
    cin >> day;
}

int Date::days_in_month() {
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            return 29;
        }
        else {
            return 28;
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    else {
        return 31;
    }
}

void Date::add_day() {
    day++;
    if (day > days_in_month()) {
        day = 1;
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
}

double Date::diff(Date& T) {
    int days1 = 0;
    for (int i = 1; i < month; i++) {
        Date d = { year, i, 1 };
        days1 += d.days_in_month();
    }
    days1 += day - 1;
    int days2 = 0;
    for (int i = 1; i < T.month; i++) {
        Date d = { T.year, i, 1 };
        days2 += d.days_in_month();
    }
    days2 += T.day - 1;
    int days = 0;
    if (year == T.year) {
        days = days2 - days1;
    }
    else {
        for (int i = year; i < T.year; i++) {
            Date d = { i, 1, 1 };
            days += d.days_in_month();
        }
        days -= days1;
        days += days2;
    }
    return (double)days;
}

void Clock::show_time() {
    cout << hour << ":" << minute << ":" << second << endl;
}

void Clock::set_time() {
    cout << "Enter hour: ";
    cin >> hour;
    cout << "Enter minute: ";
    cin >> minute;
    cout << "Enter second: ";
    cin >> second;
}

double Clock::diff(Clock& T) {
    long seconds1 = normalize();
    long seconds2 = T.normalize();
    return (double)(seconds2 - seconds1) / (24 * 3600);
}

long Clock::normalize() {
    long seconds = hour * 3600;
    seconds += minute * 60;
    seconds += second;
    return seconds;
}

double parkingFee(Date& d1, Clock& t1, Date& d2, Clock& t2) {
    int parkingFeePerHour = 4;
    int parkingFeePerDay = 30;
    double parkingFee = 0;

    double parkingTime = d1.diff(d2) + t1.diff(t2) / 3600.0;

    if (parkingTime <= 1) {
        parkingFee = 0;
    }
    else if (parkingTime <= 1.25) {
        parkingFee = 0.5 * parkingFeePerHour;
    }
    else if (parkingTime <= 2) {
        parkingFee = parkingFeePerHour;
    }
    else if (parkingTime <= 24) {
        parkingFee = parkingTime * parkingFeePerHour;
    }
    else if (parkingTime <= 720) {  // 超过1个月，按30元/天计费，打9折
        parkingFee = d1.diff(d2) * parkingFeePerDay * 0.9;
        d1.add_day();
        while (d1.diff(d2) > 0) {
            parkingFee += parkingFeePerDay * 0.9;
            d1.add_day();
        }
        if (t2.diff(t1) / 3600.0 > 2) {
            parkingFee += parkingFeePerDay * 0.9;
        }
        else if (t2.diff(t1) / 3600.0 > 0) {
            parkingFee += parkingFeePerDay * 0.5;
        }
    }
    else if (parkingTime <= 8760) {  // 超过1年，按30元/天计费，打8折
        parkingFee = d1.diff(d2) * parkingFeePerDay * 0.8;
        d1.add_day();
        while (d1.diff(d2) > 0) {
            parkingFee += parkingFeePerDay * 0.8;
            d1.add_day();
        }
        if (t2.diff(t1) / 3600.0 > 2) {
            parkingFee += parkingFeePerDay * 0.8;
        }
        else if (t2.diff(t1) / 3600.0 > 0) {
            parkingFee += parkingFeePerDay * 0.5;
        }
    }
    else {  // 超过1年按30元/天计费，打8折
        parkingFee = d1.diff(d2) * parkingFeePerDay * 365 * 0.8;
        d1.set_date();
        while (d1.diff(d2) > 0) {
            if (d1.diff(d2) < 30) {
                parkingFee += d1.diff(d2) * parkingFeePerDay * 0.8;
                break;
            }
            else {
                parkingFee += parkingFeePerDay * 0.8 * 30;
                d1.add_day();
            }
        }
        if (t2.diff(t1) / 3600.0 > 2) {
            parkingFee += parkingFeePerDay * 0.8;
        }
        else if (t2.diff(t1) / 3600.0 > 0) {
            parkingFee += parkingFeePerDay * 0.5;
        }
    }

    return parkingFee;
}