/**************************************************/
/* This file manages the interrupts of stm32 chip */
/**************************************************/

#include "xm_hardware.h"

#ifdef __cplusplus
extern "C" {		//Below functions don't use C++ name but C name.
#endif
	
/*put data from host computer through rs485 to the queue*/
void USART2_IRQHandler(void)
{
    unsigned char data;

    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        data = USART2->DR;
		if(queue.fullCheck()==0)
		{
           queue.putData(data);
        }
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);   
    }
}
/*timer's counter plus themselves*/
void TIM6_DAC_IRQHandler(void)
{ 

    if(TIM_GetITStatus(TIM6 , TIM_IT_Update)== SET  )
    {
        board_controller.cnt_1ms++;
        board_controller.cnt_2ms++;
        board_controller.cnt_5ms++;
        board_controller.cnt_10ms++;
        board_controller.cnt_20ms++;
        board_controller.cnt_50ms++;
		board_controller.cnt_100ms++;
		board_controller.cnt_500ms++;
        TIM_ClearITPendingBit(TIM6 , TIM_FLAG_Update);     
    }
}
/*find bug's location*/
void HardFault_Handler(void)
{
	board_controller.mmp++;
}


#ifdef __cplusplus
}
#endif
