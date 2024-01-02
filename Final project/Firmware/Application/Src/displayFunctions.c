/*
 * displayFunctions.c
 *
 *  Created on: Nov 23, 2023
 *      Author: nick_
 */
#include "ssd1306.h"
#include "string.h"
#include "stdio.h"

#include "logging.h"

#define LIBRARY_LOG_NAME	"DISPLAY"

#define DISPLAYSIZE_X 	128
#define DISPLAYSIZE_Y	64

#define FIRSTLINE	25
#define LINESPACE	12
#define SECONDCOLUMN	60

#define SMALLFONT	Font_7x10

//static lCurrentLine = FIRSTLINE;


void initDisplay (void)
{
	  //Init display
	  ssd1306_Init();
	  ssd1306_Fill(Black);
	  ssd1306_UpdateScreen();
}

void displayClear (void)
{
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

int16_t displayWriteText( uint8_t xPos, uint8_t yPos, char * textToWrite)
{

	if (strlen(textToWrite) > DISPLAYSIZE_X)
	{
		LogError("Text to long, text may not exeeding %d chars", DISPLAYSIZE_X);
		return -1;
	}

	if(xPos > DISPLAYSIZE_X || yPos > DISPLAYSIZE_Y)
	{
		LogError("Cursor position out of display range");
		return -1;
	}

	ssd1306_SetCursor(xPos, yPos);
	ssd1306_WriteString(textToWrite, SMALLFONT, White);

	ssd1306_UpdateScreen();

	return 1;
}

