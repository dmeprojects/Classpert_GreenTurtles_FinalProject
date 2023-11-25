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

static void writeImuRegister(uint8_t* address, uint8_t* data);
static void readImuRegister(uint8_t* data, uint16_t bytes);




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

void resetImu (void)
{

}

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

	//Reset device using the SW reset bit
	transmitData[0] = CTRL_REG1;
	transmitData[1] = 0x00 | (1<<CTRL_REG1_SWRESET);

	HAL_GPIO_WritePin(GPIOE, CS_I2C_SPI_Pin, GPIO_PIN_RESET);

	HAL_SPI_Transmit(&hspi1, &transmitData[0], 2, 100);

	HAL_GPIO_WritePin(GPIOE, CS_I2C_SPI_Pin, GPIO_PIN_SET);

	HAL_Delay(1);

	//Reset device using the boot bit in the ctrl1 register
	transmitData[0] = CTRL_REG1;
	transmitData[1] = 0x00 | (1<<CTRL_REG1_BOOT);

	HAL_GPIO_WritePin(GPIOE, CS_I2C_SPI_Pin, GPIO_PIN_RESET);

	HAL_SPI_Transmit(&hspi1, &transmitData[0], 2, 100);

	HAL_GPIO_WritePin(GPIOE, CS_I2C_SPI_Pin, GPIO_PIN_SET);

	HAL_Delay(15);


	//Read out the who am i register to verify correct operation
	transmitData[0] = 0b10000000 | WHO_AM_I_2;

	HAL_GPIO_WritePin(GPIOE, CS_I2C_SPI_Pin, GPIO_PIN_RESET);

	//Read the CTRL_REG1 register
	HAL_SPI_Transmit(&hspi1, &transmitData[0], 1, 100);
	//HAL_Delay(5);
	HAL_SPI_Receive(&hspi1, &receivedData[0], 1, 100);

	//halStatus = HAL_SPI_TransmitReceive(&hspi1, (uint8_t*)&transmitData, (uint8_t*)&receivedData, 6, 100);

	HAL_GPIO_WritePin(GPIOE, CS_I2C_SPI_Pin, GPIO_PIN_SET);

	regValue = receivedData[0];

}

/*
 * writes the address to the IMU
 * */
static void writeImuRegister(uint8_t* address, uint8_t* data)
{

}
static void readImuRegister(uint8_t* data, uint16_t bytes);



