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
	uint32_t tick;
	MPU6050_t imuData;
	char logString[150] = {0};
	static uint32_t counter = 0;
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

		  //Check file system if there is a map "measurements"
		  checkMeasurementsFolder();

		  checkConfigFolder();


		  displayWriteText( 5, 30, "Press button to start");
		  deviceStates = IDLE;

		  break;

	  case UPDATE_DISPLAY:
		  displayWriteText( 5, 30, "Press button to start");

		  logInfo("Press button to start sampling");
		  deviceStates = IDLE;

		  break;

	  case IDLE:

		  //Wait for buttonpres
		  if(buttonPressed == 1)
		  {
			  buttonPressed = 0;
			  displayClear();
			  displayPutHeader();
			  displayAccelerometerValues(0, 0, 0);
			  tick = HAL_GetTick();
			  logInfo("Tick: %d", tick);
			  deviceStates = INIT_MEASUREMENTS;
		  }

		  break;

	  case INIT_MEASUREMENTS:

		  //create file
		  if( createMeasurementFile() != SD_OK)
		  {
			  logError("Failed to create measurement file");
			  deviceStates = UPDATE_DISPLAY;
		  }

		  counter = 0;

		  logWarn("Sampling in progress ...");

		  deviceStates = SAMPLE_DATA;

		  break;

	  case SAMPLE_DATA:

		  //Get Timesatamp

		  //MPU6050_Read_All(&hi2c3, &imuData);
		  MPU6050_RAW_Read(&hi2c3, &imuData);

		  tick = HAL_GetTick();
		  sprintf(logString, "%lu|%lu|%d;%d;%d|%d;%d;%d|%f\n",
				  counter++,
				  tick,
				  imuData.Accel_X_RAW,
				  imuData.Accel_Y_RAW,
				  imuData.Accel_Z_RAW,
				  imuData.Gyro_X_RAW,
				  imuData.Gyro_Y_RAW,
				  imuData.Gyro_Z_RAW,
				  imuData.Temperature);

		  addNewMeasurement(logString);

		  if(buttonPressed == 1)
		  {
			  buttonPressed = 0;
			  logInfo("Measurement done: %d measurements taken", counter);
			  deviceStates = STORE_DATA;
		  }

		  break;

	  case STORE_DATA:

		  closeMeasurementFile();

		  deviceStates = UPDATE_DISPLAY;

		  break;

	  default:

		  break;
	  }
}
