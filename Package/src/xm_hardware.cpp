/**************************************************************************/
/* This file is used to control the modules of total posture of the robot */
/**************************************************************************/

#include "xm_hardware.h"

Xm_Abstract xm_robot;
Xm_Hardware xm_hardware;
/*robot hardware initialization*/
void Xm_Hardware::xmHardwareInit(void)
{
	photodetector.DMAEnable();
}
/*the hardware update, port to main loop body*/
void Xm_Hardware::xmHardwareTopCall(void)
{
	vcselBiasControl();
	vcselSinep2pControl();
	vcselSinefreControl();
	measureDataUpdate();
}	
/*control VCSEL's bias current value*/
void Xm_Hardware::vcselBiasControl(void)    
{
	if( hf_link_node_pointer->receive_package_renew[SET_VCSEL_BIAS]==1)
	{
		hf_link_node_pointer->receive_package_renew[SET_VCSEL_BIAS]=0;
		vcsel.set_vcsel_bias(xm_robot.vcsel_bias_value);
	}		
}
/*control VCSEL's modulation current peak-to-peak value*/
void Xm_Hardware::vcselSinep2pControl(void)    
{
	if( hf_link_node_pointer->receive_package_renew[SET_VCSEL_SINEP2P]==1)
	{
		hf_link_node_pointer->receive_package_renew[SET_VCSEL_SINEP2P]=0;
		vcsel.set_vcsel_sinep2p(xm_robot.vcsel_sinep2p_value);
	}		
}
/*control VCSEL's modulation current frequency value*/
void Xm_Hardware::vcselSinefreControl(void)    
{
	if( hf_link_node_pointer->receive_package_renew[SET_VCSEL_SINEFRE]==1)
	{
		hf_link_node_pointer->receive_package_renew[SET_VCSEL_SINEFRE]=0;
		vcsel.set_vcsel_sinefre(xm_robot.vcsel_sinefre_value);
	}		
}

void Xm_Hardware::measureDataUpdate(void)
{
	xm_robot.measure_light_intensity = photodetector.read_pd();
}
