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
#define WHO_AM_I_2						0x0f

#define	CTRL_REG1						0x20	//0000 0111 default

#define CTRL_REG1_NORMMODE				7u	//Normal mode enabled, default 0.  power down: 0, enable 1
#define CTRL_REG1_IFADDINC				6u	//Register address auto increment during multiple byte access, default 1.  0: disabled, 1: enabled
#define CTRL_REG1_BOOT					3u	// Reboot memory content, default 0.  0: disabled, 1 enabled
#define CTRL_REG1_SWRESET				2u	//Software reset, default 0.  0: normal mode, 1: reset device
#define CTRL_REG1_DRDYPULSE				1u	//Data ready on int 1 pin.  default 0.  0: DRDY latched, 1 DRDY pulsed (duration 1/4 ODR)
#define CTRL_REG1_BDU					0u	//Block data update, default 0.  0: continous update, 1: output registers not updated until MSB and LSB read


#define	INT1_CTRL						0x21

#define INT2_CTRL						0x22

#define	CTRL_REG4						0x23

#define CTRL_REG5						0x24

#define	OUT_TEMP_L						0x25

#define	OUT_TEMP_H						0x26

#define	STATUS_REG						0x27

#define STATUS_ZYXOR					7u
#define STATUS_ZOR						6u
#define STATUS_YOR						5u
#define STATUS_XOR						4u
#define STATUS_ZYXDA					3u
#define STATUS_ZDA						2u
#define STATUS_YDA						1u
#define STATUS_XDA						0u

#define OUT_X							0x28	//Read as 16 bit word in 2s complement

#define	OUT_Y							0x2a	//Read as 16 bit word in 2s complement

#define OUT_Z							0x2c	//Read as 16 bit word in 2s complement

#define FIFO_CTRL						0x2e

#define FIFO_FMODE2						7u
#define FIFO_FMODE1						6u
#define FIFO_FMODE0						5u
#define FIFO_FTH4						4u
#define FIFO_FTH3						3u
#define FIFO_FTH2						2u
#define FIFO_FTH1						1u
#define FIFO_FTH0						0u

#define FIFO_SRC						0x2f

#define FIFO_FTH						7u
#define FIFO_OVRN						6u
#define FIFO_FSS5						5u
#define FIFO_FSS4						4u
#define FIFO_FSS3						3u
#define FIFO_FSS2						2u
#define FIFO_FSS1						1u
#define FIFO_FSS0						0u

void resetImu (void);
void EnableImu(void);

void AccellerationX (void);
void AccellerationY (void);
void AccellerationZ (void);

#endif /* INC_ACCELEROMETER_H_ */
