#include "stm32f10x.h"                  // Device header
#include "main.h"
#include "at_stm32f10x_usart.h" 
#include "at_stm32f10x_nrf24l01.h" 
#include "stdio.h"
#include "delay.h"
#include "nrf24l01.h"
#include "I2CRoutines.h"


int main (void)
{
	char buf[80];
  uint8_t state=0, newstate=0;
	unsigned char i,v;
	uint32_t st,en;
	//extern uint32_t SystemCoreClock; 
	
	
	// enable clock to peripherials
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO | RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 | RCC_APB1Periph_TIM2,ENABLE);
	
	
	//init routines
	GPIO_CONFIG();
	TIM_CONFIG();
	MY_USART_CONFIG();
	nRF24_init();
	//DWT_Init(); //using for microseconds delay
	SystemCoreClockUpdate();
  //I2C_LowLevel_Init(I2C1);

	
	
	
	
	//startup code
	AT_USART_Puts(USART2, "Hello world\n\r");
	sprintf(buf,"%d \r\n",SystemCoreClock);	
	AT_USART_Puts(USART2,buf);

		  // OledCls();
			 TIM_SetCounter(TIM1,0);

	


if (nRF24_Check() != 0)
	{
		AT_USART_Puts(USART2,"Got wrong answer from SPI device.\n");
		AT_USART_Puts(USART2,"MCU is now halt.\n");
		while(1);
	}

//print nrf registers
	
	for (i = 0; i < 0x1D; i++) {
	
		v = nRF24_ReadReg(i);
		sprintf(buf,"REG[%d]=%02x\r\n",i,v);
		AT_USART_Puts(USART2,buf);
	
	}
	
	
	
	
	while (1)
	{
    //TIM1->CNT = 0;
		
		state= TIM_GetCounter(TIM1)/2;
		if (state>=95) 	TIM_SetCounter(TIM1,95);
		if (state!=newstate)
		{
		sprintf(buf,"%d \r\n",state);	
		AT_USART_Puts(USART2,buf);
		newstate = state;
		}
		
		
		
		
		
	}
}





	
	
	void TIM_CONFIG(void)
	{
			// INIT TIMER IN ENCODER MODE
	
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV2;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Down ;
	TIM_TimeBaseStructure.TIM_Period = 100; 
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);
	// TIM_EncoderMode_TI1: Counter counts on TI1FP1 edge depending on TI2FP2 level.
	TIM_EncoderInterfaceConfig(TIM1,TIM_EncoderMode_TI1,TIM_ICPolarity_Rising,  TIM_ICPolarity_Falling);
	TIM_Cmd(TIM1, ENABLE);
	}		
	
	
		void GPIO_CONFIG(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	

	// ENCODER INPUTS
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	//GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);
  
	
	
  // USART PINS Tx pin pa2
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_10MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	 // USART PINS Rx pin pa3
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_10MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	}

	
void MY_USART_CONFIG(void)
{	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate=19200;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=  USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART2, &USART_InitStructure);
	USART_Cmd(USART2, ENABLE);
	

 
	}
void IT_CONFIG (void)
{
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource10);
	EXTI_InitTypeDef EXTIInit;
	EXTIInit.EXTI_Line=EXTI_Line10;
	
	
	
	// Interrupt for i2c OLED display communication
	    /* 1 bit for pre-emption priority, 3 bits for subpriority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    NVIC_SetPriority(I2C1_EV_IRQn, 0x00); 
    NVIC_EnableIRQ(I2C1_EV_IRQn);

    NVIC_SetPriority(I2C1_ER_IRQn, 0x01); 
    NVIC_EnableIRQ(I2C1_ER_IRQn);
    
    
    NVIC_SetPriority(I2C2_EV_IRQn, 0x00);
    NVIC_EnableIRQ(I2C2_EV_IRQn);

    NVIC_SetPriority(I2C2_ER_IRQn, 0x01); 
    NVIC_EnableIRQ(I2C2_ER_IRQn);
	
	
	
}
