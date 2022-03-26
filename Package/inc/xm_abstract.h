#ifndef XM_ABSTRACT_H
#define XM_ABSTRACT_H


struct MSGCoord
{
    float  x;
    float  y;
    float  z;
};

class Xm_Abstract
{
	public:
    Xm_Abstract()
    {

	}
	/*************************************classic*************************************/
		MSGCoord   measure_global_coordinate; 	
		unsigned short int measure_light_intensity;	//measure VCSEL light intensity 
		float vcsel_bias_value;			//VCSEL DC bias voltage
		float vcsel_sinep2p_value; 		//VCSEL AC sine wave's peak-to-peak value voltage
		float vcsel_sinefre_value;		//VCSEL AC sine wave's frequency

};
extern Xm_Abstract xm_robot;
#endif
