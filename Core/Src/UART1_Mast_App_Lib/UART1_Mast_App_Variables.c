/*
 * Variables.c
 *
 *  Created on: Apr 17, 2019
 *      Author: krishna
 */
#include "UART1_Mast_App_Variables.h"

#include "main.h"

#include "usart.h"
#include "UART1_Mast_App_Functions.h"


//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


   // variables related to UART1_Rec_Transmission
    
//      __IO unsigned char UART1_recvdata[250]={0};
      

 
      struct U1_Mast_App_Rec_Flags U1Mast_App_Rec_Flags;


      struct U1_Mast_App_Rec_Var U1Mast_App_Rec_Var;

   

//UART1 variables related to message sending


//       __IO unsigned char UART1_Txdata[90]={0};



       struct U1_Mast_App_Send_Flags U1Mast_App_Send_Flags = {0};

       struct U1_Mast_App_Send_Var U1Mast_App_Send_Var = {0};

  
       volatile uint16_t V_INV_Ref = 2243;

       volatile uint16_t V_INV_UL  = 2652;
       volatile uint16_t V_INV_LL = 1638;

       volatile uint16_t V_Batt_H_Cutoff = 3519;
       volatile uint16_t V_Batt_H_Cutin = 2162 ;

       volatile uint16_t V_Batt_L_Cutin = 0;
       volatile uint16_t V_Batt_L_Cutoff = 2011;

       volatile uint16_t I_Inv_Full_Load = 936;

       volatile uint16_t Grid_KVA_Limit = 700;

       volatile uint16_t Relay_Off_Time = 18;
       volatile uint16_t Relay_On_Time = 17;

       volatile uint16_t I_grid_Export_Limit = 1950;
       volatile uint16_t I_grid_Import_Limit = 1950;

       volatile uint16_t PV_H_Cutoff = 2527;
       volatile uint16_t PV_H_Cutin = 2359;

       volatile uint16_t PV_L_Cutin = 505;
       volatile uint16_t PV_L_Cutoff = 421;

       volatile uint16_t I_PV_UL =1622 ;

       volatile uint16_t V_Mains_H_Cutoff = 2550; //calculate
       volatile uint16_t V_Mains_H_Cutin = 2535;

       volatile uint16_t V_Mains_L_Cutoff = 1560;
       volatile uint16_t V_Mains_L_Cutin = 1755;

       volatile uint16_t PV_Power_Limit = 2000;

     
       //struct U1_Mast_App_Msg_Send_Reqt_Flags U1Mast_App_Msg_Send_Reqt_Flags = {0};
     
