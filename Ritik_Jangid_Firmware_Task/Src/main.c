
#include "stm32f407xx.h"
#include<stdint.h>
#include<stdio.h>
#include<string.h>


//some variables used during the code
uint8_t rx_buf[2] ={0};
uint8_t rcv_set =RESET;
uint8_t *ptr = (uint8_t*)FLASH_SECTOR7_BASEADDR;
uint8_t finish[2]="\n";


void delay(void){
	for(int i=0;i<5000000;i++);
}

//USART1 handle initialization
USART_Handle_t usart1;

//UART1 Initializations

void USART1_inits(USART_Handle_t *pUSARTHandle){

	pUSARTHandle->pUARTx = USART1_REG;

	pUSARTHandle->USARTConfig.BAUD=USART_STD_BAUD_2400;
	pUSARTHandle->USARTConfig.HW_Flow_Ctrl=USART_HW_FLOW_CTRL_NONE;
	pUSARTHandle->USARTConfig.Mode=USART_MODE_TXRX;
	pUSARTHandle->USARTConfig.Parity_Ctrl=USART_PARITY_DISABLE;
	pUSARTHandle->USARTConfig.No_of_Stop_Bits=USART_STOPBITS_1;
	pUSARTHandle->USARTConfig.WordLength=USART_WORDLEN_8BITS;

	USART_IRQInterruptConfig(USART1_IRQ_NO, ENABLE);

	USART_Init(&usart1);
}


//Low Level initializations UART1

void GPIO_INITs(void){

	GPIO_Handle_t gpioB;

	gpioB.pGPIOx=GPIOB_REG;

	gpioB.GPIO_PinConfig.PinMode=GPIO_MODE_ALTFUN;
	gpioB.GPIO_PinConfig.PinAltFunMode=7;
	gpioB.GPIO_PinConfig.PinOPType=GPIO_OP_TYPE_PP;
	gpioB.GPIO_PinConfig.PinPuPdControl=GPIO_PU;
	gpioB.GPIO_PinConfig.PinSpeed=GPIO_OSPEED_MED;

	//Tx
	gpioB.GPIO_PinConfig.PinNumber=GPIO_PIN_NO_6;
	GPIO_init(&gpioB);

	//Rx
	gpioB.GPIO_PinConfig.PinNumber=GPIO_PIN_NO_7;
	GPIO_init(&gpioB);


    /* Loop forever */

}


int main(){

	delay();
	//IMPORTANT: Can't overwirte the Flash memory first need to erase it
	Flash_Erase_Sector7();

	//GPIO_ initializations
	GPIO_INITs();

	//UART1 Initializations
	USART1_inits(&usart1);

	//Peripheral Start
	USART_PeripheralControl(&usart1, ENABLE);
//  -----------------------------------------------------Reception----------------------------------------------
	//Flash Unlock for wirting
	FLash_Unlock();
	Flash_OB_Unlock();

	//Just to signal flash is ready to be written on
	printf("Ready\n\n");

	//main loop to Receive data in interrupt Mode
	while(rx_buf[0] != 13){
		while(USART_ReceiveDataIT(&usart1,rx_buf ,1) != USART_READY);

		while(rcv_set == RESET);
		rcv_set =RESET;

	}
	//Flash locked again
	Flash_Lock();
	Flash_OB_Lock();
//---------------------------------------------------------------------------------------------------
	printf("\n");


//-------------------------------------------------------Transmission---------------------------------
	//Pointer pointing to Flash
	uint8_t *ptr1 = (uint8_t*)FLASH_SECTOR7_BASEADDR;

	//Transmission in Blocking Mode
	while(*ptr1 != 13){
		USART_SendData(&usart1, ptr1, 1);
		ptr1++;
	}
	//just to finish with "\n"
	USART_SendData(&usart1, finish, 1);
//----------------------------------------------------------------------------------------------------

// Loop infinite
	while(1);
	return 0;
}




//Interrupt Controls for The UART

void USART1_IRQHandler(void){

	USART_IRQHandling(&usart1);

}
//Application Callback for Interrupt Mode USART_IRQ_handling
void USART_EventCallBack(USART_Handle_t *pUSARTHandle , uint8_t AppEv){
	if (AppEv == USART_TX_COMPLT){

	}else if(AppEv == USART_RX_COMPLT){
		//storing data to flash while receiving each Byte
		Flash_program_BYTE(ptr, rx_buf[0]);
		ptr++;

		rcv_set=SET;
		printf("%s",rx_buf);


	}

}
