/*
 * accelerometer.h
 *
 *  Created on: Nov 5, 2023
 *      Author: nick_
 */

#ifndef INC_ACCELEROMETER_H_
#define INC_ACCELEROMETER_H_

// Datasheet: https://www.st.com/resource/en/datasheet/lis3dhh.pdf


/*Registers*/
#define WHO_AM_I			0x0f
#define	CTRL_REG1			0x20	//0000 0111 default
#define CTRL_REG1_DR					7u
#define CTRL_REG1_PD					6u
#define CTRL_REG1_FS					5u
#define CTRL_REG1_STP					4u
#define CTRL_REG1_STM					3u
#define CTRL_REG1_ZEN					2u
#define CTRL_REG1_YEN					1u
#define CTRL_REG1_XEN					0u


#define	CTRL_REG2			0x21
#define	CTRL_REG3			0x22
#define	HP_FILTER_RESET		0x23
#define	STATUS_REG			0x27
#define OUT_X				0x29
#define OUT_Y				0x2B
#define OUT_Z				0x2D

#define FF_WU_CFG_1			0x30
#define	FF_WU_SRC_1			0x31
#define	FF_WU_THS_1			0x32
#define	FF_WU_DURATION_1	0x33
#define	FF_WU_CFG_2			0x34
#define	FF_WU_CFG_3			0x35
#define	FF_WU_THS_2			0x36
#define	FF_WU_DURATION_2	0x37
#define	CLICK_CFG			0x38
#define	CLICK_SRC			0x39
#define	CLICK_THSY_X		0x3b
#define	CLICK_THSZ			0x3c
#define	CLICK_TIMELIMIT		0x3d
#define	CLICK_LATENCY		0x3e
#define	CLICK_WINDOW		0x3f



void EnableImu(void);

void AccellerationX (void);
void AccellerationY (void);
void AccellerationZ (void);

#endif /* INC_ACCELEROMETER_H_ */
