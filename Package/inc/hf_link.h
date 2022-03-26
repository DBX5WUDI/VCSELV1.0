#ifndef HF_LINK_H
#define HF_LINK_H


#include "xm_abstract.h"

#include "board_controller.h"
#include "string.h"

#define HF_LINK_NODE_MODEL 0
static const unsigned short int MESSAGE_BUFER_SIZE = 120;

typedef struct HFMessage
{
    unsigned char 		sender_id;
    unsigned char 		receiver_id;
    unsigned short int 	length;
    unsigned char 		data[MESSAGE_BUFER_SIZE];
}HFMessage;

enum Recstate
{
    WAITING_FF1,
    WAITING_FF2,
    SENDER_ID,
    RECEIVER_ID,
    RECEIVE_LEN_H,
    RECEIVE_LEN_L,
    RECEIVE_PACKAGE,
    RECEIVE_CHECK
};

enum Command
{
    SHAKING_HANDS,		SET_VCSEL_BIAS,		SET_VCSEL_SINEP2P,	SET_VCSEL_SINEFRE,	READ_PD ,LAST_COMMAND_FLAG		
};

class HFLink
{
	public:
		HFLink(Xm_Abstract* xm_robot_)
		{
 			hf_link_node_model = HF_LINK_NODE_MODEL ;	
			my_id = 0x11 ;
			friend_id = 0x01 ;
			xm_robot = xm_robot_ ;
			shaking_hands_state=0;
			receive_state_=WAITING_FF1;
			command_state_=SHAKING_HANDS;
			
		    rx_message_.sender_id=0;
			rx_message_.receiver_id=0;
			rx_message_.length=0;
			tx_message_.sender_id=0;
			tx_message_.receiver_id=0;
			tx_message_.length=0;		
			
			receive_message_count=0;
			receive_package_count=0;
			
			tx_buffer[0]=0;		
			tx_buffer_length=0;				
		}
		unsigned char receive_package_renew[LAST_COMMAND_FLAG];
	/******************************************************************************/
	public:
		unsigned char byteAnalysisCall 	(const unsigned char rx_byte);
	/******************************************************************************/
	private:
		Xm_Abstract* 	xm_robot;
		Recstate   		receive_state_;
	    Command    		command_state_;
		HFMessage 		rx_message_ , tx_message_;
	    unsigned char 	my_id;
		unsigned char 	friend_id;
		unsigned char 	shaking_hands_state;
		unsigned char   hf_link_node_model;
	    unsigned char 	tx_buffer[MESSAGE_BUFER_SIZE];
		short int		byte_count_;
		short int		tx_buffer_length;
		short int 		receive_message_count;
		short int 		receive_package_count;
		short int 		receive_message_length_;
	    unsigned int	receive_check_sum_;	
	/******************************************************************************/
	private:
		void sendMessage(void);
		void sendSignal (unsigned char signal);
		void sendBuffer (unsigned char* buffer, unsigned short int size);
		void sendStruct (const Command command_state , unsigned char* p , const unsigned short int len);
		unsigned char packageAnalysis(void);	    
		unsigned char receiveFiniteStates(const unsigned char rx_data);	
		unsigned char setCommandAnalysis (const Command command_state , unsigned char* p , const unsigned short int len);
		unsigned char readCommandAnalysis(const Command command_state , unsigned char* p , const unsigned short int len);

};

#endif
