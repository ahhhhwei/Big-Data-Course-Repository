#pragma once
#include "Widget.h"
#include "Manager.h"
#include <sstream>

// 表格类
class Table :
    public Widget
{
public:
    Table(const Manager& manager, const int& x = 0, const int& y = 0, const int& width = 100, const int& height = 60);
    void show() const;                              // 显示表格
    void pageUp();                                  // 上一页
    void pageDown();                                // 下一页
    void showEditTable(const wchar_t* searchTerms); // 显示编辑表格
    const int& getSearchIndex() const;              // 获取搜索索引

private:
    size_t curIndex;                                // 当前大整数索引
    int searchIndex;                                // 搜索索引
    const Manager& manager;                         // 管理器引用
};
