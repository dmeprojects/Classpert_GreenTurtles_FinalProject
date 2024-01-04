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

extern uint32_t buttonPressed;

deviceStates_t deviceState;

void startConsole (void)
{
	logInfo("Init console ...");
	ConsoleInit();
}

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

	switch (deviceState)
	{
	  case BOOT:

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
			logInfo("Init IMU...");
			MPU6050_Init(&hi2c3);
			deviceState = HEADER_SHOW;
			break;


	  case HEADER_SHOW:
		  displayPutHeader();
		  deviceState = HEADER_IDLE;
		  break;

	  case HEADER_IDLE:
		  if(buttonPressed == BTN_OK)
		  {
			  buttonPressed = 0;
			  if (sdCardPresent() != SD_OK)
			  {
				  deviceState = ERROR_SD_NO_CARD;
			  }
			  else
			  {
				  logInfo("Mounting SD card ...");
				  sdCardMount();
				  checkMeasurementsFolder();
				  checkConfigFolder();
				  deviceState = MEASURE_INIT;
			  }
		  }
		  break;

	  case MEASURE_INIT:
		  displayWriteText( 5, 30, "Press OK to start");
		  logInfo("Press button to start sampling");
		  deviceState = MEASURE_IDLE;
		  break;

	  case MEASURE_IDLE:
		  if(buttonPressed == BTN_OK)
		  {
			  buttonPressed = 0;
			  displayClear();
			  displayWriteText( 5, 30, "Sampling...");
			  deviceState = MEASURE_CREATE_FILE;
		  }
		  break;

	  case MEASURE_CREATE_FILE:
		  if( createMeasurementFile() != SD_OK)
		  {
			  logError("Failed to create measurement file");
			  deviceState = ERROR_SD_CREATEFILE;
		  }
		  else
		  {
			  counter = 0;	//Reset sample counter
			  logWarn("Sampling in progress ...");
			  deviceState = MEASURE_SAMPLE;
		  }
		  break;

	  case MEASURE_SAMPLE:
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

		  if(buttonPressed == BTN_OK || buttonPressed == BTN_UP || buttonPressed == BTN_DWN)
		  {
			  buttonPressed = 0;
			  logInfo("Measurement done: %d measurements taken", counter);
			  deviceState = MEASURE_STORE;
		  }
		  break;

	  case MEASURE_STORE:
		  closeMeasurementFile();
		  deviceState = HEADER_SHOW;
		  break;

	  case ERROR_SD_NO_CARD:
		  logError("No SD card found, please insert card first");
		  displayWriteText( 5, 30, "NO SD CARD!");
		  HAL_Delay(2000);
		  deviceState = HEADER_SHOW;
		  break;

	  default:
		  displayWriteText( 5, 30, "ERROR!");
		  HAL_Delay(5000);
		  deviceState = HEADER_SHOW;
		  break;
	 }
}
