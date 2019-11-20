﻿#pragma once

#include"pch.h"

bool debugMode = false;//==false时会进行蛇/苹果的坐标显示在console上

bool clockBlink = false;
bool * pclockBlink = &clockBlink;

//bool clockBlink2 = false;
//bool * pclockBlink2 = &clockBlink2;

char userInput = 0;
char * puserInput = &userInput;

int fileInput = 0;
int *pfileInput = &fileInput;


#include"COM.h"
#include"FileReading.h"
#include"Snake.h"

#include<conio.h>
#include<time.h>

#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<thread>

using namespace std;

/*
void askUser()
{
	while (true)
	{
		if (_kbhit())
		{
			*puserInput = _getch();
		}
	}
}
*/
//替代为使用FileReading.h输入数据

void snakeWork()//---------------蛇的工作----------------
{
	CubeKit ck;
	Snake snake(4, ck , pclockBlink,puserInput);

	ck.Check();
	//cout << "begin" << endl;
	int count = 0;
	while (true)
	{
		if (snake.IsEatingSelf())
		{
			cout << "******************************************" << endl;
			cout << " *           You're eating yourself       *" << endl;
			cout << "******************************************" << endl;
		}

		snake.ExDestnation(snake.AskIfEx());
		if (*pclockBlink)
		{
			snake.MoveAndRend();
		}
	}
}



void mClock()//---------------时间----------------
{
	clock_t start, finish;
	double duration;
	start = clock();
	while (true)
	{
		finish = clock();
		duration = (finish - start);
		if (duration >= 2000)
		{
			*pclockBlink = true;
			//cout << *pclockBlink << endl;
			//发送响应,在Move执行后关闭该响应
			start = clock();
		}
	}
}

/*
void mClock2()//---------------时间2----------------
{
	clock_t start, finish;
	double duration;
	start = clock();
	while (true)
	{
		finish = clock();
		duration = (finish - start);
		if (duration >= 200)
		{
			*pclockBlink2 = true;
			start = clock();
		}
	}
}
*/

int main()
{
	thread ts(snakeWork);
	ts.detach();
	thread tc(mClock);
	tc.detach();
	
	/*
	thread tc2(mClock2);
	tc2.detach();
	*/

	while (true);
	return 0;
}