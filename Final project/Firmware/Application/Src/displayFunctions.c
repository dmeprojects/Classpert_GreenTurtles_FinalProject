/*
 * displayFunctions.c
 *
 *  Created on: Nov 23, 2023
 *      Author: nick_
 */

#define FIRSTLINE	25
#define LINESPACE	12

#define SMALLFONT	Font_7x10

static lCurrentLine = FIRSTLINE;




void displayPutHeader (void)
{
	/*Write title block*/
	  ssd1306_SetCursor(7, 0);
	  ssd1306_WriteString("Aim-A-Lyzer", Font_11x18, 0x01 );
	  ssd1306_Line(0,17,128,17, 0x01);
	  ssd1306_UpdateScreen();
}

void DisplayAccelerometerValues(int32_t x, int32_t y, int32_t z)
{
	char xString[6];
	char yString[6];
	char zString[6];

	char StringToDisplay[128];

	uint8_t CurrentLine = FIRSTLINE;

	//Write X:
	sprintf(StringToDisplay, "X: %i", x);
	ssd1306_SetCursor(0, CurrentLine);
	ssd1306_WriteString(StringToDisplay, SMALLFONT, White);
	CurrentLine += LINESPACE;

	//Write Y:
	sprintf(StringToDisplay, "Y: %i", y);
	ssd1306_SetCursor(0, CurrentLine);
	ssd1306_WriteString(StringToDisplay, SMALLFONT, White);
	CurrentLine += LINESPACE;

	//Write Z:
	sprintf(StringToDisplay, "Y: %i", z);
	ssd1306_SetCursor(0, CurrentLine);
	ssd1306_WriteString(StringToDisplay, SMALLFONT, White);
	CurrentLine += LINESPACE;


}

