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

#include "mpu6050.h"

struct usbCommunication usbCom;

extern I2C_HandleTypeDef hi2c3;

extern deviceStates_t deviceStates;

void startUp (void)
{
	  initDisplay();
	  displayPutHeader();
	  displayAccelerometerValues(0,0,0);
	  MPU6050_Init(&hi2c3);
}

void mainApp (void)
{
	  ConsoleProcess();

	  switch (deviceStates)
	  {
	  case BOOT:

		  break;

	  case IDLE:

		  break;

	  case INIT_MEASUREMENTS:

		  break;

	  case SAMPLE_DATA:

		  break;

	  case STORE_DATA:

		  break;

	  default:

		  break;
	  }
}
