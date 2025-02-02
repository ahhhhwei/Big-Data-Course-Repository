#define _CRT_SECURE_NO_WARNINGS 1
#include"Init.h"

int main()
{
	Init init;
	init.draw1();
	if (init.student)
	{
		while (true)
		{
			ExMessage m;
			m = getmessage(EM_MOUSE);
			init.draw5();
			break;
		}
	}
	if (init.administrator)
	{
		while (true)
		{
			ExMessage m;
			m = getmessage(EM_MOUSE);
			init.draw6();
			break;
		}
	}
	return 0;
}