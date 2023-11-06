/*
 * accelerometer.c
 *
 *  Created on: Nov 5, 2023
 *      Author: nick_
 */
#include "accelerometer.h"
#include "app.h"

#include "main.h"

extern SPI_HandleTypeDef hspi1;




/*
 *
 * HAL_StatusTypeDef HAL_SPI_Receive(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout)
 *
 *
 * HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout)
 *
 *
 * HAL_StatusTypeDef HAL_SPI_TransmitReceive(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size,
 *
 *
 *
 *
 * */

//void EnableImu(void);
//
//void AccellerationX (void);
//void AccellerationY (void);
//void AccellerationZ (void);

void EnableImu(void)
{
	//Set the PD bit to 1
	uint8_t regValue = 0;
	uint8_t receivedData[4] = {0};
	uint8_t transmitData[4] = {0};
	HAL_StatusTypeDef halStatus;

	//Turn CS to high
	HAL_GPIO_WritePin(GPIOE, CS_I2C_SPI_Pin, GPIO_PIN_SET);

	HAL_Delay(10);



	//transmitData[0] = 0;
	//transmitData[0] = 0b10000000 | WHO_AM_I;
	transmitData[0] = WHO_AM_I;
	//transmitData[1] = 0x80;
	//transmitData[2] = 0b01010101;
	//transmitData[2] = WHO_AM_I;
	transmitData[3] = 0b10000000 | WHO_AM_I;

	HAL_GPIO_WritePin(GPIOE, CS_I2C_SPI_Pin, GPIO_PIN_RESET);

	//Read the CTRL_REG1 register
	HAL_SPI_Transmit(&hspi1, &transmitData[0], 8, 100);
	//HAL_Delay(5);
	//HAL_SPI_Receive(&hspi1, receivedData, 1, 100);

	//halStatus = HAL_SPI_TransmitReceive(&hspi1, (uint8_t*)&transmitData, (uint8_t*)&receivedData, 6, 100);

	HAL_GPIO_WritePin(GPIOE, CS_I2C_SPI_Pin, GPIO_PIN_SET);

	regValue = receivedData[0];

}



