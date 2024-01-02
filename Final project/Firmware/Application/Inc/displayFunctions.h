/*
 * displayFunctions.h
 *
 *  Created on: Nov 23, 2023
 *      Author: nick_
 */

#ifndef INC_DISPLAYFUNCTIONS_H_
#define INC_DISPLAYFUNCTIONS_H_

void initDisplay(void);
void displayClear (void);
void displayPutHeader (void);

void displayAccelerometerValues(int32_t x, int32_t y, int32_t z);
void displayGyroValues (int32_t gX, int32_t Gy, int32_t gZ);
void displayRawValues (int32_t aX, int32_t gX, int32_t aY, int32_t gY, int32_t aZ, int32_t gZ);
int16_t displayWriteText( uint8_t xPos, uint8_t yPos, char * textToWrite);



#endif /* INC_DISPLAYFUNCTIONS_H_ */
