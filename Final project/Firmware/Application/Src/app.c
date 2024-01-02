/*
 * app.c
 *
 *  Created on: Oct 26, 2023
 *      Author: nick_
 */

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

#define LIBRARY_LOG_NAME	"APPLICATION"

struct usbCommunication usbCom;

extern I2C_HandleTypeDef hi2c3;

extern deviceStates_t deviceStates;

extern uint8_t buttonPressed;

void startUp (void)
{
	logInfo("Init Display...");
	initDisplay();
	displayPutHeader();

	logInfo("Init console ...");
	ConsoleInit();

	logInfo ("Checking SD card ...");
	if( sdCardPresent() != SD_OK)
	{
	  logWarn("SD card not inserted");
	}
	else
	{
	  logInfo("Mounting SD card ...");
	  sdCardMount();
	}
	logInfo("Init IMU...");
	MPU6050_Init(&hi2c3);
}

void mainApp (void)
{
	sdResult_t result;
	  ConsoleProcess();

	  switch (deviceStates)
	  {
	  case BOOT:
		  //Nothing implemented

		  /*
		   * TO DO:
		   *
		   * Create a function that finds the correct files with the number of measurements.
		   * Remember the latest number +1.  This we need to create a new measurements file
		   *
		   * This must be a function that returns a true or false.
		   *
		   *
		   * */

		  result = checkFile("NumberOfMeasurements.txt");
		  if( result == SD_OK)
		  {
			  //Read file
		  }
		  else
		  {
			  //create file
			  createFile( "NumberOfMeasurements.txt");
			  //write a 0 to the file

		  }
		  displayWriteText( 5, 30, "Press a button to start");
		  deviceStates = IDLE;

		  break;

	  case IDLE:

		  //Wait for buttonpres
		  if(buttonPressed == 1)
		  {
			  buttonPressed =0;
			  displayClear();
			  displayPutHeader();
			  displayAccelerometerValues(0, 0, 0);
			  deviceStates = INIT_MEASUREMENTS;
		  }

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
