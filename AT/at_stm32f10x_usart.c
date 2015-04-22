#include "at_stm32f10x_usart.h"
#include "stm32f10x_usart.h" 




		void AT_USART_Putc(USART_TypeDef* USARTx, volatile char c) {
	/* Wait to be ready */
	while (!USART_GetFlagStatus(USARTx, USART_FLAG_TXE));
	/* Send data */
	USARTx->DR = (uint16_t)(c & 0x01FF);
}
		
void AT_USART_Puts(USART_TypeDef* USARTx, char* str) {
	while (*str) {
		/* Send char by char */
	  AT_USART_Putc(USARTx, *str++);
		
		//TM_USART_Putc(USARTx, *str++);
	}
}
 
