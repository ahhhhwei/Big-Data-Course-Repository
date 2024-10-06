#pragma once
#include "Table.h"
#include "Widget.h"
#include "Button.h"
#include "Manager.h"
#include <Windows.h>
#include <time.h>
#include "List.hpp"

class Window :public Widget
{
public:
    // 窗口状态标识，每个状态代表了一个界面
    enum WindowState { mainWindow, viewBigums, edit };
    #define BACKGROUND_IMAGE L"background.jpg"                   // 背景图片名的常量
    Window(const int& width = 600, const int& height = 400);
    void show() const;                                           // 显示窗口
    void messageLoop();                                          // 消息循环
    void close();                                                // 关闭窗口
    void showMainWindow();                                       // 显示主窗口
    void showViewBignums();                                      // 显示查看大整数窗口
    Bignum<List<int>> wstring2Bignum(wstring str);               // wstring转大整数

private:
    // 主窗口按钮
    Button* mainWindow_leftnum;           // 左操作数
    Button* mainWindow_rightnum;          // 右操作数
    Button* mainWindow_sign;              // 操作符
    Button* mainWindow_exit;              // 退出程序
    Button* mainWindow_RWfile;            // 读写文件

    // 查看大整数窗口按钮
    Button* RWfile_back;                  // 返回
    Button* RWfile_pageUp;                // 上一页
    Button* RWfile_pageDown;              // 下一页

    WindowState state;                    // 窗口状态
    Table* table;                         // 大数据表格
    Manager _manager;                     // 管理器
    Bignum<List<int>> _left;              // 左操作数
    Bignum<List<int>> _right;             // 右操作数
    Bignum<List<int>> _ret;               // 结果
    int _base = 0;                        // 进制
    // C++11的新特性，支持在声明时给缺省值
};