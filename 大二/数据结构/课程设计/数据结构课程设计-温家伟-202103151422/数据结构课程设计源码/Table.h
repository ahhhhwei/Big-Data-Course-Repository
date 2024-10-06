#pragma once
#include "Widget.h"
#include "Manager.h"
#include <sstream>

// �����
class Table :
    public Widget
{
public:
    Table(const Manager& manager, const int& x = 0, const int& y = 0, const int& width = 100, const int& height = 60);
    void show() const;                              // ��ʾ���
    void pageUp();                                  // ��һҳ
    void pageDown();                                // ��һҳ
    void showEditTable(const wchar_t* searchTerms); // ��ʾ�༭���
    const int& getSearchIndex() const;              // ��ȡ��������

private:
    size_t curIndex;                                // ��ǰ����������
    int searchIndex;                                // ��������
    const Manager& manager;                         // ����������
};
