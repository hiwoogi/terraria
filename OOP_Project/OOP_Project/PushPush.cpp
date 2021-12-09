#include<iostream>
#include<stdlib.h>
using namespace std;
#include "keycode.h"
#include "Util.h"
#define MAP_X1 10 //맵의 x좌표
#define MAP_Y1 4 // 맵의 y좌표
#define MAP_WIDTH 10 // 맵 너비
#define MAP_HEIGHT 10 // 맵 길이

// 1번 맵
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

// 기호 (0 = 공백, 1 = 벽, 2 = 공, 4 = 도착점)
const char* cellSymbol[] = { "  ", "▒▒","●",NULL,"@@",NULL };

// 맵의 특정 좌표를 그리는함수
void drawCell(int col, int row) {
	int cell = mapData[row][col];
	textbackground((cell == 1) ? DARKGRAY : YELLOW);
	gotoxy((MAP_X1 + col + 1) * 2, MAP_Y1 + row + 1);
	puts(cellSymbol[cell]);
} 

// 맵 전체를 그리는 함수
void drawMap()
{
	for (int row = 0; row < MAP_HEIGHT; ++row)
		for (int col = 0; col < MAP_WIDTH; ++col)
			drawCell(col, row);
} 
// 플레이어를 그리는 함수
void drawCharcter(int x, int y)
{
	textcolor(RED);
	Util::xyputstr((MAP_X1 + 1 + x) * 2, MAP_Y1 + 1 + y, "★");
}

// 첫 화면을 나타내는 함수
void mainScreen()
{
	int key;
	_setcursortype(_NOCURSOR);
	Util::fillbox(18, 4, 62, 9, WHITE);
	Util::fillbox(20, 5, 60, 8, BLACK);
	Util::xyputstr(35, 6, "PUSH PUSH");

	Util::fillbox(18, 8, 62, 16, WHITE);
	Util::fillbox(20, 9, 60, 15, BLACK);
	Util::xyputstr(28, 11, "1. 게임 시작 (ENTER or 1입력)");
	Util::xyputstr(28, 13, "2. 게임 종료 ");

	while (1)
	{
		key = Util::getKey();
		if (key == '1' || key == ENTER) // 엔터나 1번을 누르는 경우 다음 화면으로 이동
		{
			clrscr();
			break;
		}
		else if (key == '2') // 2번을 누르는 경우 프로그램 종료
		{
			exit(0);
		}

	}
}
int main()
{
	int posX = 5, posY = 5; // 플레이어의 최초 좌표
	int oldX, oldY; 
	int nPosX, nPosY; // 플레이어가 갈 경로의 좌표

	mainScreen();
	_setcursortype(_NOCURSOR);
	drawMap();
	drawCharcter(posX, posY);
	while (1)
	{
		int key = Util::getKey();
		if (key == 'q') break; // 'q' 입력시 프로그램 종료.
		oldX = nPosX = posX;
		oldY = nPosY = posY;


		switch (key)
		{
		case M_LEFTKEY: // ← 키 입력
			if (posX > 0)
				nPosX--;
			break;
		case M_UPKEY: // ↑키 입력
			if (posY > 0)
				nPosY--;
			break;
		case M_DOWNKEY: // ↓키 입력
			if (posY < MAP_HEIGHT - 1)
				nPosY++; 
			break;
		case M_RIGHTKEY://  → 키 입력
			if (posX < MAP_WIDTH - 1)
				nPosX++; 
			break;
		}

		if (mapData[nPosY][nPosX] == 0 || mapData[nPosY][nPosX] == 4) // 가는 경로가 공백이거나 도착점인 경우
		{
			posX = nPosX; // 플레이어의 x, y좌표 수정
			posY = nPosY;
		}

		if (mapData[nPosY][nPosX] == 2) // 진행경로에 공이 있는경우
		{
			if (nPosX < oldX && mapData[nPosY][nPosX - 1] == 4) // 좌측이동 경로에 도착점이 있는경우
			{
				mapData[nPosY][nPosX - 1] = 2; // 공의 경로 수정
				mapData[nPosY][nPosX] = 0; // 공이 지나왔던 경로를 공백으로 수정
				drawCell(nPosX - 1, nPosY);
				posX = nPosX; //플레이어 위치 수정
				posY = nPosY;
				Util::xyputstr(28, 11, "게임을 클리하셨습니다!");
			}

			else if (nPosX < oldX && mapData[nPosY][nPosX - 1] != 1) // 좌측이동 경로에 벽이없는 경우
			{
				mapData[nPosY][nPosX - 1] = 2; // 공의 경로 수정
				mapData[nPosY][nPosX] = 0; // 공이 지나왔던 경로를 공백으로 수정
				drawCell(nPosX - 1, nPosY);
				posX = nPosX; //플레이어 위치 수정
				posY = nPosY;
			}
			if (nPosX > oldX && mapData[nPosY][nPosX + 1] == 4) //우측이동 경로에 도착점이 있는경우
			{
				mapData[nPosY][nPosX + 1] = 2;
				mapData[nPosY][nPosX] = 0;
				drawCell(nPosX + 1, nPosY);
				posX = nPosX;
				posY = nPosY;
				Util::xyputstr(28, 11, "게임을 클리하셨습니다!");
			}
			else if (nPosX > oldX && mapData[nPosY][nPosX + 1] != 1) //우측이동 경로에 벽이없는 경우
			{
				mapData[nPosY][nPosX + 1] = 2;
				mapData[nPosY][nPosX] = 0;
				drawCell(nPosX + 1, nPosY);
				posX = nPosX;
				posY = nPosY;

			}
			if (nPosY < oldY && mapData[nPosY - 1][nPosX] == 4) // 위로이동하는 도착점이 있는경우
			{
				mapData[nPosY - 1][nPosX] = 2;
				mapData[nPosY][nPosX] = 0;
				drawCell(nPosX, nPosY - 1);
				posX = nPosX;
				posY = nPosY;
				Util::xyputstr(28, 11, "게임을 클리하셨습니다!");
			}

			else if (nPosY < oldY && mapData[nPosY - 1][nPosX] != 1) // 위로이동하는 경로에 벽이없는 경우
			{
				mapData[nPosY - 1][nPosX] = 2;
				mapData[nPosY][nPosX] = 0;
				drawCell(nPosX, nPosY - 1);
				posX = nPosX;
				posY = nPosY;
			}
			if (nPosY > oldY && mapData[nPosY + 1][nPosX] == 4) // 아래로 이동하는 경로에 도착점이 있는경우
			{
				mapData[nPosY + 1][nPosX] = 2;
				mapData[nPosY][nPosX] = 0;
				drawCell(nPosX, nPosY + 1);
				posX = nPosX;
				posY = nPosY;
				Util::xyputstr(28, 11, "게임을 클리하셨습니다!");
			}
			else if (nPosY > oldY && mapData[nPosY + 1][nPosX] != 1) // 아래로 이동하는 경로에 벽이없는 경우
			{
				mapData[nPosY + 1][nPosX] = 2;
				mapData[nPosY][nPosX] = 0;
				drawCell(nPosX, nPosY + 1);
				posX = nPosX;
				posY = nPosY;
			}
		}

		//플레이어의 위치가 바뀐경우
		if (oldX != posX || oldY != posY)
		{
			drawCell(posX, posY); // 바뀐 셀을 수정해준다.
			drawCell(oldX, oldY);
		}
		drawCharcter(posX, posY); 


	}

	return 0;
}