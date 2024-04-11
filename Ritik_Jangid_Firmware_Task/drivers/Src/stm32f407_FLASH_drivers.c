/*
 * stm32f407_FLASH_drivers.c
 *
 *  Created on: Apr 11, 2024
 *      Author: ritik
 */

#include "stm32f407_FLASH_drivers.h"


static void Flash_flushcache(void){
	if ((FLASH_REG->ACR & (1<<FLASH_ACR_ICEN)) != RESET)
	{
		FLASH_REG->ACR &= ~(1<<FLASH_ACR_ICEN);
		FLASH_REG->ACR |= (1<<FLASH_ACR_ICRST);
		FLASH_REG->ACR &= ~(1<<FLASH_ACR_ICRST);
		FLASH_REG->ACR |= (1<<FLASH_ACR_ICEN);
	}


	if ((FLASH_REG->ACR & (1<<FLASH_ACR_DCEN)) != RESET)
	{
		FLASH_REG->ACR &= ~(1<<FLASH_ACR_DCEN);
		FLASH_REG->ACR |= (1<<FLASH_ACR_DCRST);
		FLASH_REG->ACR &= ~(1<<FLASH_ACR_DCRST);
		FLASH_REG->ACR |= (1<<FLASH_ACR_DCEN);
	}
}

void Flash_Lock(void){
	FLASH_REG->CR |= (1<<FLASH_CR_LOCK);
}
void FLash_Unlock(void){
	if((FLASH_REG->CR & (1<<FLASH_CR_LOCK))  != RESET){
		FLASH_REG->KEYR = FLASH_KEY1;
		FLASH_REG->KEYR = FLASH_KEY2;
	}

}
void Flash_OB_Lock(void){
	FLASH_REG->OPTCR |= (1<<FLASH_OPT_OPTLOCK);
}
void Flash_OB_Unlock(void){
	if((FLASH_REG->OPTCR & (1<<FLASH_OPT_OPTLOCK))  != RESET){
		FLASH_REG->OPTKEYR = FLASH_OPT_KEY1;
		FLASH_REG->OPTKEYR = FLASH_OPT_KEY2;
	}
}

void Flash_Erase_Sector7(void){
	FLash_Unlock();
	Flash_OB_Unlock();
	while((FLASH_REG->SR & (1<<FLASH_SR_BSY)) != RESET);

	FLASH_REG->CR &= ~(3<<FLASH_CR_PSIZE);
	FLASH_REG->CR |= (3<<FLASH_CR_PSIZE);
	FLASH_REG->CR &= ~(0x1f<<FLASH_CR_SNB);
	FLASH_REG->CR |= (1<<FLASH_CR_SER) | (7 << FLASH_CR_SNB);
	FLASH_REG->CR |= (1<<FLASH_CR_STRT);

	while((FLASH_REG->SR & (1<<FLASH_SR_BSY)) != RESET);

	FLASH_REG->CR &= ~((1<<FLASH_CR_SER) | (0x1f<<FLASH_CR_SNB));

	Flash_flushcache();
	Flash_OB_Lock();
	Flash_Lock();


}

void Flash_read_Sector7 (uint8_t *data,uint32_t No_of_bytes){
	volatile uint32_t read_data;
	volatile uint32_t read_cnt=0;
	do
	{
		read_data = *(uint32_t*)(0x08060000 + read_cnt);
		if(read_data != 0xFFFFFFFF)
		{
			data[read_cnt] = (uint8_t)read_data;
			data[read_cnt + 1] = (uint8_t)(read_data >> 8);
			data[read_cnt + 2] = (uint8_t)(read_data >> 16);
			data[read_cnt + 3] = (uint8_t)(read_data >> 24);
			read_cnt += 4;
		}
	}while(read_data != 0xFFFFFFFF);
}

void Flash_program_BYTE(uint8_t *Address , uint8_t data){

	FLASH_REG->CR &= ~(3<<FLASH_CR_PSIZE);
	FLASH_REG->CR |= 0;
	FLASH_REG->CR |= (1<<FLASH_CR_PG);

	*Address = data;
	while((FLASH_REG->SR & (1<<FLASH_SR_BSY)) != RESET);

	FLASH_REG->CR &= ~(1<<FLASH_CR_PG);
}
