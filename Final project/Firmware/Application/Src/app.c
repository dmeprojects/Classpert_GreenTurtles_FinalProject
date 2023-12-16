/*
 * app.c
 *
 *  Created on: Oct 26, 2023
 *      Author: nick_
 */
#define TEXT	"Test 123 ABC \r\n"

#include "app.h"
#include "main.h"

#include "usb_device.h"

#include "custom_pindefines.h"
#include "state_defines.h"

#include "usbCom.h"
#include "console.h"
#include "displayFunctions.h"

struct usbCommunication usbCom;

void startUp (void)
{
	  initDisplay();
	  displayPutHeader();
	  displayAccelerometerValues(0,0,0);
}

void mainApp (void)
{
	  ConsoleProcess();
}
