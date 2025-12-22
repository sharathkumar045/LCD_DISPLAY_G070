
/*
 * UART_Communication_Functions.c
 *
 *  Created on: Apr 19, 2019
 *      Author: krishna
 */

#include "UART1_Mast_Drv_Functions.h"
#include "usart.h"
#include "UART1_Mast_Drv_Variables.h"
#include "UART1_Mast_App_Functions.h"
#include "UART1_Mast_App_Variables.h"




unsigned char U1Mast_Drv_crcFast(unsigned char message[],unsigned int nbyte)
{
   unsigned char  data,remainder =0;
   unsigned int  byte;

    for (byte = 0; byte < nbyte; ++byte)
    {
       data =(message[byte]) ^ (remainder);
       remainder = UART1_crcTable[data] ^ (message[byte] << 8);

    }
     return (remainder);
}

void U1Mast_Drv_Receive_ISR_Program(void)
{
	U1Mast_Drv_Rec_Var.recdata = UART1_Rec_Data_Register;

      if(U1Mast_Drv_Rec_Flags.busy_flag==0)
      {
         if(U1Mast_Drv_Rec_Var.recdata=='m' && U1Mast_Drv_Rec_Flags.recv_check==0)//for factory set if data received as T
         {
            U1Mast_Drv_Rec_Flags.recv_check=1;
            U1Mast_Drv_Rec_Var.Array_Index=0;
            UART1_recvdata[U1Mast_Drv_Rec_Var.Array_Index]=U1Mast_Drv_Rec_Var.recdata; //SAVE RECEIVE DATA IN FACTORY SET ARRAY
         }
         else if((U1Mast_Drv_Rec_Flags.recv_check==1) && U1Mast_Drv_Rec_Var.Array_Index<43 && UART1_recvdata[0]=='m')
         {
            U1Mast_Drv_Rec_Var.Array_Index++;
            UART1_recvdata[U1Mast_Drv_Rec_Var.Array_Index]=U1Mast_Drv_Rec_Var.recdata;
         }
         
         ///////////////////////////////////////////////////////////////////////////////////////////////
         else if(U1Mast_Drv_Rec_Var.recdata=='s' && U1Mast_Drv_Rec_Flags.recv_check==0)//for factory set if data received as T
         {
            U1Mast_Drv_Rec_Flags.recv_check=1;
            U1Mast_Drv_Rec_Var.Array_Index=0;

            UART1_recvdata[U1Mast_Drv_Rec_Var.Array_Index]=U1Mast_Drv_Rec_Var.recdata; //SAVE RECEIVE DATA IN FACTORY SET ARRAY
         }
         else if((U1Mast_Drv_Rec_Flags.recv_check==1) && U1Mast_Drv_Rec_Var.Array_Index<1 && UART1_recvdata[0]=='s')
         {
            U1Mast_Drv_Rec_Var.Array_Index++;
            UART1_recvdata[U1Mast_Drv_Rec_Var.Array_Index]=U1Mast_Drv_Rec_Var.recdata;
         }
         
         ///////////////////////////////////////////////////////////////////////////////////////////////
         
         else if(U1Mast_Drv_Rec_Var.recdata=='c' && U1Mast_Drv_Rec_Flags.recv_check==0)//for factory set if data received as T
         {
            U1Mast_Drv_Rec_Flags.recv_check=1;
            U1Mast_Drv_Rec_Var.Array_Index=0;
            UART1_recvdata[U1Mast_Drv_Rec_Var.Array_Index]=U1Mast_Drv_Rec_Var.recdata; //SAVE RECEIVE DATA IN FACTORY SET ARRAY
         }
         else if((U1Mast_Drv_Rec_Flags.recv_check==1) && U1Mast_Drv_Rec_Var.Array_Index<19 && UART1_recvdata[0]=='c')
         {
            U1Mast_Drv_Rec_Var.Array_Index++;
            UART1_recvdata[U1Mast_Drv_Rec_Var.Array_Index]=U1Mast_Drv_Rec_Var.recdata;
         }
         
         ///////////////////////////////////////////////////////////////////////////////////////////////
         
         
         else if(U1Mast_Drv_Rec_Var.recdata=='r' && U1Mast_Drv_Rec_Flags.recv_check==0)//for factory set if data received as T
         {
            U1Mast_Drv_Rec_Flags.recv_check=1;
            U1Mast_Drv_Rec_Var.Array_Index=0;
            UART1_recvdata[U1Mast_Drv_Rec_Var.Array_Index]=U1Mast_Drv_Rec_Var.recdata; //SAVE RECEIVE DATA IN FACTORY SET ARRAY
         }
         else if((U1Mast_Drv_Rec_Flags.recv_check==1) && U1Mast_Drv_Rec_Var.Array_Index<1 && UART1_recvdata[0]=='r')
         {
            U1Mast_Drv_Rec_Var.Array_Index++;
            UART1_recvdata[U1Mast_Drv_Rec_Var.Array_Index]=U1Mast_Drv_Rec_Var.recdata;
         }
         //////////////////////////////////////////////////////////////////////////////////////////////
         else if(U1Mast_Drv_Rec_Var.recdata=='a' && U1Mast_Drv_Rec_Flags.recv_check==0)//for factory set if data received as T
         {
            U1Mast_Drv_Rec_Flags.recv_check=1;
            U1Mast_Drv_Rec_Var.Array_Index=0;
            UART1_recvdata[U1Mast_Drv_Rec_Var.Array_Index]=U1Mast_Drv_Rec_Var.recdata; //SAVE RECEIVE DATA IN FACTORY SET ARRAY
         }
         else if((U1Mast_Drv_Rec_Flags.recv_check==1) && U1Mast_Drv_Rec_Var.Array_Index<4 && UART1_recvdata[0]=='a')
         {
            U1Mast_Drv_Rec_Var.Array_Index++;
            UART1_recvdata[U1Mast_Drv_Rec_Var.Array_Index]=U1Mast_Drv_Rec_Var.recdata;
         }
         ///////////////////////////////////////////////////////////////////////////////////////////////
         else if(U1Mast_Drv_Rec_Var.recdata=='g' && U1Mast_Drv_Rec_Flags.recv_check==0)//for factory set if data received as T
         {
            U1Mast_Drv_Rec_Flags.recv_check=1;
            U1Mast_Drv_Rec_Var.Array_Index=0;
            UART1_recvdata[U1Mast_Drv_Rec_Var.Array_Index]=U1Mast_Drv_Rec_Var.recdata; //SAVE RECEIVE DATA IN FACTORY SET ARRAY
         }
         else if((U1Mast_Drv_Rec_Flags.recv_check==1) && U1Mast_Drv_Rec_Var.Array_Index<3 && UART1_recvdata[0]=='g')
         {
            U1Mast_Drv_Rec_Var.Array_Index++;
            UART1_recvdata[U1Mast_Drv_Rec_Var.Array_Index]=U1Mast_Drv_Rec_Var.recdata;
         }
         
        ///////////////////////////////////////////////////////////////////////////////////////////////

      }


      UART1_Clear_Receive_Flag;
      UART1_Clear_Overflow_Flag;
  
    }

void U1Mast_Drv_Send_Function_Inside_Timer_Interrupt(void) ///put this code in timer interrupt which is called every 200uS or so
{
   if((U1Mast_Drv_Send_Flags.Send_Enable==1)&&(UART1_TRx_Complete))
    {
      if(U1Mast_Drv_Send_Var.Array_Index<U1Mast_Drv_Send_Var.Msg_Length)
         {
           UART1_Transmit_Data_register=UART1_Txdata[U1Mast_Drv_Send_Var.Array_Index];
           U1Mast_Drv_Send_Var.Array_Index= U1Mast_Drv_Send_Var.Array_Index+1;
         }
      else
         {    

           U1Mast_Drv_Send_Flags.Send_Enable=0;//now one can populate need data into transmit register
         }
    }   
 }

void U1Mast_Drv_Variables_Init(void)
{

	U1Mast_Drv_Rec_Flags.busy_flag=0;
	U1Mast_Drv_Rec_Flags.recv_check=0;

	U1Mast_Drv_Rec_Var.Array_Index=0;
	U1Mast_Drv_Rec_Var.U1_CRC=0;
	U1Mast_Drv_Rec_Var.recdata=0;

	U1Mast_Drv_Send_Flags.Send_Enable=0;

	U1Mast_Drv_Send_Var.Array_Index=0;
	U1Mast_Drv_Send_Var.Msg_Length=0;

}
