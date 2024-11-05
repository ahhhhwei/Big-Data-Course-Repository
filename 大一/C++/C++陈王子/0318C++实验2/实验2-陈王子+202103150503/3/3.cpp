#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>
using namespace std;

// 加法运算
string add(string num1, string num2) {
    int len1 = num1.size(), len2 = num2.size();
    int carry = 0, sum;
    string res;
    while (len1 || len2) {
        int x = len1 ? num1[--len1] - '0' : 0;
        int y = len2 ? num2[--len2] - '0' : 0;
        sum = x + y + carry;
        carry = sum / 10;
        res += (sum % 10) + '0';
    }
    if (carry) res += carry + '0';
    reverse(res.begin(), res.end());
    return res;
}

// 减法运算
string sub(string num1, string num2) {
    int len1 = num1.size(), len2 = num2.size();
    int borrow = 0, diff;
    string res;
    while (len1 || len2) {
        int x = len1 ? num1[--len1] - '0' : 0;
        int y = len2 ? num2[--len2] - '0' : 0;
        diff = x - y - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        }
        else {
            borrow = 0;
        }
        res += diff + '0';
    }
    reverse(res.begin(), res.end());
    while (res.size() > 1 && res[0] == '0') res.erase(0, 1);
    return res;
}

// 乘法运算
string mul(string num1, string num2) {
    int len1 = num1.size(), len2 = num2.size();
    string res(len1 + len2, '0');
    for (int i = len1 - 1; i >= 0; i--) {
        int carry = 0;
        for (int j = len2 - 1; j >= 0; j--) {
            int tmp = (num1[i] - '0') * (num2[j] - '0') + carry + (res[i + j + 1] - '0');
            res[i + j + 1] = tmp % 10 + '0';
            carry = tmp / 10;
        }
        res[i] += carry;
    }
    while (res.size() > 1 && res[0] == '0') res.erase(0, 1);
    return res;
}

// 处理输入的字符串，得到两个数和运算符
void parseInput(string input, string& num1, string& num2, char& op) {
    int pos = input.find(',');
    num1 = input.substr(0, pos);
    input = input.substr(pos + 1);
    pos = input.find(',');
    num2 = input.substr(0, pos);
    op = input[pos + 1];
}

// 生成一个指定位数的随机大数
// 生成指定位数的随机大数
string genRandNum(int numDigits) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 9);
    string randNum;
    randNum.reserve(numDigits);
    for (int i = 0; i < numDigits; i++) {
        randNum += std::to_string(dis(gen));
    }
    return randNum;
}


// 检查输入是否合法
bool isValidInput(const string& input) {
    // 检查输入长度
    if (input.size() < 3) {
        return false;
    }
    // 检查逗号个数
    int commaCount = count(input.begin(), input.end(), ',');
    if (commaCount != 2) {
        return false;
    }
    // 检查运算符合法性
    char op = input[input.size() - 1];
    if (op != '+' && op != '-' && op != '*') {
        return false;
    }
    // 检查数字合法性
    for (int i = 0; i < input.size() - 2; i++) {
        if (!isdigit(input[i]) && input[i] != ',') {
            return false;
        }
    }
    return true;
}

int main() {
    srand(time(NULL)); // 随机数种子
    
    while (cout << "\nPlease enter your equation:" << endl) {
        string input;
        string num1, num2;
        char op = { 0 };
        getline(cin,input); // 从用户输入中解析出两个操作数和运算符
        if (input == "exit") break; // 用户输入exit时退出程序

        if (isValidInput(input)) { // 判断输入是否合法
            parseInput(input, num1, num2, op); // 将用户输入解析为数字和运算符
            if (op == '+') {
                string res = add(num1, num2); // 调用加法函数
                cout << num1 << " + " << num2 << " = " << res << endl;
            }
            else if (op == '-') {
                string res = sub(num1, num2); // 调用减法函数
                cout << num1 << " - " << num2 << " = " << res << endl;
            }
            else if (op == '*') {
                string res = mul(num1, num2); // 调用乘法函数
                cout << num1 << " * " << num2 << " = " << res << endl;
            }
        }
        else {
            cout << "Invalid input. Please try again." << endl;
        }
    }
    
    // 生成随机大数并计算
    int digits = 1000;
    string num1 = genRandNum(digits); 
    string num2 = genRandNum(digits);
    string res = add(num1, num2); // 计算num1 * num2
    cout << "Random number digits:"<< digits <<"\nResult: \n" << num1 << "\n    +    \n" << num2 << "\n   =   \n" << res << endl;
}