#include <iostream>
#include <fstream>
#include <random>

int main()
{
    std::default_random_engine rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 100);  // 生成 1 到 100 的随机整数

    const int n = 10;  // 数组长度为 10
    int data1[n], data2[n];

    // 生成第一组数据
    for (int i = 0; i < n; ++i) {
        data1[i] = dist(rng);  // 生成随机数
    }

    // 将第一组数据写入文件 data1.txt
    std::ofstream fout1("data1.txt");
    if (fout1.is_open()) {
        for (int i = 0; i < n; ++i) {
            fout1 << data1[i] << " ";  // 写入数字和空格
        }
        fout1.close();
    }
    else {
        std::cerr << "Failed to open file: data1.txt" << std::endl;
        return 1;
    }

    // 生成第二组数据
    for (int i = 0; i < n; ++i) {
        data2[i] = dist(rng);  // 生成随机数
    }

    // 将第二组数据写入文件 data2.txt
    std::ofstream fout2("data2.txt");
    if (fout2.is_open()) {
        for (int i = 0; i < n; ++i) {
            fout2 << data2[i] << " ";  // 写入数字和空格
        }
        fout2.close();
    }
    else {
        std::cerr << "Failed to open file: data2.txt" << std::endl;
        return 1;
    }

    std::cout << "Data generated and saved successfully." << std::endl;

    return 0;
}
