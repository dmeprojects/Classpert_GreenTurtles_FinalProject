/*
 * state_defines.h
 *
 *  Created on: Oct 15, 2023
 *      Author: nick_
 */

#ifndef INC_STATE_DEFINES_H_
#define INC_STATE_DEFINES_H_

typedef enum deviceStates
{
		BOOT = 0,
		IDLE,
		INIT_MEASUREMENTS,
		SAMPLE_DATA,
		STORE_DATA
};

typedef enum
{
	ROTATE,
	POLICE,
	STROBE,
	MAXFUNCTIONS
}ledState;



#endif /* INC_STATE_DEFINES_H_ */
