#ifndef __UART1_Mast_Variables_H
#define __UART1_Mast_Variables_H
#ifdef __cplusplus
 extern "C" {
#endif


   // variables related to UART1_Rec_Transmission
#include "main.h"
//  extern __IO unsigned char UART1_recvdata[250];

#define U1Mast_Ack_Wait_Time 1000
#define U1Mast_App_Ack_Fail_Num_Limit 10
//#define U1Mast_App_Ack_Fail_Num_Limit 10
//  extern const uint8_t UART1_crcTable[256];
 
  struct U1_Mast_App_Rec_Flags{

	    __IO unsigned Received_Message_m : 1;
	    __IO unsigned Received_Message_s : 1;
	    __IO unsigned Received_Message_c : 1;
	    __IO unsigned Received_Message_c_again : 1;
	    __IO unsigned Received_Message_r : 1;

  };

  extern struct U1_Mast_App_Rec_Flags U1Mast_App_Rec_Flags;

  struct  U1_Mast_App_Rec_Var {

  };

  extern struct U1_Mast_App_Rec_Var U1Mast_App_Rec_Var;

   
#define UART1_Enable_Receive_Interrupt  USART2->CR1|=LL_USART_CR1_RXNEIE
#define UART1_Enable  USART2->CR1|=USART_CR1_UE
#define UART1_Transmit_Not_Complete !(USART2->ISR&LL_USART_ISR_TC)
#define UART1_Clear_Receive_Flag USART2->CR1|=USART_RQR_RXFRQ
#define UART1_Clear_Overflow_Flag USART2->ICR|=USART_ICR_ORECF
#define UART1_Rec_Data_Register USART2->RDR
#define UART1_Disable_Recv_INT USART2->CR1&=(~LL_USART_CR1_RXNEIE)




//UART1 variables related to message sending


// extern __IO unsigned char UART1_Txdata[90];

 struct U1_Mast_App_Send_Flags {

	  __IO unsigned Meterng_Communication_eror;
	  __IO unsigned Setting_Communication_eror;
	  __IO unsigned Calib_Communication_eror;

 };
 
 extern struct U1_Mast_App_Send_Flags U1Mast_App_Send_Flags;


 struct U1_Mast_App_Send_Var {
    __IO int32_t Ack_Wait_Time_cntr;
    __IO uint8_t Ack_Fail_Num;

 };
  
 extern struct U1_Mast_App_Send_Var U1Mast_App_Send_Var;

   
      #define UART1_Send_Ack_Wait_Time_Limit 30000 // these many counts of interrupt time length
      #define UART1_Transmit_Data_register USART2->TDR
      #define UART1_TRx_Complete (USART2->ISR&0x00000040)
      #define UART1_Expected_Ack_for_msg_A '0'
      #define UART1_Send_Number_of_Msg_types 1 //if A ,B, C and X are the message types possible then this will be 4

     
 extern volatile uint16_t V_INV_Ref;

extern volatile uint16_t V_INV_UL ;
extern volatile uint16_t V_INV_LL ;

extern volatile uint16_t V_Batt_H_Cutoff;
extern volatile uint16_t V_Batt_H_Cutin ;

extern volatile uint16_t V_Batt_L_Cutin ;
extern volatile uint16_t V_Batt_L_Cutoff;

extern volatile uint16_t I_Inv_Full_Load;

extern  volatile uint16_t Relay_Off_Time;
extern  volatile uint16_t Relay_On_Time;

extern  volatile uint16_t I_grid_Export_Limit;
extern  volatile uint16_t I_grid_Import_Limit;

extern  volatile uint16_t PV_H_Cutoff ;
extern  volatile uint16_t PV_H_Cutin ;

 extern volatile uint16_t PV_L_Cutin ;
extern  volatile uint16_t PV_L_Cutoff;

extern  volatile uint16_t I_PV_UL ;

extern  volatile uint16_t V_Mains_H_Cutoff; //calculate
extern  volatile uint16_t V_Mains_H_Cutin ;

extern  volatile uint16_t V_Mains_L_Cutoff;
extern  volatile uint16_t V_Mains_L_Cutin ;

extern  volatile uint16_t PV_Power_Limit;

      
#ifdef __cplusplus
}
#endif
#endif //__UART1_Mast_Variables_H
