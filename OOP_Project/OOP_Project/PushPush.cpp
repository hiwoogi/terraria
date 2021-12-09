#include<iostream>
#include<stdlib.h>
using namespace std;
#include "keycode.h"
#include "Util.h"
#define MAP_X1 10 //���� x��ǥ
#define MAP_Y1 4 // ���� y��ǥ
#define MAP_WIDTH 10 // �� �ʺ�
#define MAP_HEIGHT 10 // �� ����

// 1�� ��
int mapData[MAP_HEIGHT][MAP_WIDTH] = { 
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,0,0,0,0,1},
	{1,4,0,0,1,0,0,0,0,1},
	{1,1,0,0,0,0,1,0,0,1},
	{1,0,0,1,1,0,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,1},
	{1,0,1,0,1,0,0,2,0,1},
	{1,0,0,0,0,0,1,1,0,1},
	{1,1,1,1,1,1,1,1,1,1}
}; 

// ��ȣ (0 = ����, 1 = ��, 2 = ��, 4 = ������)
const char* cellSymbol[] = { "  ", "�Ƣ�","��",NULL,"@@",NULL };

// ���� Ư�� ��ǥ�� �׸����Լ�
void drawCell(int col, int row) {
	int cell = mapData[row][col];
	textbackground((cell == 1) ? DARKGRAY : YELLOW);
	gotoxy((MAP_X1 + col + 1) * 2, MAP_Y1 + row + 1);
	puts(cellSymbol[cell]);
} 

// �� ��ü�� �׸��� �Լ�
void drawMap()
{
	for (int row = 0; row < MAP_HEIGHT; ++row)
		for (int col = 0; col < MAP_WIDTH; ++col)
			drawCell(col, row);
} 
// �÷��̾ �׸��� �Լ�
void drawCharcter(int x, int y)
{
	textcolor(RED);
	Util::xyputstr((MAP_X1 + 1 + x) * 2, MAP_Y1 + 1 + y, "��");
}

// ù ȭ���� ��Ÿ���� �Լ�
void mainScreen()
{
	int key;
	_setcursortype(_NOCURSOR);
	Util::fillbox(18, 4, 62, 9, WHITE);
	Util::fillbox(20, 5, 60, 8, BLACK);
	Util::xyputstr(35, 6, "PUSH PUSH");

	Util::fillbox(18, 8, 62, 16, WHITE);
	Util::fillbox(20, 9, 60, 15, BLACK);
	Util::xyputstr(28, 11, "1. ���� ���� (ENTER or 1�Է�)");
	Util::xyputstr(28, 13, "2. ���� ���� ");

	while (1)
	{
		key = Util::getKey();
		if (key == '1' || key == ENTER) // ���ͳ� 1���� ������ ��� ���� ȭ������ �̵�
		{
			clrscr();
			break;
		}
		else if (key == '2') // 2���� ������ ��� ���α׷� ����
		{
			exit(0);
		}

	}
}
int main()
{
	int posX = 5, posY = 5; // �÷��̾��� ���� ��ǥ
	int oldX, oldY; 
	int nPosX, nPosY; // �÷��̾ �� ����� ��ǥ

	mainScreen();
	_setcursortype(_NOCURSOR);
	drawMap();
	drawCharcter(posX, posY);
	while (1)
	{
		int key = Util::getKey();
		if (key == 'q') break; // 'q' �Է½� ���α׷� ����.
		oldX = nPosX = posX;
		oldY = nPosY = posY;


		switch (key)
		{
		case M_LEFTKEY: // �� Ű �Է�
			if (posX > 0)
				nPosX--;
			break;
		case M_UPKEY: // ��Ű �Է�
			if (posY > 0)
				nPosY--;
			break;
		case M_DOWNKEY: // ��Ű �Է�
			if (posY < MAP_HEIGHT - 1)
				nPosY++; 
			break;
		case M_RIGHTKEY://  �� Ű �Է�
			if (posX < MAP_WIDTH - 1)
				nPosX++; 
			break;
		}

		if (mapData[nPosY][nPosX] == 0 || mapData[nPosY][nPosX] == 4) // ���� ��ΰ� �����̰ų� �������� ���
		{
			posX = nPosX; // �÷��̾��� x, y��ǥ ����
			posY = nPosY;
		}

		if (mapData[nPosY][nPosX] == 2) // �����ο� ���� �ִ°��
		{
			if (nPosX < oldX && mapData[nPosY][nPosX - 1] == 4) // �����̵� ��ο� �������� �ִ°��
			{
				mapData[nPosY][nPosX - 1] = 2; // ���� ��� ����
				mapData[nPosY][nPosX] = 0; // ���� �����Դ� ��θ� �������� ����
				drawCell(nPosX - 1, nPosY);
				posX = nPosX; //�÷��̾� ��ġ ����
				posY = nPosY;
				Util::xyputstr(28, 11, "������ Ŭ���ϼ̽��ϴ�!");
			}

			else if (nPosX < oldX && mapData[nPosY][nPosX - 1] != 1) // �����̵� ��ο� ���̾��� ���
			{
				mapData[nPosY][nPosX - 1] = 2; // ���� ��� ����
				mapData[nPosY][nPosX] = 0; // ���� �����Դ� ��θ� �������� ����
				drawCell(nPosX - 1, nPosY);
				posX = nPosX; //�÷��̾� ��ġ ����
				posY = nPosY;
			}
			if (nPosX > oldX && mapData[nPosY][nPosX + 1] == 4) //�����̵� ��ο� �������� �ִ°��
			{
				mapData[nPosY][nPosX + 1] = 2;
				mapData[nPosY][nPosX] = 0;
				drawCell(nPosX + 1, nPosY);
				posX = nPosX;
				posY = nPosY;
				Util::xyputstr(28, 11, "������ Ŭ���ϼ̽��ϴ�!");
			}
			else if (nPosX > oldX && mapData[nPosY][nPosX + 1] != 1) //�����̵� ��ο� ���̾��� ���
			{
				mapData[nPosY][nPosX + 1] = 2;
				mapData[nPosY][nPosX] = 0;
				drawCell(nPosX + 1, nPosY);
				posX = nPosX;
				posY = nPosY;

			}
			if (nPosY < oldY && mapData[nPosY - 1][nPosX] == 4) // �����̵��ϴ� �������� �ִ°��
			{
				mapData[nPosY - 1][nPosX] = 2;
				mapData[nPosY][nPosX] = 0;
				drawCell(nPosX, nPosY - 1);
				posX = nPosX;
				posY = nPosY;
				Util::xyputstr(28, 11, "������ Ŭ���ϼ̽��ϴ�!");
			}

			else if (nPosY < oldY && mapData[nPosY - 1][nPosX] != 1) // �����̵��ϴ� ��ο� ���̾��� ���
			{
				mapData[nPosY - 1][nPosX] = 2;
				mapData[nPosY][nPosX] = 0;
				drawCell(nPosX, nPosY - 1);
				posX = nPosX;
				posY = nPosY;
			}
			if (nPosY > oldY && mapData[nPosY + 1][nPosX] == 4) // �Ʒ��� �̵��ϴ� ��ο� �������� �ִ°��
			{
				mapData[nPosY + 1][nPosX] = 2;
				mapData[nPosY][nPosX] = 0;
				drawCell(nPosX, nPosY + 1);
				posX = nPosX;
				posY = nPosY;
				Util::xyputstr(28, 11, "������ Ŭ���ϼ̽��ϴ�!");
			}
			else if (nPosY > oldY && mapData[nPosY + 1][nPosX] != 1) // �Ʒ��� �̵��ϴ� ��ο� ���̾��� ���
			{
				mapData[nPosY + 1][nPosX] = 2;
				mapData[nPosY][nPosX] = 0;
				drawCell(nPosX, nPosY + 1);
				posX = nPosX;
				posY = nPosY;
			}
		}

		//�÷��̾��� ��ġ�� �ٲ���
		if (oldX != posX || oldY != posY)
		{
			drawCell(posX, posY); // �ٲ� ���� �������ش�.
			drawCell(oldX, oldY);
		}
		drawCharcter(posX, posY); 


	}

	return 0;
}