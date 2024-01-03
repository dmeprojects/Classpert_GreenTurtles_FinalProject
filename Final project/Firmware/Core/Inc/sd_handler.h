/*
 * sd_handler.h
 *
 *  Created on: Jan 2, 2024
 *      Author: nick_
 */

#ifndef INC_SD_HANDLER_H_
#define INC_SD_HANDLER_H_

#define MEASUREMENTS_FOLDER		"MEASUREMENTS"
#define	CONFIG_FOLDER			"CONFIG"
#define	CONFIG_FILE				"SETTINGS.INI"
#define	MEASUREMENT_FILE		"MEASUREMENT_"	//Add number after the _ character
#define	MEASUREMENT_FILETYPE	".TXT"



typedef enum {
	GEN_ERROR = -1,
	SD_OK
} sdResult_t;

typedef struct {
	uint8_t fileNumber;
	uint32_t numberOfLinesRead;
	uint32_t numberOfLinesWritten;
} MEASUREMENTFILE;

sdResult_t sdCardPresent(void);

sdResult_t sdCardMount(void);
sdResult_t sdCardUnMount(void);

sdResult_t createFile (char * fileName);
sdResult_t openFile (char * fileName);
sdResult_t writeToFile (char * data, int32_t dataLen);
sdResult_t openFile ( char * fileName);
sdResult_t checkFile (char * fileName);


sdResult_t findFolder (char * folderName);

sdResult_t checkMeasurementsFolder (void);
sdResult_t checkConfigFolder (void);

sdResult_t createMeasurementFile(void);




#endif /* INC_SD_HANDLER_H_ */
