#include "vcsel.h"

Vcsel vcsel;
/*set vcsel's current bias value*/
void Vcsel::set_vcsel_bias(float value)
{
	voltage_bias = value ;
	Dad5660 = DAD5660FULL * voltage_bias / 5;
	Had5660[2] = 0x00;
    Had5660[1] = (unsigned char)( Dad5660 >> 8);	//high bit
    Had5660[0] = (unsigned char)  Dad5660;			//low  bit
	
	board_controller.SPI1SendBuffer(Had5660,3);
}
/*set vcsel's sine wave's peak-to-peak value */
void Vcsel::set_vcsel_sinep2p(float value)
{
	voltage_sinep2p = value ;
	Dad5660 = DAD5660FULL * voltage_sinep2p / 5;
	Had5660[2] = 0x00;
    Had5660[1] = (unsigned char)( Dad5660 >> 8);	//high bit
    Had5660[0] = (unsigned char)  Dad5660;			//low  bit
	
	board_controller.SPI2SendBuffer(Had5660,3);	
}
/*set vcsel's sine wave's frequency value */
void Vcsel::set_vcsel_sinefre(float value)
{
	Dad9834 = (uint32_t)value*AD9834FRERATIO;
	Had9834[0] = (uint16_t)Dad9834;
	Had9834[0] = Had9834[0]&0x3FFF;
	Had9834[0] = Had9834[0]+0x4000;
	Had9834[1] = (uint16_t)(Dad9834>>14);
	Had9834[1] = Had9834[1]&0x3FFF;
	Had9834[1] = Had9834[1]+0x4000;
	
	board_controller.SPI3SendUSInt(0x2100);
	board_controller.SPI3SendUSInt(Had9834[0]);
	board_controller.SPI3SendUSInt(Had9834[1]);	
	
//	board_controller.SPI3SendUSInt(0x51EF); 		//standard 10kHz
//	board_controller.SPI3SendUSInt(0x4003);
	board_controller.SPI3SendUSInt(0x0000);
}


