#include "photodetector.h"

Photodetector photodetector;
/********************************************************************************************/
/*************************** Median value average filtering method **************************/
/********************************************************************************************/
void  Photodetector::DMAEnable(void)
{
	board_controller.DMAInit((uint32_t)voltage_u16_array); 
}
	
uint16_t Photodetector::read_pd(void)
{
	voltage_u16_sum = 0;
//	for(i=0; i<10; i++)
//	{
//		voltage_u16_array[i] = board_controller.ADC1GetChar();	
//	}
	
	QuickSort(voltage_u16_array,0,19);
	for(i=6; i<14; i++)
	{
		voltage_u16_sum +=  voltage_u16_array[i];
	}
	voltage_u16 = voltage_u16_sum*0.125;
	
	return voltage_u16;
}
//PD data dealing ,quick sort algorithm
void Photodetector::QuickSort(uint16_t * arr, int8_t low, int8_t high)
{
	if(low < high)
	{
		int16_t index = GetIndex(arr,low,high);
		QuickSort(arr,low, index-1);
		QuickSort(arr,index+1,high);
	}
}
//PD data dealing ,search tmp's index
int8_t Photodetector::GetIndex(uint16_t * arr, int8_t low, int8_t high)
{
	uint16_t tmp = arr[low];
	while (low < high)
	{
		while (low < high && arr[high] >= tmp)
		{
			high--;
		}
		arr[low]=arr[high];
		while (low < high && arr[low] <= tmp)
		{
			low++;
		}	
		arr[high]=arr[low];
	}
	arr[low] = tmp;
	return low;
}
