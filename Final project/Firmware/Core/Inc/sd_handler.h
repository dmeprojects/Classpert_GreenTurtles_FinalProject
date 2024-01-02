/*
 * sd_handler.h
 *
 *  Created on: Jan 2, 2024
 *      Author: nick_
 */

#ifndef INC_SD_HANDLER_H_
#define INC_SD_HANDLER_H_

#define LIBRARY_LOG_NAME	"SD CARD HANDLER"

typedef enum {
	GEN_ERROR = -1,
	SD_OK
} sdResult_t;

sdResult_t SdCardPresent(void);

sdResult_t SdCardMount(void);
sdResult_t SdCardUnMount(void);

sdResult_t CreateFile (char * fileName);
sdResult_t OpenFile (char * fileName);
sdResult_t WriteToFile (char * data, int32_t dataLen);


sdResult_t FindFolder (char * folderName);






#endif /* INC_SD_HANDLER_H_ */
