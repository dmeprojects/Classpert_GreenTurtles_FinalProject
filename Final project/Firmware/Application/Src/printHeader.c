/*
 * printHeader.c
 *
 *  Created on: Jan 4, 2024
 *      Author: nick_
 */

#include "main.h"
#include "logging.h"
#include "terminalColorCodes.h"
#include "asciHeader.h"

void printHeader(void)
{
	//Clean screen
	printLog(SERIAL_CLEAR_SCREEN);
	//Set caracters to blue
	printLog(SERIAL_BRIGHT_CYAN_CHARS);

	//Print out header
	printLog(ASCIART_1);
	printLog(ASCIART_2);
	printLog(ASCIART_3);
	printLog(ASCIART_4);
	printLog(ASCIART_5);
	printLog(ASCIART_6);
	printLog(ASCIART_7);

	//Reset to default color

	printLog(SERIAL_DEFAULT_COLORS);
}



