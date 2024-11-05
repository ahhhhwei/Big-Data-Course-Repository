#include <iostream>
#include <fstream>
#include <algorithm>

int main()
{
    const int n = 20;  // 数组长度为 20
    int a[n] = {0};    // 初始化数组为 0

    // 读取第一组数据
    std::ifstream fin1("data1.txt");
    if (fin1.is_open()) {
        for (int i = 0; i < 10; ++i) {
            fin1 >> a[i];  // 读取数字并赋值给数组元素
        }
        fin1.close();
    }
    else {
        std::cerr << "Failed to open file: data1.txt" << std::endl;
        return 1;
    }

    // 读取第二组数据
    std::ifstream fin2("data2.txt");
    if (fin2.is_open()) {
        for (int i = 10; i < 20; ++i) {
            fin2 >> a[i];  // 读取数字并赋值给数组元素
        }
        fin2.close();
    }
    else {
        std::cerr << "Failed to open file: data2.txt" << std::endl;
        return 1;
    }

    // 对数组进行排序
    std::sort(a, a + n);

    // 输出数组到屏幕
    for (int i = 0; i < n; ++i) {
        std::cout << a[i] << " ";  // 输出数字和空格
    }
    std::cout << std::endl;

    // 将数组写入文件 data3.txt
    std::ofstream fout("data3.txt");
    if (fout.is_open()) {
        for (int i = 0; i < n; ++i) {
            fout << a[i] << " ";  // 写入数字和空格
        }
        fout.close();
    }
    else {
        std::cerr << "Failed to open file: data3.txt" << std::endl;
        return 1;
    }

    std::cout << "Data processed and saved successfully." << std::endl;

    return 0;
}
