/*
 * accelero_io.h
 *
 *  Created on: Nov 8, 2023
 *      Author: nick_
 */

#ifndef INC_ACCELERO_IO_H_
#define INC_ACCELERO_IO_H_


/*############################# ACCELEROMETER ################################*/
/* Read/Write command */
#define READWRITE_CMD                     ((uint8_t)0x80)
/* Multiple byte read/write command */
#define MULTIPLEBYTE_CMD                  ((uint8_t)0x40)
/* Dummy Byte Send by the SPI Master device in order to generate the Clock to the Slave device */
#define DUMMY_BYTE                        ((uint8_t)0x00)

/* Chip Select macro definition */
#define ACCELERO_CS_LOW()       HAL_GPIO_WritePin(ACCELERO_CS_GPIO_PORT, ACCELERO_CS_PIN, GPIO_PIN_RESET)
#define ACCELERO_CS_HIGH()      HAL_GPIO_WritePin(ACCELERO_CS_GPIO_PORT, ACCELERO_CS_PIN, GPIO_PIN_SET)

/**
  * @brief  ACCELEROMETER Interface pins
  */
#define ACCELERO_CS_PIN                        GPIO_PIN_3                 /* PE.03 */
#define ACCELERO_CS_GPIO_PORT                  GPIOE                      /* GPIOE */
#define ACCELERO_CS_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOE_CLK_ENABLE()
#define ACCELERO_CS_GPIO_CLK_DISABLE()         __HAL_RCC_GPIOE_CLK_DISABLE()
#define ACCELERO_INT_GPIO_PORT                 GPIOE                      /* GPIOE */
#define ACCELERO_INT_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOE_CLK_ENABLE()
#define ACCELERO_INT_GPIO_CLK_DISABLE()        __HAL_RCC_GPIOE_CLK_DISABLE()
#define ACCELERO_INT1_PIN                      GPIO_PIN_0                 /* PE.00 */
#define ACCELERO_INT1_EXTI_IRQn                EXTI0_IRQn
#define ACCELERO_INT2_PIN                      GPIO_PIN_1                 /* PE.01 */
#define ACCELERO_INT2_EXTI_IRQn                EXTI1_IRQn
/**
  * @}
  */




#endif /* INC_ACCELERO_IO_H_ */
