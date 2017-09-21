#ifndef __I2C_H
#define __I2C_H

//#include "stm32f10x.h"
//#include "stm32l1xx.h"
#include "main.h"


#define LCD_ON()								GPIOx->BSRRH = GPIO_Pin

void I2C_LowLevel_Init(void);
void I2C_LowLevel_DeInit(void);
uint32_t I2C_WrBuf(uint8_t DataCmd, uint8_t *buf, uint32_t cnt);
uint32_t I2C_RdBuf(uint8_t DevAddr, uint8_t *buf, uint32_t cnt);
uint32_t I2C_RdBufEasy(uint8_t DevAddr, uint8_t *buf, uint32_t cnt);

#endif //__I2C_H
