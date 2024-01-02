/*
 * logging.c
 *
 *  Created on: Jan 2, 2024
 *      Author: nick_
 */

#include "main.h"

#include "string.h"
#include "stdarg.h"

#include "logging.h"

void printLog ( const char * pc, ...)
{
	va_list va;
	va_start(va, pc);

	vprintf(pc, va);

	va_end(va);
}


