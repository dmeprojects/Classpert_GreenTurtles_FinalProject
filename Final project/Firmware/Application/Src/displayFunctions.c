/*
 * displayFunctions.c
 *
 *  Created on: Nov 23, 2023
 *      Author: nick_
 */
#include "ssd1306.h"

#define FIRSTLINE	25
#define LINESPACE	12

#define SMALLFONT	Font_7x10

static lCurrentLine = FIRSTLINE;


void initDisplay (void)
{
	  //Init display
	  ssd1306_Init();
	  ssd1306_Fill(Black);
	  ssd1306_UpdateScreen();
}

void displayPutHeader (void)
{
	/*Write title block*/
	  ssd1306_SetCursor(7, 0);
	  ssd1306_WriteString("Aim-A-Lyzer", Font_11x18, 0x01 );
	  ssd1306_Line(0,17,128,17, 0x01);
	  ssd1306_UpdateScreen();
}

void displayAccelerometerValues(int32_t x, int32_t y, int32_t z)
{
	char StringToDisplay[128];
	uint8_t CurrentLine = FIRSTLINE;

	//Write X:
	sprintf(StringToDisplay, "X: %li      ", x);
	ssd1306_SetCursor(0, CurrentLine);
	ssd1306_WriteString(StringToDisplay, SMALLFONT, White);
	CurrentLine += LINESPACE;

	//Write Y:
	sprintf(StringToDisplay, "Y: %li      ", y);
	ssd1306_SetCursor(0, CurrentLine);
	ssd1306_WriteString(StringToDisplay, SMALLFONT, White);
	CurrentLine += LINESPACE;

	//Write Z:
	sprintf(StringToDisplay, "Z: %li      ", z);
	ssd1306_SetCursor(0, CurrentLine);
	ssd1306_WriteString(StringToDisplay, SMALLFONT, White);


	//Update screen
	ssd1306_UpdateScreen();
}

