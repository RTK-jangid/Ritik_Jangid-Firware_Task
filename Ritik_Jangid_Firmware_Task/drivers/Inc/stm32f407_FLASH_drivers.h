/*
 * stm32f407_FLASH_drivers.h
 *
 *  Created on: Apr 11, 2024
 *      Author: ritik
 */
#include "stm32f407xx.h"

#ifndef DRIVERS_INC_STM32F407_FLASH_DRIVERS_H_
#define DRIVERS_INC_STM32F407_FLASH_DRIVERS_H_


#define FLASH_SECTOR7_BASEADDR		0x08060000U

#define FLASH_KEY1               0x45670123U
#define FLASH_KEY2               0xCDEF89ABU
#define FLASH_OPT_KEY1           0x08192A3BU
#define FLASH_OPT_KEY2           0x4C5D6E7FU

void Flash_Erase_Sector7(void);
void Flash_read_Sector7 (uint8_t *buffer,uint32_t No_of_bytes);
void Flash_Lock(void);
void FLash_Unlock(void);
void Flash_OB_Lock(void);
void Flash_OB_Unlock(void);
void Flash_program_BYTE(uint8_t *Address , uint8_t data);

#endif /* DRIVERS_INC_STM32F407_FLASH_DRIVERS_H_ */
