/**********************************************************/
/* This file is used to control the modules of stm32 chip */
/**********************************************************/

#include "board_controller.h"

Board_controller  board_controller;
/*board controller constructor*/
Board_controller::Board_controller()
{																//initiative some timers' counters
    cnt_1ms = 0;          
    cnt_2ms = 0;
    cnt_5ms = 0;
    cnt_10ms = 0;
    cnt_20ms = 0;
    cnt_50ms  = 0;
}
/*stm32 chip initialization*/
void Board_controller::boardBasicInit(void)
{
	Xm_System_timer_Init();
	Xm_NVIC_Init();
	Xm_Led_Init();
	Xm_Communicate_Init();
	Xm_Timer_Init();
	Xm_Motor_Communicate_Init();
	Vcsel_Bias_Init();
	Vcsel_Sinep2p_Init();
	Vcsel_Sinefre_Init();	
}
/*chip delay functions initialization*/
void Board_controller::Xm_System_timer_Init()
{
	System_Timer_Init(168);
}
/*chip interrupt management initialization*/
void Board_controller::Xm_NVIC_Init()
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}
/*chip level output initialization*/
void Board_controller::Xm_Led_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;    
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_1|GPIO_Pin_2 ;
    GPIO_Init(GPIOC , &GPIO_InitStruct);
	GPIO_ResetBits(GPIOC,GPIO_Pin_1 | GPIO_Pin_2);
}
/*chip Universal Synchronous/Asynchronous Receiver/Transmitter2 initialization*/
void Board_controller::Xm_Communicate_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;
    GPIO_StructInit(&GPIO_InitStructure);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,  ENABLE);
		
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP; 

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2|GPIO_Pin_3;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);

	
	USART_InitStructure.USART_BaudRate = 115200 ;  
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);
	
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	USART_Cmd(USART2, ENABLE);
}
/*chip timer6 initialization*/
void Board_controller::Xm_Timer_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6 , ENABLE);

	TIM_TimeBaseStructure.TIM_Prescaler     = (84 - 1);
	TIM_TimeBaseStructure.TIM_Period        = 1000-1 ;               
    TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1; 		
    TIM_TimeBaseStructure.TIM_CounterMode   =TIM_CounterMode_Up;   
    TIM_TimeBaseInit(TIM6 , &TIM_TimeBaseStructure);
	
    TIM_ITConfig(TIM6 ,TIM_IT_Update,ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
                    
    TIM_Cmd(TIM6 , ENABLE);
}
/*chip Controller Area Network1 initialization*/
void Board_controller::Xm_Motor_Communicate_Init(void)
{
    CAN_InitTypeDef        CAN_InitStructure;
    CAN_FilterInitTypeDef  CAN_FilterInitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11| GPIO_Pin_12;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_CAN1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_CAN1);

    CAN_InitStructure.CAN_TTCM = DISABLE;			  
    CAN_InitStructure.CAN_AWUM = DISABLE;			 
    CAN_InitStructure.CAN_NART = ENABLE;
    CAN_InitStructure.CAN_RFLM = DISABLE;
    CAN_InitStructure.CAN_TXFP = DISABLE;
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;	 
    CAN_InitStructure.CAN_SJW  = CAN_SJW_1tq;
    CAN_InitStructure.CAN_BS1  = CAN_BS2_6tq;
    CAN_InitStructure.CAN_BS2  = CAN_BS1_7tq;
    CAN_InitStructure.CAN_Prescaler =3;               
    CAN_Init(CAN1, &CAN_InitStructure);
	
	CAN_FilterInitStructure.CAN_FilterNumber=0;
    CAN_FilterInitStructure.CAN_FilterMode  =CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale =CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;
    CAN_FilterInitStructure.CAN_FilterIdLow =0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;
    CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure);
	
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);  	
  
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;         
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	          
    NVIC_Init(&NVIC_InitStructure);
}
/*VCSEL bias value control, SPI1 initialization*/
void Board_controller::Vcsel_Bias_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_SPI1);  
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_SPI1); 
 
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,ENABLE);
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,DISABLE);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;  
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//must 1Edge!!!!
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	
	SPI_InitStructure.SPI_CRCPolynomial = 7;	
	SPI_Init(SPI1, &SPI_InitStructure);
	
	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler_8));
	SPI1->CR1&=0XFFC7;
	SPI1->CR1|=SPI_BaudRatePrescaler_8;	 
	SPI_Cmd(SPI1,ENABLE);
}
/*VCSEL AC sine wave's peak-to-peak value voltage control, SPI2 initialization*/
void Board_controller::Vcsel_Sinep2p_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_15;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_SPI2);  
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_SPI2); 
	
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2,ENABLE);
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2,DISABLE);

	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;  
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//must 1Edge!!!!
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	
	SPI_InitStructure.SPI_CRCPolynomial = 7;	
	SPI_Init(SPI2, &SPI_InitStructure);
	
	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler_8));
	SPI2->CR1&=0XFFC7;
	SPI2->CR1|=SPI_BaudRatePrescaler_8;	 
	SPI_Cmd(SPI2,ENABLE);
}
/*VCSEL sine wave's frequency control, SPI3 initialization*/
void Board_controller::Vcsel_Sinefre_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_12;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_SPI3);  
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_SPI3); 
	
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3,ENABLE);
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3,DISABLE);

	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;  
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;		
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;				//must 1Edge!!!!
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	
	SPI_InitStructure.SPI_CRCPolynomial = 7;	
	SPI_Init(SPI3, &SPI_InitStructure);
	
	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler_8));
	SPI3->CR1&=0XFFC7;
	SPI3->CR1|=SPI_BaudRatePrescaler_8;	 
	SPI_Cmd(SPI3,ENABLE);
}

/*chip send can data function*/
void Board_controller::Motor_Sendmessage(unsigned int ID, uint8_t *TxBuf)
{
    CanTxMsg TxMessageBuffer;
    uint8_t i;
	uint8_t Length=8;
    TxMessageBuffer.StdId=ID;
    TxMessageBuffer.RTR=0;
    TxMessageBuffer.IDE=0;
    TxMessageBuffer.DLC=Length;
    
    for(i=0;i<Length;i++)
    {
        TxMessageBuffer.Data[i]=*(TxBuf+i);
    }
    CAN_Transmit(CAN1, &TxMessageBuffer);  

}  
/*chip set level output function*/
void Board_controller::SetLedState(uint8_t led_id, uint8_t operation)
{
	if ( led_id == 0)
	{
		if(operation == 0){ GPIO_SetBits(GPIOC , GPIO_Pin_1);}
        else if(operation == 1) { GPIO_ResetBits(GPIOC , GPIO_Pin_1);}
		else if(operation == 2) { GPIO_ToggleBits(GPIOC , GPIO_Pin_1);}
	}
    else if(led_id == 1)
	{
        if(operation == 0){ GPIO_SetBits(GPIOC , GPIO_Pin_2);}
        else if(operation == 1) { GPIO_ResetBits(GPIOC , GPIO_Pin_2);}
		else if(operation == 2) { GPIO_ToggleBits(GPIOC , GPIO_Pin_2);}
    }
}
/*chip set rs485 state*/
void Board_controller::rs485_cmd(unsigned char state)
{
	if(state==0)GPIO_ResetBits (GPIOA,GPIO_Pin_1);
	if(state==1)GPIO_SetBits   (GPIOA,GPIO_Pin_1);
}
/*chip rs485 send a char*/
void Board_controller::rs485_sendchar(uint8_t Tx_Byte)
{
    USART_SendData(USART2 , (uint8_t)Tx_Byte);
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
	delay_us(20);
}
/*chip SPI1 send a char*/
void Board_controller::SPI1SendChar(uint8_t Data)
{
	GPIO_SetBits(GPIOA , GPIO_Pin_4);
	GPIO_ResetBits(GPIOA , GPIO_Pin_4);
	delay_us(20);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){}  
	SPI_I2S_SendData(SPI1, Data);
	delay_us(20);						//necessary delay,at least 2us
	GPIO_SetBits(GPIOA , GPIO_Pin_4);
}
/*chip SPI1 send a buffer*/
void Board_controller::SPI1SendBuffer(uint8_t *buffer, uint16_t len)
{
	GPIO_SetBits(GPIOA , GPIO_Pin_4);
	GPIO_ResetBits(GPIOA , GPIO_Pin_4);
	delay_us(20);
	uint16_t i;
	for(i = len ;i > 0;i--)
	{
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){}  
		SPI_I2S_SendData(SPI1, buffer[i-1]);
	}
	delay_us(20);						//necessary delay,at least 2us
	GPIO_SetBits(GPIOA , GPIO_Pin_4);
}
/*chip SPI2 send a char*/
void Board_controller::SPI2SendChar(uint8_t Data)
{
	GPIO_SetBits(GPIOB , GPIO_Pin_12);
	GPIO_ResetBits(GPIOB , GPIO_Pin_12);
	delay_us(20);
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET){}  
	SPI_I2S_SendData(SPI2, Data);
	delay_us(20);						//necessary delay,at least 2us
	GPIO_SetBits(GPIOB , GPIO_Pin_12);
}
/*chip SPI2 send a buffer*/
void Board_controller::SPI2SendBuffer(uint8_t *buffer, uint16_t len)
{
	GPIO_SetBits(GPIOB , GPIO_Pin_12);
	GPIO_ResetBits(GPIOB , GPIO_Pin_12);
	delay_us(20);
	uint16_t i;
	for(i = len ;i > 0;i--)
	{
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET){}  
		SPI_I2S_SendData(SPI2, buffer[i-1]);
	}
	delay_us(20);						//necessary delay,at least 2us
	delay_us(20);						//necessary delay,at least 2us
	GPIO_SetBits(GPIOB , GPIO_Pin_12);
}
/*chip SPI3 send a unsigned short int*/
void Board_controller::SPI3SendUSInt(uint16_t Data)
{
	GPIO_SetBits(GPIOA , GPIO_Pin_15);
	GPIO_ResetBits(GPIOA , GPIO_Pin_15);
	delay_us(20);
	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET){}  
	SPI_I2S_SendData(SPI3, Data);
	delay_us(20);						//necessary delay,at least 2us
	GPIO_SetBits(GPIOA , GPIO_Pin_15);
}
/*chip SPI3 send a buffer*/
void Board_controller::SPI3SendBuffer(uint16_t *buffer, uint16_t len)
{
	GPIO_SetBits(GPIOA , GPIO_Pin_15);
	GPIO_ResetBits(GPIOA , GPIO_Pin_15);
	delay_us(20);
	uint16_t i;
	for(i = len ;i > 0;i--)
	{
		while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET){}  
		SPI_I2S_SendData(SPI3, buffer[i-1]);
	}
	delay_us(20);						//necessary delay,at least 2us
	delay_us(20);						//necessary delay,at least 2us
	GPIO_SetBits(GPIOA , GPIO_Pin_15);
}

