#ifndef PHOTODETECTOR_H
#define PHOTODETECTOR_H

#include "board_controller.h"

class Photodetector
{
	public:
		Photodetector()
		{	
			voltage_u16 = 0;
			voltage = 0;
			current = 0;
		}
		uint16_t read_pd(void);
		void DMAEnable(void);
		
	private:
		uint8_t i;
		uint16_t voltage_u16;
		uint16_t voltage_u16_sum;
		uint16_t voltage_u16_array[20];
		float voltage;
		float current;
	
		void QuickSort(uint16_t * arr, int8_t low, int8_t high);//PD data dealing ,quick sort algorithm
		int8_t GetIndex(uint16_t * arr, int8_t low, int8_t high);//PD data dealing ,search tmp's index
};

extern Photodetector photodetector;

#endif
