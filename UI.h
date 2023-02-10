#ifndef UI_H
#define UI_H
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <fstream>
#include <windows.h>
#include <ctype.h>
#include <iomanip>
#include <cwchar>

// UI Class is used as a class for User Interface that contains multiple functions to provide interactive console

class UI
{
	public:
		
void CurPosition(int, int);

void loadAnimation();

void FontColor(int);

void curDateAndTime();

void TextSize(int, int);

void Box();

int MainMenu();

void AboutUs();
};

#endif

