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

static sdResult_t SdCardPresent(void)
{
	  if (HAL_GPIO_ReadPin(GPIOA, SD_CS_Pin) == 1)
	  {
		  return SD_OK;
	  }
	  else
	  {
		  return GEN_ERROR;

	  }
}

sdResult_t SdCardMount(void)
{
	FRESULT fresult;

	if( SdCardPresent() != 1)
	{
		LogError("No SD card inserted");
		return GEN_ERROR;
	}

	  /*SD card test*/
	  fresult = f_mount(&SDFatFS, (TCHAR const *)SDPath, 0);
	  if(fresult != FR_OK)
	  {
		  LogError("Failed to init SD card with error: %d", fresult);
		  return GEN_ERROR;
	  }
	  else
	  {
		  return SD_OK;
	  }
}

sdResult_t SdCardUnMount(void)
{
	f_mount(&SDFatFS, (TCHAR const *) NULL, 0);

	return SD_OK;
}



sdResult_t CreateFile (char * fileName)
{
	FRESULT fresult;

	if( SdCardPresent() != 1)
	{
		LogError("No SD card inserted");
		return GEN_ERROR;
	}

	fresult = f_open(&SDFile, "STM32_TST_2.txt", FA_CREATE_ALWAYS | FA_WRITE);

	if( fresult!= FR_OK)
	{
		LogError("Failed to create %s with error %i", fileName, fresult);
		return GEN_ERROR;
	}
	else
	{
		return SD_OK;
	}
}

/*
fresult = f_open(&SDFile, "STM32_TST_2.txt", FA_CREATE_ALWAYS | FA_WRITE);

if (fresult != FR_OK)
{
	  LogError("Failed to open file on SD card with error: %d", fresult);
	  Error_Handler();
}
else
{
	  fresult = f_write(&SDFile, wtext, strlen((char*)wtext), (void*)&byteswritten);

	  if (fresult != FR_OK || byteswritten == 0)
	  {
		  LogError("Failed to create file on SD card with error: %d", fresult);
		  Error_Handler();
	  }
	  else
	  {
		  f_close(&SDFile);
	  }
}
*/




