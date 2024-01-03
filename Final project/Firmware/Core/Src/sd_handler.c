/*
 * sd_handler.c
 *
 *  Created on: Jan 2, 2024
 *      Author: nick_
 */

#include "main.h"
#include "fatfs.h"
#include "string.h"

#include "logging.h"

#include "sd_handler.h"

#define LIBRARY_LOG_NAME	"SD CARD HANDLER"

extern uint8_t SdCardpresent;

FATFS fs;
FIL fil;
//FRESULT fresult;
char SdBuffer[1024];

UINT br, bw;

//capacity related variables
FATFS *pfs;
DWORD free_clust;
uint32_t total, free_space;

sdResult_t sdResult;

sdResult_t sdCardPresent(void)
{
	  if (HAL_GPIO_ReadPin(SD_DETECT_GPIO_Port, SD_DETECT_Pin) == 1)
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

/*
fresult = f_open(&SDFile, "STM32_TST_2.txt", FA_CREATE_ALWAYS | FA_WRITE);

if (fresult != FR_OK)
{
	  logError("Failed to open file on SD card with error: %d", fresult);
	  Error_Handler();
}
else
{
	  fresult = f_write(&SDFile, wtext, strlen((char*)wtext), (void*)&byteswritten);

	  if (fresult != FR_OK || byteswritten == 0)
	  {
		  logError("Failed to create file on SD card with error: %d", fresult);
		  Error_Handler();
	  }
	  else
	  {
		  f_close(&SDFile);
	  }
}
*/

sdResult_t checkDefaultMaps (void)
{
	//Check for map measurements
	FRESULT fResult;
	FILINFO fInfo;
	DIR dir;

	//find folder
	fResult = f_stat(MEASUREMENTS_FOLDER, &fInfo);

	switch (fResult)
	{
	case FR_OK:
		logInfo("Folder found");
		break;
	case FR_NO_PATH:
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
	fResult = f_findfirst(&dir, &fInfo, "0:/MEASUREMENTS/", "MEASUREMENT_???.TXT");

	while (fResult == FR_OK && fInfo.fname[0])
	{
		logInfo("%s", fInfo.fname);
		fResult = f_findnext(&dir, &fInfo);
	}
//	fResult = f_chdir("/" + MEASUREMENTS_FOLDER);
//	if (fResult != FR_OK)
//	{
//		logError("Failed to switch directory with error %d", fResult);
//		return GEN_ERROR;
//	}



}




