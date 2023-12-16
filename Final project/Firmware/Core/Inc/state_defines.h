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
		IDLE,
		INIT_MEASUREMENTS,
		SAMPLE_DATA,
		STORE_DATA
} deviceStates;





#endif /* INC_STATE_DEFINES_H_ */
