#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<time.h>
#pragma comment(lib,"Winmm.lib")
#define accDown 1
#define accUp 6
#define BallX 210

int BallY = 100;
int Vy = 0;
int RectHeight1=10000;
int RectHeight2;
int RectWidth1=10000;
int RectWidth2;
int RectX1 = 1300;
int RectX2;
int RectY1 = 800;
int RectUpY1 = 10000;
int RectY2 = 800;
int RectUpY2;
int RectSpeed1 = 5;
int RectSpeed2 = 10;
int score = 0;
TCHAR s[20];
bool imm = false;
bool add = false;
int i = 0;
int j = 0;
IMAGE player, Sky;
IMAGE GrassUp1, GrassUp2, GrassDown1, GrassDown2;
void BkDraw()
{
	setcolor(BLUE);
	cleardevice();
	loadimage(&Sky, L"sky.jpg", 1200, 600);
	putimage(0, 0, &Sky);
}

void BallMove()
{
	/*fillcircle(BallX, BallY, 10);*/
	setfillcolor(RED);
	if(Vy<15)
		Vy += accDown;
	BallY += Vy;
	if (_kbhit())
	{
		char Space = _getch();
		if (Space == ' ')
		{
			Vy = 0;
			Vy -= accUp;
			BallY += Vy;
		}
	}
	loadimage(&player, L"player.jpg", 30, 30);
	putimage(BallX, BallY, &player);
}
void RectMove()
{
		RectX1 -= RectSpeed2;
		RectX2 -= RectSpeed2;
		RectWidth1 -= RectSpeed2;
		RectWidth2 -= RectSpeed2;
	
}
void RectDraw()
{
	if (BallX == RectX1)
	{
		srand((unsigned)BallY);
		RectHeight2 = rand() % 501 + 100;
		RectWidth2 = rand() % 151+ 1200;
		RectX2 = 1400;
	}
	RectUpY2 = RectHeight2 - 100;
	fillrectangle(RectWidth2, 0, RectX2, RectUpY2);
	fillrectangle(RectWidth2, RectHeight2, RectX2, RectY2);
	if (BallX == RectX2)
	{
		srand((unsigned)BallY);
		RectHeight1 = rand() % 501 + 100;
		RectWidth1 = rand() % 151 + 1200;
		RectX1 = 1400;
	}
	RectUpY1 = RectHeight1 - 100;
	fillrectangle(RectWidth1, 0, RectX1, RectUpY1);
	/*loadimage(&GrassUp1, L"grass.jpg", RectX1 - RectWidth1, RectUpY1);
	putimage(RectWidth1, 0, &GrassUp1);*/
	fillrectangle(RectWidth1, RectHeight1, RectX1, RectY1);
	/*loadimage(&GrassDown1, L"grass.jpg", RectX1 - RectWidth1, RectY1 - RectHeight1);
	putimage(RectWidth1, RectHeight1, &GrassDown1);*/
}
void Score()
{
	if (imm == false)
	{
		if (BallX <= RectX1)
		{
			if (RectX1 == BallX && BallY > RectUpY1 && BallY < RectHeight1)
				score++;
		}
		if (BallX <= RectX2)
		{
			if (RectX2 == BallX && BallY > RectUpY2 && BallY < RectHeight2)
				score++;
		}
		/*if (BallY < 15 || BallY > 785)
		{
			score--;
			imm = true;
			Sleep(1000);
		}*/
		if (BallY + 25 > RectHeight1 && BallX + 17 > RectWidth1 && BallX < RectX1)
		{
			score--;
			imm = true;
			Sleep(1000);
		}

		if (BallY + 25 > RectHeight2 && BallX + 17 > RectWidth2 && BallX < RectX2)
		{
			score--;
			imm = true;
			Sleep(1000);
		}
		if (BallY  < RectUpY1 && BallX + 17  > RectWidth1 && BallX  < RectX1)
		{
			score--;
			imm = true;
			Sleep(1000);
		}
		if (BallY < RectUpY2 && BallX + 17  > RectWidth2 && BallX < RectX2)
		{
			score--;
			imm = true;
			Sleep(1000);
		}
	}
	else
	{
		i++;
		if (i == 25)
		{
			imm = false;
			i = 0;
		}
	}
	/*BeginBatchDraw();*/
	_stprintf(s, _T("%d"), score);
	settextcolor(RGB(43, 209, 93));
	settextstyle(40, 0, _T("黑体"));
	outtextxy(50, 30, s);
	/*EndBatchDraw();*/
}
int main()
{
	//绘制地图大小
	initgraph(1200, 600);
	//绘制第一次墙
	srand((unsigned)time(0));
	RectHeight1 = rand() % 501 + 100;
	RectWidth1 = rand() % 151 + 1200;
	RectX1 = 1400;
	mciSendString(_T("open bkmusic.mp3 alias bkmusic"), NULL, 0, NULL);
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
	while (1)
	{
		BeginBatchDraw();
		//绘制背景颜色
		BkDraw();
		//控制小球移动
		BallMove();
		//墙体的绘制和移动
		RectDraw();
		RectMove();
		//小球的碰撞和判断
		//得分的显示
		Score();
		//延时
		Sleep(30);
		EndBatchDraw();
	}
	closegraph();
	return 0;
}