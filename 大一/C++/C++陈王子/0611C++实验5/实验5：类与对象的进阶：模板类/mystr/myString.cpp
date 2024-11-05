#include <iostream>
#include <cstring>
#include <limits>
using namespace std;

class myString {
public:
    // 默认构造函数
    myString();
    // 带参构造函数：使用 char* s 初始化字符串
    myString(const char* s);
    // 带参构造函数：使用 char* s、开始位置 start 和字符串长度 len 初始化字符串
    myString(const char* s, int start, int len);
    // 带参构造函数：使用字符 c 重复 count 次构造新字符串
    myString(int count, char c);

    // 拷贝构造函数
    myString(const myString& other);

    // 赋值运算符重载
    myString& operator=(const myString& other);

    // 析构函数
    ~myString();

    // 成员函数
    void display() const; // 显示字符串
    void input(); // 输入字符串
    int len() const; // 求字符串长度

    // 运算符重载
    char& operator[](int index); // 下标重载运算
    friend bool operator==(const myString& a, const myString& b); // 字符串等于比较
    friend bool operator>(const myString& a, const myString& b); // 字符串大于比较
    friend myString operator+(const myString& a, const myString& b); // 字符串拼接
    myString& operator+=(const myString& other); // 字符串拼接赋值运算

    // 输入输出流重载
    friend ostream& operator<<(ostream& out, const myString& s);
    friend istream& operator>>(istream& in, myString& s);

private:
    char* str;
    int length;
};

// 默认构造函数实现
myString::myString() {
    str = nullptr;
    length = 0;
}

// 带参构造函数：使用 char* s 初始化字符串
myString::myString(const char* s) {
    length = strlen(s);
    str = new char[length + 1];
    strcpy_s(str, length + 1, s);
}

// 带参构造函数：使用 char* s、开始位置 start 和字符串长度 len 初始化字符串
myString::myString(const char* s, int start, int len) {
    length = len;
    str = new char[length + 1];
    strncpy_s(str, length + 1, s + start, length);
    str[length] = '\0';
}

// 带参构造函数：使用字符 c 重复 count 次构造新字符串
myString::myString(int count, char c) {
    length = count;
    str = new char[length + 1];
    for (int i = 0; i < length; ++i) {
        str[i] = c;
    }
    str[length] = '\0';
}

// 拷贝构造函数实现
myString::myString(const myString& other) {
    length = other.length;
    str = new char[length + 1];
    strcpy_s(str, length + 1, other.str);
}

// 赋值运算符重载实现
myString& myString::operator=(const myString& other) {
    if (this != &other) {
        delete[] str;
        length = other.length;
        str = new char[length + 1];
        strcpy_s(str, length + 1, other.str);
    }
    return *this;
}

// 析构函数实现
myString::~myString() {
    delete[] str;
}

// 成员函数实现
void myString::display() const {
    if (str != nullptr && strlen(str) > 0) {
        cout << str;
    }
    else {
        cout << "empty string";
    }
}


void myString::input() {
    const int MAX_LEN = 1000;
    char buf[MAX_LEN];
    cin.getline(buf, MAX_LEN);
    int new_length = strlen(buf);
    if (str != nullptr && new_length <= length) {
        strcpy_s(str, length + 1, buf);
        length = new_length;
    }
    else {
        delete[] str;
        length = new_length;
        str = new char[length + 1];
        strcpy_s(str, length + 1, buf);
    }
}

int myString::len() const {
    return length;
}

// 运算符重载实现
char& myString::operator[](int index) {
    if (index < 0 || index >= length) {
        cout << "Index error!" << endl;
        exit(-1);
    }
    return str[index];
}

bool operator==(const myString& a, const myString& b) {
    return strcmp(a.str, b.str) == 0;
}

bool operator>(const myString& a, const myString& b) {
    return strcmp(a.str, b.str) > 0;
}

myString operator+(const myString& a, const myString& b) {
    myString res;
    res.length = a.length + b.length;
    res.str = new char[res.length + 1];
    strcpy_s(res.str, res.length + 1, a.str);
    strcat_s(res.str, res.length + 1, b.str);
    return res;
}

myString& myString::operator+=(const myString& other) {
    char* temp = new char[length + 1];
    strcpy_s(temp, length + 1, str);
    delete[] str;
    length += other.length;
    str = new char[length + 1];
    strcpy_s(str, length + 1, temp);
    strcat_s(str, length + 1, other.str);
    delete[] temp;
    return *this;
}

// 输入输出流重载函数实现
ostream& operator<<(ostream& out, const myString& s) {
    out << s.str;
    return out;
}

istream& operator>>(istream& in, myString& s) {
    const int MAX_LEN = 1000;
    char buf[MAX_LEN];
    in.getline(buf, MAX_LEN);
    s.length = strlen(buf);
    delete[] s.str; // 防止内存泄漏
    s.str = new char[s.length + 1];
    strcpy_s(s.str, s.length + 1, buf);
    return in;
}


int main() {
    char str[30] = "Sue likes hot weather.";
    myString a, //空串
        b("I love ZJUT"),  //I love ZJUT
        c(str, 10, 11), //hot weather
        d(3, 'a'), //aaa
        e(b);//I love ZJUT
    cout << "a:"; a.display(); cout << endl;
    cout << "b:"; b.display(); cout << endl;
    cout << "c:"; c.display(); cout << endl;
    cout << "d:"; d.display(); cout << endl;
    cout << "e:"; e.display(); cout << endl;

    if (b == str) cout << "equal";
    else cout << "not equal";
    cout << endl;

    if (b == e) cout << "equal";
    else cout << "not equal";
    cout << endl;

    a = c;
    a.display();
    a[2] = 'x';
    a.display();

    if (d > e) d.display();
    else e.display();

    //输出字符串b的内容
    for (int i = 0; i < b.len(); i++)
        cout << b[i];
    cout << endl;

    b = "Steve is happy today.";
    cout << "b:"; b.display(); cout << endl;

    a.input(); //输入：Kate wasn't hungry.
    a.display();  //输出：Kate wasn't hungry.

    a = e + " and " + c;
    a.display(); //输出： I love ZJUT and hot weather
    cout << endl;

    cin >> d;
    cout << d;
    
    return 0;
}
