#pragma once
#include <graphics.h>
#include <conio.h>
class Init
{
public:
	//进入与退出界面
    //进入---draw2()
	void draw1();
	//学生与管理员
    //学生---draw3()
    //管理员---draw4()
	void draw2();
	//学生的学号与密码输入
	void draw3();
	//管理员密码输入
	void draw4();
	//学生选课界面
	void draw5();
	//学生信息浏览---draw7()
	//课程信息浏览---draw8()
	//按学分查询课程---draw9()
	//某课程学生选修情况---draw10()
	//某学生选课情况---draw11()
	//数据整理---draw12()
	void draw6();
	//学生信息浏览
	void draw7();
	//课程信息浏览
	void draw8();
	//按学分查询课程
	void draw9();
	//某课程学生选修情况
	void draw10();
	//某学生选课情况
	void draw11();
	// 数据整理界面:
	// 选课信息按学分排序---draw13()
	// 选课信息按选修人数排序---draw14()
	// 选课信息按课程编号排序---draw15()
	void draw12();
	//选课信息按学分排序
	void draw13();
	//选课信息按选修人数排序
	void draw14();
	//选课信息按课程编号排序
	void draw15();
	//鼠标在某矩形范围内的检测
	bool Check(int, int, int, int, ExMessage*);
	//字体设置函数
	void settextMSG();
	//退出函数
	void drawExit();
	bool student = 0;
	bool administrator = 0;
private:
	//背景
	void drawBackground();
};