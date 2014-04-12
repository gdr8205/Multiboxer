#ifndef CONFIGS_H_
#define CONFIGS_H_

#include "stdafx.h"



using namespace std;

int read();

int renameWindows(int configdInstancesNumber, int redo);
void getWindowInfo(int winNumber);
void actionMaker(string info);
int convertStringToAction(string info);
void addBorders(HWND, int, int);

struct WOWS {
	wstring title;
	HWND hWnd;
	int width;
	int height;
	int xpos;
	int ypos;
	RECT oldRect;
};

struct CONFIG {
	wstring defaultGameWindowTitle;
	string hotkey[1000];
	int keys[1000][3];
	int actions[1000][2];
	int screen[1000];
	int totalHotkeys = 0;
	int keysPressed[3];
	int windowCounter;
	int defaultWidth = 0;
	int defaultHeight = 0;

	int currentWindowMaxed = -1;
	bool borders = true;

};

extern struct WOWS windows[];
extern struct CONFIG configs;
#endif