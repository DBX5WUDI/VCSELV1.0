#ifndef VCSEL_H
#define VCSEL_H

#include "board_controller.h"

#define  DAD5660FULL 65535
#define  AD9834FRERATIO 5.3687091
class Vcsel
{
	public:
		Vcsel()
		{	
			voltage_bias = 0;
			voltage_sinep2p = 0;
			voltage_sinefre = 0;
		
			current_bias = 0;
			current_sinep2p = 0;
			current_sinefre = 0;
		}
		void set_vcsel_bias(float value);
		void set_vcsel_sinep2p(float value);
		void set_vcsel_sinefre(float value);		
		
	private:
		float voltage_bias;
		float voltage_sinep2p;
		float voltage_sinefre;
	
		float current_bias;
		float current_sinep2p;
		float current_sinefre;
	
		uint16_t Dad5660;
		unsigned char Had5660 [3];
		uint32_t Dad9834;
		uint16_t Had9834 [2];
};

extern Vcsel vcsel;
#endif
