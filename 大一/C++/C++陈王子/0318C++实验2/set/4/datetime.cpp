

class DateTime {
public:
    void show_time();
    void set_time();
    int days_in_month(int month, int year);
    bool is_leap_year(int year);
    double diff(DateTime& T);
private:
    long normalize();
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

void DateTime::show_time() {
    cout << year << "-" << month << "-" << day << " " << hour << ":" << minute << ":" << second << endl;
}

void DateTime::set_time() {
    cout << "Enter year: ";
    cin >> year;
    cout << "Enter month: ";
    cin >> month;
    cout << "Enter day: ";
    cin >> day;
    cout << "Enter hour: ";
    cin >> hour;
    cout << "Enter minute: ";
    cin >> minute;
    cout << "Enter second: ";
    cin >> second;
}

double DateTime::diff(DateTime& T) {
    long seconds1 = normalize();
    long seconds2 = T.normalize();
    return (double)abs((seconds2 - seconds1) / (24 * 3600));
}

long DateTime::normalize() {
    // 计算从公元0年0月0日起至当前日期的天数
    long days = 0;
    for (int i = 0; i < year; i++) {
        days += is_leap_year(i) ? 366 : 365;
    }
    for (int i = 1; i < month; i++) {
        days += days_in_month(i, year);
    }
    days += day - 1;

    // 计算总秒数
    long seconds = days * 24 * 3600;
    seconds += hour * 3600;
    seconds += minute * 60;
    seconds += second;
    return seconds;
}

int DateTime::days_in_month(int month, int year) {
    if (month == 2) {
        if (is_leap_year(year)) {
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

bool DateTime::is_leap_year(int year) {
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
        return true;
    }
    else {
        return false;
    }
}




//parkingcost.cpp
double parkingFee(double parkingHour) {
    int parkingFeePerHour = 4;
    int parkingFeePerDay = 30;
    double parkingFee = 0;

    if (parkingHour <= 1) {
        parkingFee = 0;
    }
    else if (parkingHour > 1.25 && parkingHour <= 1.5) {
        parkingFee = 0.5 * parkingFeePerHour;
    }
    else if (parkingHour > 1.5 && parkingHour <= 2) {
        parkingFee = parkingFeePerHour;
    }
    else if (parkingHour > 2 && parkingHour <= 24) {
        parkingFee = parkingHour * parkingFeePerHour;
    }
    else if (parkingHour <= 720) {  // 超过1个月，按30元/天计费，打9折
        parkingFee = (int)parkingHour / 24 * parkingFeePerDay * 0.9;
        if ((int)parkingHour % 24 > 2) {
            parkingFee += parkingFeePerDay * 0.9;
        }
        else if ((int)parkingHour % 24 > 0) {
            parkingFee += parkingFeePerDay * 0.5;
        }
    }
    else if (parkingHour <= 8760) {  // 超过1年，按30元/天计费，打8折
        parkingFee = (int)parkingHour / 24 * parkingFeePerDay * 0.8;
        if ((int)parkingHour % 24 > 2) {
            parkingFee += parkingFeePerDay * 0.8;
        }
        else if ((int)parkingHour % 24 > 0) {
            parkingFee += parkingFeePerDay * 0.5;
        }
    }
    else {  // 超过1年按30元/天计费，打8折
        parkingFee = (int)(parkingHour / 24 / 365 * parkingFeePerDay * 365 * 0.8);
        int days = (int)parkingHour / 24 % 365;
        if (days > 30) {
            parkingFee += parkingFeePerDay * 0.8 * 30;
        }
        else {
            parkingFee += parkingFeePerDay * 0.8 * days;
        }
    }

    return parkingFee;
}
