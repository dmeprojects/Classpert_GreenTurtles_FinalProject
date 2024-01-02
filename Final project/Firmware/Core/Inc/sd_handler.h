/*
 * sd_handler.h
 *
 *  Created on: Jan 2, 2024
 *      Author: nick_
 */

#ifndef INC_SD_HANDLER_H_
#define INC_SD_HANDLER_H_



typedef enum {
	GEN_ERROR = -1,
	SD_OK
} sdResult_t;

sdResult_t sdCardPresent(void);

sdResult_t sdCardMount(void);
sdResult_t sdCardUnMount(void);

sdResult_t createFile (char * fileName);
sdResult_t openFile (char * fileName);
sdResult_t writeToFile (char * data, int32_t dataLen);
sdResult_t openFile ( char * fileName);
sdResult_t checkFile (char * fileName);


sdResult_t findFolder (char * folderName);






#endif /* INC_SD_HANDLER_H_ */
