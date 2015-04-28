// prototypes
void GPIO_CONFIG(void);
void TIM_CONFIG(void);
void MY_USART_CONFIG(void);
//end
ErrorStatus HSEStartUpStatus;
/* Buffer of data to be received by I2C1 */
uint8_t Buffer_Rx1[255];
/* Buffer of data to be transmitted by I2C1 */
uint8_t Buffer_Tx1[255] = {0xc0, 0x6,0x8,0xA};
/* Buffer of data to be received by I2C2 */
uint8_t Buffer_Rx2[255];
/* Buffer of data to be transmitted by I2C2 */
uint8_t Buffer_Tx2[255] = {0xF, 0xB, 0xC,0xD};
uint8_t Buffer_Init[255]={0x80,	//control byte
0xae,//Display OFF
0x00,//Low Column
0x10,//High Column
0xB0,//Page 
0x40,//Start line
	
0xA1,//remap 
0xDA,//com pins 
0x12,
0xD3, //display offset
0x00,//NO offset
0xc0,//scan direction
0xc8,
0xA6,//normal display
0xA4,//display ON 
	
0x81,//set contrast
0x50,//contrast DATA
	
0xa8,//multiplex ratio 
0x3f,//1/64 duty 
		
0xD5,//Display clock divide
0x80,
	
0xd9,//precharge period
0xF1,

0xDB,//VCOM deselect
0x40,

0x8d,//charge pump 
0x14,

0xAF,//display ON
};
uint8_t Buffer_Data[1024];

extern __IO uint8_t Tx_Idx1 , Rx_Idx1;
extern __IO uint8_t Tx_Idx2 , Rx_Idx2;
