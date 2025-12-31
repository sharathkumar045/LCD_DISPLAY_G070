
/*
 * UART_Communication_Functions.c
 *
 *  Created on: Apr 19, 2019
 *      Author: krishna
 */

#include "usart.h"
#include "UART1_Mast_App_Functions.h"
#include "UART1_Mast_App_Variables.h"

#include "UART1_Mast_Drv_Functions.h"
#include "UART1_Mast_Drv_Variables.h"

#include "Main_Functions.h"
#include "Main_Variables.h"

#include "Display_App_Variables.h"
#include "Display_App_Functions.h"


void Whileloop_Metering_Data_Rq_Fn(void)
{
	//Display(Syncing)
	if (Disp_Cntrl.First_Time_State_Entry==1)
	{
		U1Mast_App_Rec_Flags.Received_Message_m =0;
		U1Mast_App_Send_Var.Ack_Fail_Num=0;
		U1Mast_App_Send_Flags.Meterng_Communication_eror=0;
		U1Mast_Drv_Send_Flags.Send_Enable=0;

//		Populate array_with_M;
		U1Mast_App_Populate_And_Send_Txdata_Array_With_Message_Request_Metering();
		U1Mast_App_Send_Var.Ack_Wait_Time_cntr=U1Mast_Ack_Wait_Time; // 1 seconds ; This time includes sending and receiving both so calculate appropriately

		Disp_Cntrl.First_Time_State_Entry=0;
	}

	if (	Disp_Cntrl.First_Time_State_Entry==0)
	{
		if((U1Mast_App_Send_Var.Ack_Wait_Time_cntr==0)&&(U1Mast_App_Rec_Flags.Received_Message_m==0)&&(U1Mast_Drv_Send_Flags.Send_Enable==0))
		{
			U1Mast_Drv_Send_Var.Array_Index=0;
			U1Mast_Drv_Send_Flags.Send_Enable=1;
			U1Mast_App_Send_Var.Ack_Wait_Time_cntr=U1Mast_Ack_Wait_Time;
			U1Mast_App_Send_Var.Ack_Fail_Num = U1Mast_App_Send_Var.Ack_Fail_Num + 1;
		}

		if(U1Mast_App_Rec_Flags.Received_Message_m==1)
		{
//			State = Disp_Cntrl.Prev_State;
			State = RTC_Disp_Time_Date;
			Metering_Rq_Data_State_Disp_Fn();
			Disp_Cntrl.First_Time_State_Entry=1;
		}

		if(U1Mast_App_Send_Var.Ack_Fail_Num>=U1Mast_App_Ack_Fail_Num_Limit)
		{
			//State = Disp_Cntrl.Prev_State;
			State = Error;
			Disp_Cntrl.First_Time_State_Entry=1;
			U1Mast_App_Send_Flags.Meterng_Communication_eror=1;
		}
	}
}

void U1Mast_App_Populate_And_Send_Txdata_Array_With_Message_Request_Metering(void)
{
	U1Mast_Drv_Send_Var.Msg_Length=2; //M and crc

	UART1_Txdata[0]='M';
	UART1_Txdata[1]=U1Mast_Drv_crcFast(UART1_Txdata,U1Mast_Drv_Send_Var.Msg_Length-1);

	U1Mast_Drv_Send_Var.Array_Index=0;
	U1Mast_Drv_Send_Flags.Send_Enable=1;
}

void Whileloop_Setting_Send_Data_Fn(void)
{
	if(Disp_Cntrl.First_Time_State_Entry == 1)
	{
		U1Mast_App_Rec_Flags.Received_Message_s =0;
		U1Mast_App_Send_Var.Ack_Fail_Num=0;
		U1Mast_App_Send_Flags.Meterng_Communication_eror=0;
		U1Mast_Drv_Send_Flags.Send_Enable=0;

		//		Populate array_with_S;
//		U1Mast_App_Populate_And_Send_Txdata_Array_With_Message_Settings();
		Display_to_Inverter();
		U1Mast_App_Send_Var.Ack_Wait_Time_cntr=U1Mast_Ack_Wait_Time; // 1 seconds ; This time includes sending and receiving both so calculate appropriately

		Disp_Cntrl.First_Time_State_Entry = 0;
	}
	if(Disp_Cntrl.First_Time_State_Entry == 0)
	{

		if((U1Mast_App_Send_Var.Ack_Wait_Time_cntr==0)&&(U1Mast_App_Rec_Flags.Received_Message_s==0)&&(U1Mast_Drv_Send_Flags.Send_Enable==0))
		{
			U1Mast_Drv_Send_Var.Array_Index=0;
			U1Mast_Drv_Send_Flags.Send_Enable=1;
			U1Mast_App_Send_Var.Ack_Wait_Time_cntr=U1Mast_Ack_Wait_Time;
			U1Mast_App_Send_Var.Ack_Fail_Num = U1Mast_App_Send_Var.Ack_Fail_Num + 1;
		}

		if(U1Mast_App_Rec_Flags.Received_Message_s==1)
		{
		//			State = Disp_Cntrl.Prev_State;

			Settings_Send_Data_State_Disp_Fn();
			State = Metering_Data_Rq;
			Disp_Cntrl.First_Time_State_Entry=1;
		}
/////////////////////////////////////
		if(U1Mast_App_Send_Var.Ack_Fail_Num>=U1Mast_App_Ack_Fail_Num_Limit)
		{
			//State = Disp_Cntrl.Prev_State;
			State = Error;
			Disp_Cntrl.First_Time_State_Entry=1;

			U1Mast_App_Send_Flags.Setting_Communication_eror=1;
		}
	}
}

void Display_to_Inverter(){
	U1Mast_Drv_Send_Var.Msg_Length=50;
	U1Mast_Drv_Send_Flags.Send_Enable=1;

			UART1_Txdata[0] = 'S';

//			UART1_Txdata[1]=(0x00FF & 1831);
//			UART1_Txdata[2]=((0xFF00 & 1831)>>8);

			UART1_Txdata[1] = (V_INV_Ref & 0x00FF);
			UART1_Txdata[2] = (V_INV_Ref  & 0x00FF) >>8;
//
			UART1_Txdata[3] = (V_INV_UL  & 0x00FF);
			UART1_Txdata[4] = (V_INV_UL & 0x00FF) >> 8 ;
//
			UART1_Txdata[6] = (V_INV_LL) & 0x00FF;
			UART1_Txdata[5] = (V_INV_LL & 0x00FF) >> 8 ;

			UART1_Txdata[7] = (V_Batt_H_Cutoff ) & 0x00FF;
			UART1_Txdata[8] = (V_Batt_H_Cutoff & 0x00FF)>> 8 ;
//
			UART1_Txdata[9] = (V_Batt_H_Cutin ) & 0x00FF;
			UART1_Txdata[10] = (V_Batt_H_Cutin & 0x00FF) >> 8 ;

			UART1_Txdata[11] = (V_Batt_L_Cutin) & 0x00FF;
			UART1_Txdata[12] = (V_Batt_L_Cutin  & 0x00FF) >>8;

			UART1_Txdata[13] = (V_Batt_L_Cutoff) & 0x00FF;
			UART1_Txdata[14] = (V_Batt_L_Cutoff & 0x00FF) >> 8 ;

			UART1_Txdata[15] = (I_Inv_Full_Load ) & 0x00FF;
			UART1_Txdata[16] = (I_Inv_Full_Load & 0x00FF )>> 8 ;

			UART1_Txdata[17] = (Relay_Off_Time) & 0x00FF;
			UART1_Txdata[18] = (Relay_Off_Time>> 8) & 0x00FF;

			UART1_Txdata[19] = (Relay_On_Time ) & 0x00FF;
			UART1_Txdata[20] = (Relay_On_Time & 0x00FF) >> 8 ;

			UART1_Txdata[21] = (I_grid_Export_Limit ) & 0x00FF;
			UART1_Txdata[22] = (I_grid_Export_Limit & 0x00FF) >> 8 ;

			UART1_Txdata[23] = (I_grid_Import_Limit) & 0x00FF;
			UART1_Txdata[24] = (I_grid_Import_Limit & 0x00FF)>>8 ;

			UART1_Txdata[25] = (PV_H_Cutoff) & 0x00FF;
			UART1_Txdata[26] = (PV_H_Cutoff & 0x00FF)>>8 ;

			UART1_Txdata[27] = (PV_H_Cutin ) & 0x00FF;
			UART1_Txdata[28] = (PV_H_Cutin & 0x00FF)>> 8 ;

			UART1_Txdata[29] = (PV_L_Cutin ) & 0x00FF;
			UART1_Txdata[30] = (PV_L_Cutin & 0x00FF) >> 8 ;

			UART1_Txdata[31] = (PV_L_Cutoff ) & 0x00FF;
			UART1_Txdata[32] = (PV_L_Cutoff  & 0x00FF)>> 8;

			UART1_Txdata[33] = (I_PV_UL ) & 0xFF;
			UART1_Txdata[34] = (I_PV_UL & 0x00FF) >> 8;

			UART1_Txdata[35] = (V_Mains_H_Cutoff ) &0x00FF;
			UART1_Txdata[36] = (V_Mains_H_Cutoff &0x00FF)>> 8 ;

			UART1_Txdata[37] = (V_Mains_H_Cutin  ) & 0x00FF;
			UART1_Txdata[38] = (V_Mains_H_Cutin & 0x00FF)>> 8  ;

			UART1_Txdata[39] = (V_Mains_L_Cutin ) & 0x00FF;
			UART1_Txdata[40] = (V_Mains_L_Cutin & 0x00FF) >> 8;

			UART1_Txdata[41] = (V_Mains_L_Cutoff ) & 0x00FF;
			UART1_Txdata[42] = (V_Mains_L_Cutoff & 0x00FF)>> 8  ;

			UART1_Txdata[43] = (PV_Power_Limit ) & 0x00FF;
			UART1_Txdata[44] = (PV_Power_Limit & 0x00FF)>> 8 ;

			UART1_Txdata[45] = 0 ;
			UART1_Txdata[46] = 0 ;
			UART1_Txdata[47] = 0 ;
			UART1_Txdata[48] = 0 ;

			UART1_Txdata[49] = U1Mast_Drv_crcFast(UART1_Txdata, 49);

			U1Mast_Drv_Send_Var.Array_Index=0;


}
void U1Mast_App_Populate_And_Send_Txdata_Array_With_Message_Settings(void)
{
		UART1_Txdata[0] = 'S';

//		__IO uint8_t j = 1;
//		for(int i =1 ; i<79 ; i = i+2)
//		{
//			UART1_Txdata[i]=(0x00FF & Disp_New_Setting_Value[j]);
//			UART1_Txdata[i+1]=((0xFF00 & Disp_New_Setting_Value[j])>>8);
//			j = j+1;
//		}
		UART1_Txdata[1]=(0x00FF & 1831);
		UART1_Txdata[2]=((0xFF00 & 1831)>>8);

		UART1_Txdata[3]=(0x00FF & 2165);
		UART1_Txdata[4]=((0xFF00 & 2165)>>8);

		UART1_Txdata[5]=(0x00FF & 1337);
		UART1_Txdata[6]=((0xFF00 & 1337)>>8);

		UART1_Txdata[7]=(0x00FF & 2765);
		UART1_Txdata[8]=((0xFF00 & 2765)>>8);

		UART1_Txdata[9]=(0x00FF & 3519);
		UART1_Txdata[10]=((0xFF00 & 3519)>>8);

		UART1_Txdata[11]=(0x00FF & 3368);
		UART1_Txdata[12]=((0xFF00 & 3368)>>8);

		UART1_Txdata[13]=(0x00FF & 2162);
		UART1_Txdata[14]=((0xFF00 & 2162)>>8);

		UART1_Txdata[15]=(0x00FF & 2011);
		UART1_Txdata[16]=((0xFF00 & 2011)>>8);

		UART1_Txdata[17]=(0x00FF & 2458);
		UART1_Txdata[18]=((0xFF00 & 2458)>>8);

		UART1_Txdata[19]=(0x00FF & 1639);
		UART1_Txdata[20]=((0xFF00 & 1639)>>8);

		UART1_Txdata[21]=(0x00FF & 1803);
		UART1_Txdata[22]=((0xFF00 & 1803)>>8);

		UART1_Txdata[23]=(0x00FF & 2049);
		UART1_Txdata[24]=((0xFF00 & 2049)>>8);

        UART1_Txdata[25]=(0x00FF & 2459);
        UART1_Txdata[26]=((0xFF00 & 2459)>>8);

		UART1_Txdata[27]=(0x00FF & 1950);
		UART1_Txdata[28]=((0xFF00 & 1950)>>8);

		UART1_Txdata[29]=(0x00FF & 1950);
		UART1_Txdata[30]=((0xFF00 & 1950)>>8);

		UART1_Txdata[31]=(0x00FF & 2527);
		UART1_Txdata[32]=((0xFF00 & 2527)>>8);

		UART1_Txdata[33]=(0x00FF & 2359);
		UART1_Txdata[34]=((0xFF00 & 2359)>>8);

		UART1_Txdata[35]=(0x00FF & 505);
		UART1_Txdata[36]=((0xFF00 & 505)>>8);

		UART1_Txdata[37]=(0x00FF & 421);
		UART1_Txdata[38]=((0xFF00 & 421)>>8);

		UART1_Txdata[39]=(0x00FF & 1622);
		UART1_Txdata[40]=((0xFF00 & 1622)>>8);

		UART1_Txdata[41]=(0x00FF & 2633);
		UART1_Txdata[42]=((0xFF00 & 2633)>>8);

		UART1_Txdata[43]=(0x00FF & 2535);
		UART1_Txdata[44]=((0xFF00 & 2535)>>8);

		UART1_Txdata[45]=(0x00FF & 1755);
		UART1_Txdata[46]=((0xFF00 & 1755)>>8);

		UART1_Txdata[47]=(0x00FF & 1560);
		UART1_Txdata[48]=((0xFF00 & 1560)>>8);

		UART1_Txdata[49]=(0x00FF & 2900);
		UART1_Txdata[50]=((0xFF00 & 2900)>>8);

		UART1_Txdata[51]=(0x00FF & 2500);
		UART1_Txdata[52]=((0xFF00 & 2500)>>8);

		UART1_Txdata[53]=(0x00FF & 0);
		UART1_Txdata[54]=((0xFF00 & 0)>>8);

		UART1_Txdata[55]=(0x00FF & 2000);
		UART1_Txdata[56]=((0xFF00 & 2000)>>8);

		UART1_Txdata[57]=(0x00FF & 1);
		UART1_Txdata[58]=((0xFF00 & 1)>>8);

		UART1_Txdata[59]=(0x00FF & 2500);
		UART1_Txdata[60]=((0xFF00 & 2500)>>8);

		UART1_Txdata[61]=(0x00FF & 2450);
		UART1_Txdata[62]=((0xFF00 & 2450)>>8);

		UART1_Txdata[63]=(0x00FF & 2500);
		UART1_Txdata[64]=((0xFF00 & 2500)>>8);

		UART1_Txdata[65]=(0x00FF & 2500);
		UART1_Txdata[66]=((0xFF00 & 2500)>>8);

        UART1_Txdata[67]=(0x00FF & 200);
        UART1_Txdata[68]=((0xFF00 & 200)>>8);

		UART1_Txdata[69]=(0x00FF & 100);
		UART1_Txdata[70]=((0xFF00 & 100)>>8);

		UART1_Txdata[71]=(0x00FF & 2500);
		UART1_Txdata[72]=((0xFF00 & 2500)>>8);

		UART1_Txdata[73]=(0x00FF & 2500);
		UART1_Txdata[74]=((0xFF00 & 2500)>>8);

		UART1_Txdata[75]=(0x00FF & 0);
		UART1_Txdata[76]=((0xFF00 & 0)>>8);

		UART1_Txdata[77]=(0x00FF & 0);
		UART1_Txdata[78]=((0xFF00 & 0)>>8);

		U1Mast_Drv_Send_Var.Msg_Length=80;//(0-26)for message and 27th location for CRC (total 28)
		UART1_Txdata[79] = U1Mast_Drv_crcFast((UART1_Txdata),(U1Mast_Drv_Send_Var.Msg_Length-1));

		//U1Mast_Drv_Send_Var.Msg_m=0;
		U1Mast_Drv_Send_Var.Array_Index=0;
		U1Mast_Drv_Send_Flags.Send_Enable=1;
}

void U1Mast_App_Populate_And_Send_Txdata_Array_With_Zeros_Calib(void)
{
	U1Mast_App_Rec_Flags.Received_Message_c =0;
	U1Mast_App_Send_Var.Ack_Fail_Num=0;
	U1Mast_App_Send_Flags.Meterng_Communication_eror=0;
	U1Mast_Drv_Send_Flags.Send_Enable=0;

	UART1_Txdata[0]='C';

	for (int  i = 1; i<21 ;i++)
	{
		UART1_Txdata[i] = 0;
	}
	U1Mast_Drv_Send_Var.Msg_Length=22; //M and crc
	UART1_Txdata[21]=U1Mast_Drv_crcFast(UART1_Txdata,U1Mast_Drv_Send_Var.Msg_Length-1);

	U1Mast_Drv_Send_Var.Array_Index=0;
	U1Mast_Drv_Send_Flags.Send_Enable=1;

}

void U1Mast_App_Populate_And_Send_Txdata_Array_With_Msg_Calib(void)
{
	U1Mast_App_Rec_Flags.Received_Message_c =0;
	U1Mast_App_Send_Var.Ack_Fail_Num=0;
	U1Mast_App_Send_Flags.Meterng_Communication_eror=0;
	U1Mast_Drv_Send_Flags.Send_Enable=0;


	U1Mast_Drv_Send_Var.Msg_Length=22; //M and crc

	UART1_Txdata[0]='C';


	UART1_Txdata[1] = (0xff & Calib_Value[1]);
	UART1_Txdata[2] = (0xff & Calib_Value[1])>>8;

	UART1_Txdata[3] = (0xff & Calib_Value[2]);
	UART1_Txdata[4] = (0xff & Calib_Value[2]) >>8;

	UART1_Txdata[5] = (0xff & Calib_Value[3]);
	UART1_Txdata[6] = (0xff & Calib_Value[3]) >>8;

	UART1_Txdata[7] = (0xff & Calib_Value[4]);
	UART1_Txdata[8] = (0xff & Calib_Value[4]) >>8;

	UART1_Txdata[9] = (0xff & Calib_Value[4]);
	UART1_Txdata[10] = (0xff & Calib_Value[4]) >>8;

	UART1_Txdata[11] = (0xff & Calib_Value[4]);
	UART1_Txdata[12] = (0xff & Calib_Value[4]) >>8;

//	UART1_Txdata[9] =  (Calib_Value[5]);
//	UART1_Txdata[10] = ( Calib_Value[5]>>8);
//
//	UART1_Txdata[11] = (uint8_t)(Calib_Value[6]);
//	UART1_Txdata[12] = (uint8_t)(Calib_Value[6]>>8);

	UART1_Txdata[13] = (0xff & Calib_Value[7]);
	UART1_Txdata[14] = (0xff & Calib_Value[7]) >>8;

	UART1_Txdata[15] = (0xff & Calib_Value[8]);
	UART1_Txdata[16] = (0xff & Calib_Value[8]) >>8;

	UART1_Txdata[17] = (0xff & Calib_Value[9]);
	UART1_Txdata[18] = (0xff & Calib_Value[9]) >>8;

	UART1_Txdata[19] = (0xff & Calib_Value[10]);
	UART1_Txdata[20] = (0xff & Calib_Value[10]) >>8;


	UART1_Txdata[21]=U1Mast_Drv_crcFast(UART1_Txdata,U1Mast_Drv_Send_Var.Msg_Length-1);

	U1Mast_Drv_Send_Var.Array_Index=0;
	U1Mast_Drv_Send_Flags.Send_Enable=1;

}

void U1Mast_App_Populate_And_Send_Txdata_Array_With_Msg_RESET(void)
{
	U1Mast_App_Rec_Flags.Received_Message_r =0;
	U1Mast_App_Send_Var.Ack_Fail_Num=0;
	U1Mast_App_Send_Flags.Meterng_Communication_eror=0;
	U1Mast_Drv_Send_Flags.Send_Enable=0;

	UART1_Txdata[0]='R';
	UART1_Txdata[1]='E';
	UART1_Txdata[2]='S';
	UART1_Txdata[3]='E';
	UART1_Txdata[4]='T';

	U1Mast_Drv_Send_Var.Msg_Length=6; //M and crc included
	UART1_Txdata[5]=U1Mast_Drv_crcFast(UART1_Txdata,U1Mast_Drv_Send_Var.Msg_Length-1);

	U1Mast_Drv_Send_Var.Array_Index=0;
	U1Mast_Drv_Send_Flags.Send_Enable=1;

}

void U1Mast_App_Store_Received_Data_In_Variables(void)
{
	U1Mast_App_Update_Variables_if_Mesage_is_m();
	U1Mast_App_Update_Variables_if_Mesage_is_S();
	U1Mast_App_Update_Variables_if_Mesage_is_c();
	U1Mast_App_Update_Variables_if_Mesage_is_r();

//    UART1_Update_Variables_if_Mesage_is_V();
//    UART1_Update_Variables_if_Mesage_is_W();

    //add functions for various messages
}

void U1Mast_App_Update_Variables_if_Mesage_is_m(void)
{
	if(UART1_recvdata[0]=='m' && U1Mast_Drv_Rec_Var.Array_Index==43)//for user set
	{
		U1Mast_Drv_Rec_Flags.busy_flag=1;
		U1Mast_Drv_Rec_Flags.recv_check=0;
		U1Mast_Drv_Rec_Var.U1_CRC = U1Mast_Drv_crcFast((UART1_recvdata),43);
		UART1_recvdata[0]=0;
		if(U1Mast_Drv_Rec_Var.U1_CRC == UART1_recvdata[43])
		{
			U1Mast_App_Use_Received_Data_m();

			U1Mast_App_Rec_Flags.Received_Message_m=1;  // this is different as compared to slave
			//  UART1_Msg_Send_Reqt_Flags.Msg_B=1;//send ack
			// UART1_Send_Flags.Msg_t=0

		}
		U1Mast_Drv_Rec_Flags.busy_flag=0;
	}
}     

void U1Mast_App_Update_Variables_if_Mesage_is_S(void)
{
	if(UART1_recvdata[0]=='s' && U1Mast_Drv_Rec_Var.Array_Index==1)//for user set
	{
		U1Mast_Drv_Rec_Flags.busy_flag=1;
		U1Mast_Drv_Rec_Flags.recv_check=0;
		//U1Mast_Drv_Rec_Var.U1_CRC = U1Mast_Drv_crcFast((UART1_recvdata),1);
		UART1_recvdata[0]=0;
		//if(U1Mast_Drv_Rec_Var.U1_CRC == UART1_recvdata[1])
		//{

		U1Mast_App_Rec_Flags.Received_Message_s=1;  // this is different as compared to slave
			//  UART1_Msg_Send_Reqt_Flags.Msg_B=1;//send ack

		//}
		U1Mast_Drv_Rec_Flags.busy_flag=0;
	}

}

void U1Mast_App_Update_Variables_if_Mesage_is_c(void)
{
	if(UART1_recvdata[0]=='c' && U1Mast_Drv_Rec_Var.Array_Index==21)//for user set
	{
		U1Mast_Drv_Rec_Flags.busy_flag=1;
		U1Mast_Drv_Rec_Flags.recv_check=0;
		U1Mast_Drv_Rec_Var.U1_CRC = U1Mast_Drv_crcFast((UART1_recvdata),21);
		UART1_recvdata[0]=0;
		if(U1Mast_Drv_Rec_Var.U1_CRC == UART1_recvdata[21])
		{
			U1Mast_App_Use_Received_Data_c();

			U1Mast_App_Rec_Flags.Received_Message_c=1;  // this is different as compared to slave
			U1Mast_App_Rec_Flags.Received_Message_c_again = 1;
			//  UART1_Msg_Send_Reqt_Flags.Msg_B=1;//send ack
			// UART1_Send_Flags.Msg_t=0

		}
		U1Mast_Drv_Rec_Flags.busy_flag=0;
	}

}

void U1Mast_App_Update_Variables_if_Mesage_is_r(void)
{
	if(UART1_recvdata[0]=='r')//for user set
	{
		U1Mast_Drv_Rec_Flags.busy_flag=1;
		U1Mast_Drv_Rec_Flags.recv_check=0;
		UART1_recvdata[0]=0;

		U1Mast_App_Rec_Flags.Received_Message_r=1;  // this is different as compared to slave

		U1Mast_Drv_Rec_Flags.busy_flag=0;
	}

}

/*
void UART1_SendMsg(void)
{
   unsigned char size;
   UART1_TXPtr=&UART1_txdata[0];
   size=sizeof(UART1_txdata);
   while(size)
   {
      while (UART1_Transmit_Not_Complete);
      USART1->TDR = *UART1_TXPtr++;
      size--;
   }
}
*/

void U1Mast_App_Use_Received_Data_m(void)
{
	__IO uint8_t j = 1;
	for(int i = 1; i < 40 ; i = i+2)
	{
		Disp_Metering_Value[j] = (uint16_t)(UART1_recvdata[i])|((uint16_t)(UART1_recvdata[i+1])<<8);
		j = j+1;
	}

	Disp_Metrng_Calib_Value[3] = Disp_Metering_Value[7];                    //I_INV
	Disp_Metrng_Calib_Value[5] = Disp_Metering_Value[2];                    //V_PV
	Disp_Metrng_Calib_Value[6] = Disp_Metering_Value[3];                    //I_PV
	Disp_Metrng_Calib_Value[7] = Disp_Metering_Value[6];                    //V_MAINS
	Disp_Metrng_Calib_Value[8] = Disp_Metering_Value[8];                    //I_MAINS

	Disp_Desired_Metrng_Calib_Value[3] = Disp_Metering_Value[7];             //I_INV
	Disp_Desired_Metrng_Calib_Value[5] = Disp_Metering_Value[2];             //V_PV
	Disp_Desired_Metrng_Calib_Value[6] = Disp_Metering_Value[3];             //I_PV
	Disp_Desired_Metrng_Calib_Value[7] = Disp_Metering_Value[6];             //V_MAINS
	Disp_Desired_Metrng_Calib_Value[8] = Disp_Metering_Value[8];             //I_MAINS


}

void U1Mast_App_Use_Received_Data_c(void)
{

		//Calibration_Temp.Error = 0;

		__IO uint8_t j = 1;
		for(int i = 1; i < 20 ; i = i+2)
		{
			Calib_Value[j] = (uint16_t)(UART1_recvdata[i])|((uint16_t)(UART1_recvdata[i+1])<<8);
			j = j+1;
		}

//		i = 1;
//		Calib_Value[1] = (uint16_t)(UART1_recvdata[i])|((uint16_t)(UART1_recvdata[i+1])<<8);
//
//		i = 3;
//		Calib_Value[2] = (uint16_t)(UART1_recvdata[i])|((uint16_t)(UART1_recvdata[i+1])<<8);
//
//		i = 5;
//		Calib_Value[3] = (uint16_t)(UART1_recvdata[i])|((uint16_t)(UART1_recvdata[i+1])<<8);
//
//		i = 7;
//		Calib_Value[4] = (uint16_t)(UART1_recvdata[i])|((uint16_t)(UART1_recvdata[i+1])<<8);
//
//		i = 9;
//		Calib_Value[5] = (uint16_t)(UART1_recvdata[i])|((uint16_t)(UART1_recvdata[i+1])<<8);
//
//		i = 11;
//		Calib_Value[6] = (uint16_t)(UART1_recvdata[i])|((uint16_t)(UART1_recvdata[i+1])<<8);
//
//		i = 13;
//		Calib_Value[7] = (uint16_t)(UART1_recvdata[i])|((uint16_t)(UART1_recvdata[i+1])<<8);
//
//		i = 15;
//		Calib_Value[8] = (uint16_t)(UART1_recvdata[i])|((uint16_t)(UART1_recvdata[i+1])<<8);
//
//		i = 17;
//		Calib_Value[9] = (uint16_t)(UART1_recvdata[i])|((uint16_t)(UART1_recvdata[i+1])<<8);

}
/*
void UART1_Populate_Txdata_Array_With_Message_Settings(void)

   {

        
        UART1_Send_Var.Array_Index=0;
        UART1_Send_Flags.Send_Enable=1;
     }

void UART1_Populate_Txdata_Array_With_Message_Calib(void)

   {
        UART1_Txdata[0]='t';
        UART1_Send_Var.Msg_Length=1;//(0)for message and no CRC (total 1)
        
        
        UART1_Send_Var.Array_Index=0;
        UART1_Send_Flags.Send_Enable=1;
   }

void UART1_Populate_Txdata_Array_With_Message_Request_Calib(void)
{
       UART1_Txdata[0]='u';
       UART1_Send_Var.Msg_Length=1;//(0)for message and no CRC (total 1)


       UART1_Send_Var.Array_Index=0;
       UART1_Send_Flags.Send_Enable=1;
  }



void UART1_Populate_Txdata_Array_With_Request_Dignostics(void)
{
       UART1_Txdata[0]='w';
       UART1_Send_Var.Msg_Length=1;//(0)for message and no CRC (total 1)


       UART1_Send_Var.Array_Index=0;
       UART1_Send_Flags.Send_Enable=1;
  }

void UART1_Populate_Txdata_Array_With_Request_Reset(void)
{
       UART1_Txdata[0]='w';
       UART1_Send_Var.Msg_Length=1;//(0)for message and no CRC (total 1)


       UART1_Send_Var.Array_Index=0;
       UART1_Send_Flags.Send_Enable=1;
  }
*/

void UART1_Master_Variables_Init(void)
{
	U1Mast_App_Rec_Flags.Received_Message_m=0;

	U1Mast_App_Send_Flags.Meterng_Communication_eror=0;

	U1Mast_App_Send_Var.Ack_Fail_Num=0;
	U1Mast_App_Send_Var.Ack_Wait_Time_cntr=U1Mast_Ack_Wait_Time;

}
