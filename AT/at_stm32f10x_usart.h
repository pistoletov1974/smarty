#include "stm32f10x_usart.h"
#include "stm32f10x.h"


void AT_USART_Putc(USART_TypeDef* USARTx, volatile char c);
void AT_USART_Puts(USART_TypeDef* USARTx, char* str);
