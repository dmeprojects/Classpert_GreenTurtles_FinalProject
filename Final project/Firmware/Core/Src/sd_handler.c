/*
 * sd_handler.c
 *
 *  Created on: Jan 2, 2024
 *      Author: nick_
 */

#include "main.h"
#include "fatfs.h"
#include "string.h"
#include "stdio.h"

#include "logging.h"

#include "sd_handler.h"

#define LIBRARY_LOG_NAME	"SD CARD HANDLER"

extern uint8_t SdCardpresent;

FATFS fs;
FIL gFile;
char SdBuffer[1024];
UINT br, bw;

//capacity related variables
FATFS *pfs;
DWORD free_clust;
uint32_t total, free_space;

sdResult_t sdResult;

MEASUREMENTFILE measurementFile;

sdResult_t sdCardPresent(void)
{
	  if (HAL_GPIO_ReadPin(SD_DET_GPIO_Port, SD_DET_Pin) == 0)
	  {
		  return SD_OK;
	  }
	  else
	  {
		  return GEN_ERROR;

	  }
}

sdResult_t sdCardMount(void)
{
	FRESULT fresult;

	if( sdCardPresent() == 1)
	{
		logError("No SD card inserted");
		return GEN_ERROR;
	}

	  /*SD card test*/
	  fresult = f_mount(&SDFatFS, (TCHAR const *)SDPath, 0);
	  if(fresult != FR_OK)
	  {
		  logError("Failed to init SD card with error: %d", fresult);
		  return GEN_ERROR;
	  }
	  else
	  {
		  return SD_OK;
	  }
}

sdResult_t sdCardUnMount(void)
{
	f_mount(&SDFatFS, (TCHAR const *) NULL, 0);

	return SD_OK;
}

sdResult_t createFile (char * fileName)
{
	FRESULT fresult;

	if( sdCardPresent() == 1)
	{
		logError("No SD card inserted");
		return GEN_ERROR;
	}

	fresult = f_open(&SDFile, fileName, FA_CREATE_ALWAYS | FA_WRITE);

	if( fresult!= FR_OK)
	{
		logError("Failed to create %s with error %i", fileName, fresult);
		return GEN_ERROR;
	}
	else
	{
		f_close(&SDFile);
		return SD_OK;
	}
}

sdResult_t openFile ( char * fileName)
{
	return -1;
}

sdResult_t checkFile (char * fileName)
{
	FRESULT fResult;
	FILINFO fInfo;

	fResult = f_stat(fileName, &fInfo);

	switch (fResult)
	{
	case FR_OK:

		logInfo("File found, filezize: %lu ", fInfo.fsize);
		return SD_OK;

		break;

	case FR_NO_FILE:
		logError("File not found");
		return GEN_ERROR;
		break;

	case FR_NO_PATH:
		logError("Directory not existing");
		return GEN_ERROR;
		break;

	default:
		logError("Error in checkFile function: %d", fResult);
		break;
	}

	return GEN_ERROR;
}

sdResult_t checkMeasurementsFolder (void)
{
	//Check for map measurements
	FRESULT fResult;
	FILINFO fInfo;
	DIR dir;

	uint8_t fileCounter = 0;

	//Reset number of files
	measurementFile.fileNumber = 0;

	//find folder
	fResult = f_stat(MEASUREMENTS_FOLDER, &fInfo);

	switch (fResult)
	{
	case FR_OK:
		logInfo("%s Folder found", MEASUREMENTS_FOLDER);
		break;
	case FR_NO_PATH:
	case FR_NO_FILE:
		logInfo("No measurements folder found, creatign one");
		fResult = f_mkdir(MEASUREMENTS_FOLDER);
		if(fResult != FR_OK)
		{
			logError("Failed to create measurements folder with error: %d", fResult);
			return GEN_ERROR;
		}
		break;
	default:
		logError("An error occured: %d", fResult);
		return GEN_ERROR;
		break;
	}

	//So folder exists, check the number of measurements files it contains
	fResult = f_findfirst(&dir, &fInfo, "0:/MEASUREMENTS", "MEASUREMENT_???.TXT");

	while (fResult == FR_OK && fInfo.fname[0])
	{
		logInfo("0:/%s/%s", MEASUREMENTS_FOLDER, fInfo.fname);

		if(fileCounter < 50)
		{
			sprintf(measurementFile.filesInFolder[fileCounter], fInfo.fname);
			fileCounter++;
		}
		else
		{
			logWarn("More than 50 files found");
		}

		fResult = f_findnext(&dir, &fInfo);
		measurementFile.fileNumber++;
	}

	logInfo("Number of measurement files found: %d", measurementFile.fileNumber);	//Increment with one after printout, to set value correct for next measurement

	f_close(&fInfo);

	return SD_OK;
}

sdResult_t checkConfigFolder (void)
{
	//Check for map measurements
	FRESULT fResult;
	FILINFO fInfo;
	DIR dir;

	//find folder
	fResult = f_stat(CONFIG_FOLDER, &fInfo);

	switch (fResult)
	{
	case FR_OK:
		logInfo("%s Folder found", CONFIG_FOLDER);
		break;
	case FR_NO_FILE:
	case FR_NO_PATH:
		logInfo("No config folder found, creating one");
		fResult = f_mkdir(CONFIG_FOLDER);
		if(fResult != FR_OK)
		{
			logError("Failed to create config folder with error: %d", fResult);
			return GEN_ERROR;
		}
		break;
	default:
		logError("An error occured: %d", fResult);
		return GEN_ERROR;
		break;
	}

	//So folder exists, check the number of measurements files it contains
	fResult = f_findfirst(&dir, &fInfo, "0:/CONFIG", "CONF.TXT");

	while (fResult == FR_OK && fInfo.fname[0])
	{
		logInfo("0:/%s/%s", MEASUREMENTS_FOLDER, fInfo.fname);
		fResult = f_findnext(&dir, &fInfo);
	}

	f_close(&fInfo);
	return SD_OK;
}

sdResult_t createMeasurementFile(void)
{
	FRESULT fResult;
	char lFileName[50];
	char lPathName[100];

	if( ++measurementFile.fileNumber < 10)
	{
		sprintf(lFileName, "MEASUREMENT_00%d.txt", measurementFile.fileNumber);
	}

	if( measurementFile.fileNumber >= 10 && measurementFile.fileNumber < 100)
	{
		sprintf(lFileName, "MEASUREMENT_0%d.txt", measurementFile.fileNumber);
	}

	if( measurementFile.fileNumber >= 100)
	{
		sprintf(lFileName, "MEASUREMENT_%d.txt", measurementFile.fileNumber);
	}

	if( measurementFile.fileNumber >= 1000)
	{
		logError("Max number of files reached!");
		return GEN_ERROR;
	}

	measurementFile.savedFileNameLength = sprintf(measurementFile.savedFileName, lFileName);

	sprintf(lPathName, "0:/MEASUREMENTS/%s", lFileName );

	logInfo("Creating file: %s", lPathName);

	fResult = f_open(&gFile, lPathName, FA_CREATE_ALWAYS | FA_WRITE);

	if (fResult != FR_OK)
	{
		logError("Failed to create measurement file with error: %d", fResult);

		return GEN_ERROR;
	}

	return SD_OK;
}

sdResult_t addNewMeasurement(char * string)
{
	FRESULT fResult;
	UINT bytesWritten, bytesToWrite;

	bytesToWrite = strlen(string);

	//logInfo("Adding to file: %s, with length: %d", string, bytesToWrite);

	fResult = f_write(&gFile, string, bytesToWrite, &bytesWritten);

	if(fResult != FR_OK)
	{
		logError("Failed to write to file with error: %d",fResult);
		f_close(&gFile);
		return GEN_ERROR;
	}

	return SD_OK;
}


void closeMeasurementFile(void)
{
	f_close(&gFile);
}

uint32_t returnNumberOfFiles (void)
{
	return measurementFile.fileNumber;
}

sdResult_t returnFileName( char * pFileName, uint32_t maxFileNameLength)
{
	int16_t savedFileNameLength;

	savedFileNameLength = strlen(measurementFile.savedFileName);

	if( savedFileNameLength > maxFileNameLength)
	{
		logError("Filenamebuffer is to small");
		return GEN_ERROR;
	}
	else
	{
		strcpy(pFileName, measurementFile.savedFileName);
		return SD_OK;
	}
}

sdResult_t listFiles(void)
{
	if (measurementFile.fileNumber == 0)
	{
		logError("No files found");
		return GEN_ERROR;
	}

	return SD_OK;

}







