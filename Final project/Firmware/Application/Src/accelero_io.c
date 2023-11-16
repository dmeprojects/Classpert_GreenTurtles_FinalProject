/*
 * accelero_io.c
 *
 *  Created on: Nov 8, 2023
 *      Author: nick_
 */

#include "main.h"
#include "accelero_io.h"

extern SPI_HandleTypeDef hspi1;

uint32_t SpixTimeout = 100;    /*<! Value of Timeout when SPI communication fails */

static void     SPIx_Init(void);
//static void     SPIx_MspInit(void);
static uint8_t  SPIx_WriteRead(uint8_t Byte);
static  void    SPIx_Error(void);

/* Link functions for Accelerometer peripheral */
void            ACCELERO_IO_Init(void);
void            ACCELERO_IO_ITConfig(void);
void            ACCELERO_IO_Write(uint8_t *pBuffer, uint8_t WriteAddr, uint16_t NumByteToWrite);
void            ACCELERO_IO_Read(uint8_t *pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead);

/*******************************************************************************
                            BUS OPERATIONS
*******************************************************************************/

/******************************* SPI Routines *********************************/

/**
  * @brief  SPIx Bus initialization
  */
static void SPIx_Init(void)
{
  if(HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_RESET)
  {
    /* SPI configuration -----------------------------------------------------*/
    hspi1.Instance = SPI1;
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;
    hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
    hspi1.Init.CRCPolynomial = 7;
    hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi1.Init.NSS = SPI_NSS_SOFT;
    hspi1.Init.TIMode = SPI_TIMODE_DISABLED;
    hspi1.Init.Mode = SPI_MODE_MASTER;

    //SPIx_MspInit();
    HAL_SPI_Init(&hspi1);
  }
}

/**
  * @brief  Sends a Byte through the SPI interface and return the Byte received
  *         from the SPI bus.
  * @param  Byte: Byte send.
  * @retval The received byte value
  */
static uint8_t SPIx_WriteRead(uint8_t Byte)
{
  uint8_t receivedbyte = 0;

  /* Send a Byte through the SPI peripheral */
  /* Read byte from the SPI bus */
  if(HAL_SPI_TransmitReceive(&hspi1, (uint8_t*) &Byte, (uint8_t*) &receivedbyte, 1, SpixTimeout) != HAL_OK)
  {
    SPIx_Error();
  }

  return receivedbyte;
}

/**
  * @brief  SPIx error treatment function.
  */
static void SPIx_Error(void)
{
  /* De-initialize the SPI communication bus */
  HAL_SPI_DeInit(&hspi1);

  /* Re-Initialize the SPI communication bus */
  SPIx_Init();
}

/*******************************************************************************
                            LINK OPERATIONS
*******************************************************************************/

/***************************** LINK ACCELEROMETER *****************************/

/**
  * @brief  Configures the Accelerometer SPI interface.
  */
void ACCELERO_IO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure the Accelerometer Control pins --------------------------------*/
  /* Enable CS GPIO clock and configure GPIO pin for Accelerometer Chip select */
  ACCELERO_CS_GPIO_CLK_ENABLE();

  /* Configure GPIO PIN for LIS Chip select */
  GPIO_InitStructure.Pin = ACCELERO_CS_PIN;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Pull  = GPIO_NOPULL;
  GPIO_InitStructure.Speed = GPIO_SPEED_MEDIUM;
  HAL_GPIO_Init(ACCELERO_CS_GPIO_PORT, &GPIO_InitStructure);

  /* Deselect: Chip Select high */
  ACCELERO_CS_HIGH();

  SPIx_Init();
}

/**
  * @brief  Configures the Accelerometer INT2.
  *         EXTI0 is already used by user button so INT1 is not configured here.
  */
void ACCELERO_IO_ITConfig(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable INT2 GPIO clock and configure GPIO PINs to detect Interrupts */
  ACCELERO_INT_GPIO_CLK_ENABLE();

  /* Configure GPIO PINs to detect Interrupts */
  GPIO_InitStructure.Pin = ACCELERO_INT2_PIN;
  GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ACCELERO_INT_GPIO_PORT, &GPIO_InitStructure);

  /* Enable and set Accelerometer INT2 to the lowest priority */
  HAL_NVIC_SetPriority((IRQn_Type)ACCELERO_INT2_EXTI_IRQn, 0x0F, 0);
  HAL_NVIC_EnableIRQ((IRQn_Type)ACCELERO_INT2_EXTI_IRQn);
}

/**
  * @brief  Writes one byte to the Accelerometer.
  * @param  pBuffer: pointer to the buffer containing the data to be written to the Accelerometer.
  * @param  WriteAddr: Accelerometer's internal address to write to.
  * @param  NumByteToWrite: Number of bytes to write.
  */
void ACCELERO_IO_Write(uint8_t *pBuffer, uint8_t WriteAddr, uint16_t NumByteToWrite)
{
  /* Configure the MS bit:
     - When 0, the address will remain unchanged in multiple read/write commands.
     - When 1, the address will be auto incremented in multiple read/write commands.
  */
  if(NumByteToWrite > 0x01)
  {
    WriteAddr |= (uint8_t)MULTIPLEBYTE_CMD;
  }
  /* Set chip select Low at the start of the transmission */
  ACCELERO_CS_LOW();

  /* Send the Address of the indexed register */
  SPIx_WriteRead(WriteAddr);

  /* Send the data that will be written into the device (MSB First) */
  while(NumByteToWrite >= 0x01)
  {
    SPIx_WriteRead(*pBuffer);
    NumByteToWrite--;
    pBuffer++;
  }

  /* Set chip select High at the end of the transmission */
  ACCELERO_CS_HIGH();
}

/**
  * @brief  Reads a block of data from the Accelerometer.
  * @param  pBuffer: pointer to the buffer that receives the data read from the Accelerometer.
  * @param  ReadAddr: Accelerometer's internal address to read from.
  * @param  NumByteToRead: number of bytes to read from the Accelerometer.
  */
void ACCELERO_IO_Read(uint8_t *pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead)
{
  if(NumByteToRead > 0x01)
  {
    ReadAddr |= (uint8_t)(READWRITE_CMD | MULTIPLEBYTE_CMD);
  }
  else
  {
    ReadAddr |= (uint8_t)READWRITE_CMD;
  }
  /* Set chip select Low at the start of the transmission */
  ACCELERO_CS_LOW();

  /* Send the Address of the indexed register */
  SPIx_WriteRead(ReadAddr);

  /* Receive the data that will be read from the device (MSB First) */
  while(NumByteToRead > 0x00)
  {
    /* Send dummy byte (0x00) to generate the SPI clock to ACCELEROMETER (Slave device) */
    *pBuffer = SPIx_WriteRead(DUMMY_BYTE);
    NumByteToRead--;
    pBuffer++;
  }

  /* Set chip select High at the end of the transmission */
  ACCELERO_CS_HIGH();
}
