#pragma once
#include<iostream>
#include<conio.h>
#include "Consola.h"
using namespace std;

class Util
{
public:

	//���� ��ǥ�� ���� �������
	static void xyputc(int x, int y, char ch)
	{
		gotoxy(x, y);
		cout << ch;
	}

	//���� ��ǥ�� ���� ���ڿ����
	static void xyputstr(int x, int y, const char str[])
	{
		gotoxy(x, y);
		cout << str;
	}

	//���� ��ǥ�� ����� ��ĥ��
	static void fillbox(int x1, int y1, int x2, int y2, char color)
	{
		textbackground(color);
		for (int y = y1; y <= y2; ++y)
			for (int x = x1; x <= x2; ++x)
				xyputc(x, y, ' ');
	}
	
	//Ű, Ư��Ű �Է� �Լ�
	static int getKey()
	{
		int key = _getch();
		if (key == 0xe0)
			return ((0xe000) | _getch());
		else
			return key;
	}
};