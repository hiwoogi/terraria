#pragma once
#include<iostream>
#include<conio.h>
#include "Consola.h"
using namespace std;

class Util
{
public:

	//지정 좌표로 가서 문자출력
	static void xyputc(int x, int y, char ch)
	{
		gotoxy(x, y);
		cout << ch;
	}

	//지정 좌표로 가서 문자열출력
	static void xyputstr(int x, int y, const char str[])
	{
		gotoxy(x, y);
		cout << str;
	}

	//지정 좌표의 배경을 색칠함
	static void fillbox(int x1, int y1, int x2, int y2, char color)
	{
		textbackground(color);
		for (int y = y1; y <= y2; ++y)
			for (int x = x1; x <= x2; ++x)
				xyputc(x, y, ' ');
	}
	
	//키, 특수키 입력 함수
	static int getKey()
	{
		int key = _getch();
		if (key == 0xe0)
			return ((0xe000) | _getch());
		else
			return key;
	}
};