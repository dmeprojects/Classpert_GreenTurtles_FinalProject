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

#include "logging.h"

#include "sd_handler.h"

struct usbCommunication usbCom;

extern I2C_HandleTypeDef hi2c3;

extern deviceStates_t deviceStates;

void startUp (void)
{
	LogInfo("Init Display...");
	  initDisplay();
	  displayPutHeader();

	  LogInfo("Init console ...");
	  ConsoleInit();

	  LogInfo ("Checking SD card ...");
	  if( SdCardPresent() != SD_OK)
	  {
		  LogWarn("SD card not inserted");
	  }
	  else
	  {
		  LogInfo("Mounting SD card ...");
		  SdCardMount();
	  }
	  LogInfo("Init IMU...");
	  MPU6050_Init(&hi2c3);
}

void mainApp (void)
{
	  ConsoleProcess();

	  switch (deviceStates)
	  {
	  case BOOT:
		  //Nothing implemented
		  deviceStates = IDLE;

		  break;

	  case IDLE:

		  break;

	  case INIT_MEASUREMENTS:

		  ///displayAccelerometerValues(0,0,0);

		  break;

	  case SAMPLE_DATA:

		  break;

	  case STORE_DATA:

		  break;

	  default:

		  break;
	  }
}
