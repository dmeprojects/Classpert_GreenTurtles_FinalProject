/*
 * state_defines.h
 *
 *  Created on: Oct 15, 2023
 *      Author: nick_
 */

#ifndef INC_STATE_DEFINES_H_
#define INC_STATE_DEFINES_H_

typedef enum
{
		BOOT = 0,
		HEADER_SHOW,
		HEADER_IDLE,
		MEASURE_INIT,
		MEASURE_IDLE,
		MEASURE_CREATE_FILE,
		MEASURE_SAMPLE,
		MEASURE_STORE,
		ERROR_SD_NO_CARD,
		ERROR_SD_CREATEFILE
} deviceStates_t;





#endif /* INC_STATE_DEFINES_H_ */
