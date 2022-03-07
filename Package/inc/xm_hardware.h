#ifndef XM_HARDWARE_H
#define XM_HARDWARE_H
#include "queue.h"
#include "hf_link.h"
#include "vcsel.h"
class Xm_Hardware
{
	public:
		Xm_Hardware()
		{
		
		}
		void xmHardwareInit   (void);
		void xmHardwareTopCall(void);

	private:
		
		struct
		{
			float  m1;
			float  m2;
			float  m3;
		}d_motor_len_filter_ ;
		
		void vcselBiasControl	(void);
		void vcselSinep2pControl(void);
		void vcselSinefreControl(void);
		
};
extern Queue queue;
extern Xm_Abstract xm_robot;
extern Xm_Hardware xm_hardware;
extern HFLink hf_link_pc_node;
extern Board_controller board_controller;
extern HFLink *hf_link_node_pointer;

#endif
