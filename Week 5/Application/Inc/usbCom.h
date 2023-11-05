/*
 * usbCom.h
 *
 *  Created on: Nov 1, 2023
 *      Author: nick_
 */

#ifndef INC_USBCOM_H_
#define INC_USBCOM_H_

struct usbCommunication
{
	uint8_t comBuffer[100];
	uint8_t comReady;
	uint8_t * dataBuffer;
	uint32_t bufferLength;
};

extern struct usbCommunication usbCom;


#endif /* INC_USBCOM_H_ */
