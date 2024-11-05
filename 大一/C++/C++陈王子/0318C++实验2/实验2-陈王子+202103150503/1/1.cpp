#include <iostream>
#include <cstring>
using namespace std;

bool mystrncpy(char* to, char* from, unsigned startpos, unsigned len) {
    if (startpos >= strlen(from)) {
        cerr << "pos error" << endl;//位置错误
        return false;
    }
    if (len <= 0) {
        cerr << "len error" << endl;//长度错误
        return false;
    }
    if (startpos + len > strlen(from)) {
        cerr << "out of range error" << endl;//过界错误
        return false;
    }
    //拷贝函数
    for (unsigned i = startpos; i < startpos + len; i++) {
        to[i - startpos] = from[i];
    }
    to[len] = '\0';
    return true;
}

int main()
{
    char from[] = "abcdefghijklmn";
    char* to=new char;

    if (mystrncpy(to, from, 0, 0)) {
        cout << "copied string:" << to << "\n" << endl;
    }
    else {
        cout << "copy failed\n" << endl;
    }
    
    if (mystrncpy(to, from, 3, 4)) {
        cout << "copied string:" << to <<"\n" << endl;
    }
    else {
        cout << "copy failed\n" << endl;
    }
    
    if (mystrncpy(to, from, 3, 20)) {
        cout << "copied string:" << to << "\n" << endl;
    }
    else {
        cout << "copy failed\n" << endl;
    } 
}