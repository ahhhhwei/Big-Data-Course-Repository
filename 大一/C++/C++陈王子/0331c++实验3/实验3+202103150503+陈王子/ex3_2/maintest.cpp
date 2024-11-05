
//-----------------------maintest.cpp-----------------------
#include<iostream>
#include "clock.hpp"
#include "demo.hpp"
using namespace std;
void fun1(Clock xclock) {
	xclock.reset();
}
Demo fun2(Demo xDemo) {
	xDemo.getclock().reset();
	return xDemo;
}
int main()
{
	Clock  aclock(8, 34, 45), bclock(aclock);
	box  abox, bbox(20, 30);
	Demo ademo(1, 2, 3, 4), bdemo(ademo), cdemo(abox, aclock), ddemo(3, 4);
	Clock* pclock;
	box* pbox;
	Demo* pDemo;
	pclock = new Clock(6, 7, 8);
	pbox = new box(cdemo.getbox());
	pDemo = new Demo[2]{ Demo(6,7,8,9),Demo(bbox,bclock) };
	fun1(*pclock);
	fun2(pDemo[1]);
	delete pclock;
	delete[]pDemo;
	delete pbox;
	return 0;
}
box abox, bbox(20, 30); // 定义 abox 和 bbox 两个对象
Clock aclock(8, 34, 45), bclock(aclock); // 定义 aclock 和 bclock 两个对象
Demo cdemo(abox, aclock); // 用 abox 和 aclock 对象初始化 cdemo 对象，此处调用 Demo 的第二个构造函数