#pragma once
#include <graphics.h>
#include <conio.h>
class Init
{
public:
	//�������˳�����
    //����---draw2()
	void draw1();
	//ѧ�������Ա
    //ѧ��---draw3()
    //����Ա---draw4()
	void draw2();
	//ѧ����ѧ������������
	void draw3();
	//����Ա��������
	void draw4();
	//ѧ��ѡ�ν���
	void draw5();
	//ѧ����Ϣ���---draw7()
	//�γ���Ϣ���---draw8()
	//��ѧ�ֲ�ѯ�γ�---draw9()
	//ĳ�γ�ѧ��ѡ�����---draw10()
	//ĳѧ��ѡ�����---draw11()
	//��������---draw12()
	void draw6();
	//ѧ����Ϣ���
	void draw7();
	//�γ���Ϣ���
	void draw8();
	//��ѧ�ֲ�ѯ�γ�
	void draw9();
	//ĳ�γ�ѧ��ѡ�����
	void draw10();
	//ĳѧ��ѡ�����
	void draw11();
	// �����������:
	// ѡ����Ϣ��ѧ������---draw13()
	// ѡ����Ϣ��ѡ����������---draw14()
	// ѡ����Ϣ���γ̱������---draw15()
	void draw12();
	//ѡ����Ϣ��ѧ������
	void draw13();
	//ѡ����Ϣ��ѡ����������
	void draw14();
	//ѡ����Ϣ���γ̱������
	void draw15();
	//�����ĳ���η�Χ�ڵļ��
	bool Check(int, int, int, int, ExMessage*);
	//�������ú���
	void settextMSG();
	//�˳�����
	void drawExit();
	bool student = 0;
	bool administrator = 0;
private:
	//����
	void drawBackground();
};