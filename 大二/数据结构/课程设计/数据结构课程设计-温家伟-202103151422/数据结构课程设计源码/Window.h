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
    // ����״̬��ʶ��ÿ��״̬������һ������
    enum WindowState { mainWindow, viewBigums, edit };
    #define BACKGROUND_IMAGE L"background.jpg"                   // ����ͼƬ���ĳ���
    Window(const int& width = 600, const int& height = 400);
    void show() const;                                           // ��ʾ����
    void messageLoop();                                          // ��Ϣѭ��
    void close();                                                // �رմ���
    void showMainWindow();                                       // ��ʾ������
    void showViewBignums();                                      // ��ʾ�鿴����������
    Bignum<List<int>> wstring2Bignum(wstring str);               // wstringת������

private:
    // �����ڰ�ť
    Button* mainWindow_leftnum;           // �������
    Button* mainWindow_rightnum;          // �Ҳ�����
    Button* mainWindow_sign;              // ������
    Button* mainWindow_exit;              // �˳�����
    Button* mainWindow_RWfile;            // ��д�ļ�

    // �鿴���������ڰ�ť
    Button* RWfile_back;                  // ����
    Button* RWfile_pageUp;                // ��һҳ
    Button* RWfile_pageDown;              // ��һҳ

    WindowState state;                    // ����״̬
    Table* table;                         // �����ݱ��
    Manager _manager;                     // ������
    Bignum<List<int>> _left;              // �������
    Bignum<List<int>> _right;             // �Ҳ�����
    Bignum<List<int>> _ret;               // ���
    int _base = 0;                        // ����
    // C++11�������ԣ�֧��������ʱ��ȱʡֵ
};