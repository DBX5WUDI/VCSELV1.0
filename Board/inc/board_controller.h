#ifndef BOARD_CONTROLLER_H
#define BOARD_CONTROLLER_H

#ifdef __cplusplus
extern "C" {											//board supporting files must write these lines, many.c files are linked.
#endif

#include "stm32f4xx.h"	
#include "delay.h"
	
class Board_controller
{
	public:
		/***************************************some timer counter********************************/
		uint16_t cnt_1ms;						
		uint16_t cnt_2ms;
		uint16_t cnt_5ms;
		uint16_t cnt_10ms;
		uint16_t cnt_20ms;
		uint16_t cnt_50ms;
		uint16_t cnt_100ms;
		uint16_t cnt_500ms;
		uint16_t mmp;
		/*****************************************************************************************/
	public:
		/*****************************************************************************************/
		Board_controller();											//board_control constructor
		void boardBasicInit(void);									//Initialize classes' constructor functions
		void Motor_Sendmessage(unsigned int ID, uint8_t *TxBuf);	//motor driver box send message
		void SetLedState(uint8_t led_id, uint8_t operation);		//set led's state
		void rs485_cmd(unsigned char state);						//enable/disable rs485
		void rs485_sendchar(uint8_t Tx_Byte);
		void HF_Flash_Write(uint32_t WriteAddr, uint32_t *pBuffer, uint32_t NumToWrite);
		void HF_Flash_Read(uint32_t ReadAddr, uint32_t *pBuffer, uint32_t NumToRead);  //read half word data(16 bits) from assign address
		void SPI1SendChar(uint8_t Data);
		void SPI1SendBuffer(uint8_t *buffer, uint16_t len);
		void SPI2SendChar(uint8_t Data);
		void SPI2SendBuffer(uint8_t *buffer, uint16_t len);
		void SPI3SendUSInt(uint16_t Data);
		void SPI3SendBuffer(uint16_t *buffer, uint16_t len);
		void DMAInit(uint32_t Memory0BaseAddr);
		uint16_t ADC1GetChar(void);
	/*****************************************************************************************/
	private:
		/*****************************************************************************************/
		void Xm_System_timer_Init(void);							//initialize the system timer
		void Xm_NVIC_Init(void);									//initialize the interrupt
		void Xm_Led_Init(void);										//initialize the led
		void Xm_Communicate_Init(void);								//initialize the communication between singlechip and computer 
		void Xm_Timer_Init(void);									//initialize the TIM timer
		void Xm_Motor_Communicate_Init(void);						//initialize the moter communication
		void Vcsel_Bias_Init(void);									//initialize the VCSEL DC bias voltage control, SPI1
		void Vcsel_Sinep2p_Init(void);								//initialize the VCSEL sine wave's peak-to-peak value , SPI2 initialization
		void Vcsel_Sinefre_Init(void);								//initialize the VCSEL sine wave's frequency , SPI3 initialization
		void Vcsel_Photodetector_Init(void);						//initialize Photodetector, ADC1_IN0 initialization
		/*****************************************************************************************/
};	

extern Board_controller board_controller;
#ifdef __cplusplus
}
#endif
#endif
