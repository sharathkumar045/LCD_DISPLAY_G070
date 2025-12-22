#ifndef __UART1_Mast_Drv_Variables_H
#define __UART1_Mast_Drv_Variables_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32g0xx.h"
#include "string.h"
   // variables related to UART1_Rec_Transmission
    
  extern __IO unsigned char UART1_recvdata[250];
  extern const uint8_t UART1_crcTable[256];
 
  struct U1_Mast_Drv_Rec_Flags{

	    __IO unsigned recv_check: 1;
	    __IO unsigned busy_flag : 1;
  };

  extern struct U1_Mast_Drv_Rec_Flags U1Mast_Drv_Rec_Flags; //UART1_Mast_Rec_Flags;

  struct  U1_Mast_Drv_Rec_Var {
     __IO char recdata; //note that that this different from recvdata[] array
     __IO uint8_t U1_CRC;
     __IO uint32_t Array_Index;

  };

  extern struct U1_Mast_Drv_Rec_Var U1Mast_Drv_Rec_Var;  //UART1_Mast_Rec_Var;

   
#define UART1_Enable_Receive_Interrupt  USART2->CR1|=USART_CR1_RXNEIE_RXFNEIE
#define UART1_Enable  USART2->CR1|=USART_CR1_UE
#define UART1_Transmit_Not_Complete !(USART2->ISR&LL_USART_ISR_TC)
#define UART1_Clear_Receive_Flag USART2->CR1|=USART_RQR_RXFRQ
#define UART1_Clear_Overflow_Flag USART2->ICR|=USART_ICR_ORECF
#define UART1_Rec_Data_Register USART2->RDR
#define UART1_Disable_Recv_INT USAR2->CR1&=(~LL_USART_CR1_RXNEIE)




//UART1 variables related to message sending


 extern  __IO unsigned char UART1_Txdata[90];

 struct U1_Mast_Drv_Send_Flags{

	  __IO unsigned Send_Enable:1;


 };
 
 extern struct U1_Mast_Drv_Send_Flags U1Mast_Drv_Send_Flags;//UART1_Mast_Send_Flags;


 struct U1_Mast_Drv_Send_Var{

    __IO uint16_t Array_Index;
    __IO uint16_t Msg_Length;

 };
  
 struct UART1_Master_Ctrl_Struct
 {
 	volatile uint32_t UART_Busy_Flag_Timeout_Cntr;
 	volatile uint8_t UART_Busy_Flag;
 	volatile uint32_t UART_Recv_Timeout_Cntr;
 	volatile uint8_t Expected_Ans;
 	volatile uint8_t Expected_Ans_Recvd_Flag;
 	volatile uint16_t Send_Index;
 	volatile uint16_t Send_Msg_Len;
 	volatile uint8_t Send_Enable;
 	volatile uint8_t Recv_Flag;
 	volatile uint32_t Resend_Delay_Cntr;
 	volatile uint8_t Recv_Eror_Flag;
 	volatile uint16_t Metering_Rq_Resend_Cntr;
 };

 extern struct UART1_Master_Ctrl_Struct UART1_Master_Ctrl;


 extern struct U1_Mast_Drv_Send_Var U1Mast_Drv_Send_Var; //UART1_Mast_Send_Var;

   
      #define UART1_Transmit_Data_register USART->TDR
      #define UART1_TRx_Complete (USART2->ISR&0x00000040)



      
      
#ifdef __cplusplus
}
#endif
#endif //__UART1_Mast_Drv_Variables_H
