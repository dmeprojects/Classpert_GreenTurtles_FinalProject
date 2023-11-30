/*
 * displayFunctions.c
 *
 *  Created on: Nov 23, 2023
 *      Author: nick_
 */
#include "ssd1306.h"
#include "stdio.h"

#define FIRSTLINE	25
#define LINESPACE	12
#define SECONDCOLUMN	60

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
	uint8_t currentLine = FIRSTLINE;

	//Write X:
	sprintf(StringToDisplay, "aX:%li     ", x);
	ssd1306_SetCursor(0, currentLine);
	ssd1306_WriteString(StringToDisplay, SMALLFONT, White);
	currentLine += LINESPACE;

	//Write Y:
	sprintf(StringToDisplay, "aY:%li    ", y);
	ssd1306_SetCursor(0, currentLine);
	ssd1306_WriteString(StringToDisplay, SMALLFONT, White);
	currentLine += LINESPACE;

	//Write Z:
	sprintf(StringToDisplay, "aZ:%li     ", z);
	ssd1306_SetCursor(0, currentLine);
	ssd1306_WriteString(StringToDisplay, SMALLFONT, White);


	//Update screen
	ssd1306_UpdateScreen();
}

void displayGyroValues (int32_t gX, int32_t gY, int32_t gZ)
{
	char StringToDisplay[128];
	uint8_t currentLine = FIRSTLINE;

	//Write X:
	sprintf(StringToDisplay, "gX:%li      ", gX);
	ssd1306_SetCursor(SECONDCOLUMN, currentLine);
	ssd1306_WriteString(StringToDisplay, SMALLFONT, White);
	currentLine += LINESPACE;

	//Write Y:
	sprintf(StringToDisplay, "gY:%li      ", gY);
	ssd1306_SetCursor(SECONDCOLUMN, currentLine);
	ssd1306_WriteString(StringToDisplay, SMALLFONT, White);
	currentLine += LINESPACE;

	//Write Z:
	sprintf(StringToDisplay, "gZ:%li      ", gZ);
	ssd1306_SetCursor(SECONDCOLUMN, currentLine);
	ssd1306_WriteString(StringToDisplay, SMALLFONT, White);

	//Update screen
	ssd1306_UpdateScreen();
}

void displayRawValues (int32_t aX, int32_t gX, int32_t aY, int32_t gY, int32_t aZ, int32_t gZ)
{
	char StringToDisplay[128];
	uint8_t currentLine = FIRSTLINE;

	//Write X:
	sprintf(StringToDisplay, "aX:%li     ", aX);
	ssd1306_SetCursor(0, currentLine);
	ssd1306_WriteString(StringToDisplay, SMALLFONT, White);

	//Write X:
	sprintf(StringToDisplay, "gX:%li      ", gX);
	ssd1306_SetCursor(SECONDCOLUMN, currentLine);
	ssd1306_WriteString(StringToDisplay, SMALLFONT, White);

	currentLine += LINESPACE;

	//Write Y:
	sprintf(StringToDisplay, "aY:%li    ", aY);
	ssd1306_SetCursor(0, currentLine);
	ssd1306_WriteString(StringToDisplay, SMALLFONT, White);

	//Write Y:
	sprintf(StringToDisplay, "gY:%li      ", gY);
	ssd1306_SetCursor(SECONDCOLUMN, currentLine);
	ssd1306_WriteString(StringToDisplay, SMALLFONT, White);

	currentLine += LINESPACE;

	//Write Z:
	sprintf(StringToDisplay, "aZ:%li     ", aZ);
	ssd1306_SetCursor(0, currentLine);
	ssd1306_WriteString(StringToDisplay, SMALLFONT, White);

	//Write Z:
	sprintf(StringToDisplay, "gZ:%li      ", gZ);
	ssd1306_SetCursor(SECONDCOLUMN, currentLine);
	ssd1306_WriteString(StringToDisplay, SMALLFONT, White);

	//Update screen
	ssd1306_UpdateScreen();

}

