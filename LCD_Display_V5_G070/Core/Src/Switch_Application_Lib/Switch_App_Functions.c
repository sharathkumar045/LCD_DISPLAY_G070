#include "stm32g0xx.h"

#include "Switch_App_Variables.h"
#include "Switch_App_Functions.h"

#include "LCD16X2_Driver_Functions.h"
#include "LCD16X2_Driver_Variables.h"


void Switch_1ms_Interrupt_Fn()
{
	if(Inc_Bttn_Pressed)
	{
		Switch_Detect_Incrmnt_Btn.Cntr = Switch_Detect_Incrmnt_Btn.Cntr + 1;

	}
	else if(Dec_Bttn_Pressed)
	{
		Switch_Detect_Decrmnt_Btn.Cntr = Switch_Detect_Decrmnt_Btn.Cntr + 1;
	}
	else if(Set_and_Enter_Bttn_Pressed)
	{
		Switch_Detect_Set_Btn.Cntr = 0;
		//Switch_Detect_Set_Btn.Long_Press = 0;
		//Switch_Detect_Set_Btn.Shrt_Press = 0;

		Switch_Detect_Enter_Btn.Cntr = 0;
		//Switch_Detect_Enter_Btn.Long_Press = 0;
		//Switch_Detect_Enter_Btn.Shrt_Press = 0;

		Switch_Detect_Set_Enter_Btn.Cntr = Switch_Detect_Set_Enter_Btn.Cntr + 1;
	}
	else if(Set_Bttn_Pressed)
	{
		Switch_Detect_Set_Btn.Cntr = Switch_Detect_Set_Btn.Cntr + 1;
	}
	else if(Enter_Bttn_Pressed)
	{
		Switch_Detect_Enter_Btn.Cntr = Switch_Detect_Enter_Btn.Cntr + 1;
	}


	Switch_Incrmnt_Detect();
	Switch_Decrmnt_Detect();
	Switch_Set_Detect();
	Switch_Enter_Detect();
	Switch_Set_and_Enter_Detect();

}

void Switch_Incrmnt_Detect()
{
   if (Inc_Bttn_Pressed) // S_Check_SW2_ON os defined as #define
	{

	   Switch_Detect_Incrmnt_Btn.Cntr++;
		if ((Switch_Detect_Incrmnt_Btn.Cntr>1000))
		{
			Switch_Detect_Incrmnt_Btn.Pressed=1;//should be reset once this request is serviced

			Switch_Detect_Incrmnt_Btn.Cntr=950;// should perform an increment operation every 50 milli seconds

		}
	}
   else
	{
		if (Switch_Detect_Incrmnt_Btn.Cntr>100)
		{
			Switch_Detect_Incrmnt_Btn.Pressed=1; //this variable is reset by the code in the main program
			Switch_Detect_Incrmnt_Btn.Cntr=0;
		}
		else
		{
			Switch_Detect_Incrmnt_Btn.Cntr=0;
		}
	}
}

void Switch_Decrmnt_Detect()
{
   if (Dec_Bttn_Pressed) // S_Check_SW2_ON os defined as #define
	{
		if ((Switch_Detect_Decrmnt_Btn.Cntr>1000))
		{
			Switch_Detect_Decrmnt_Btn.Pressed=1;//should be reset once this request is serviced

			Switch_Detect_Decrmnt_Btn.Cntr=950;// should perform an increment operation every 50 milli seconds
		}
	}
   else
	{
		if (Switch_Detect_Decrmnt_Btn.Cntr>100)
		{
			Switch_Detect_Decrmnt_Btn.Pressed=1; //this variable is reset by the code in the main program
			Switch_Detect_Decrmnt_Btn.Cntr=0;
		}
		else
		{
			Switch_Detect_Decrmnt_Btn.Cntr=0;
		}
	}
}

void Switch_Set_Detect()
{
	if (Set_Bttn_Pressed) // S_Check_SW1_ON os defined as #define
	{
		if ((Switch_Detect_Set_Btn.Cntr>1050))
		{
			Switch_Detect_Set_Btn.Cntr=1050;  //this prevents overflow or the variable
		}
	}
	else
	{
		if ((Switch_Detect_Set_Btn.Cntr>100)&&(Switch_Detect_Set_Btn.Cntr<=1000))
		{
			Switch_Detect_Set_Btn.Long_Press=0;
			Switch_Detect_Set_Btn.Shrt_Press=1; //this variable is reset by the code in the main program
			Switch_Detect_Set_Btn.Cntr=0;
		}
		else if ((Switch_Detect_Set_Btn.Cntr>1000)&&(Switch_Detect_Set_Btn.Cntr<=2000))
		{
			Switch_Detect_Set_Btn.Shrt_Press=0;
			Switch_Detect_Set_Btn.Long_Press=1; //this variable is reset by the code in the main program
			Switch_Detect_Set_Btn.Cntr=0;
		}
		else
		{
			Switch_Detect_Set_Btn.Cntr=0;
		}
	}
}

void Switch_Enter_Detect()
{
	if (Enter_Bttn_Pressed) // S_Check_SW1_ON os defined as #define
	{
		if ((Switch_Detect_Enter_Btn.Cntr>1050))
		{
			Switch_Detect_Enter_Btn.Cntr=1050;  //this prevents overflow or the variable
		}
	}
	else
	{
		if ((Switch_Detect_Enter_Btn.Cntr>100)&&(Switch_Detect_Enter_Btn.Cntr<=1000))
		{
			Switch_Detect_Enter_Btn.Long_Press=0;
			Switch_Detect_Enter_Btn.Shrt_Press=1; //this variable is reset by the code in the main program
			Switch_Detect_Enter_Btn.Cntr=0;
		}
		else if ((Switch_Detect_Enter_Btn.Cntr>1000)&&(Switch_Detect_Enter_Btn.Cntr<=2000))
		{
			Switch_Detect_Enter_Btn.Shrt_Press=0;
			Switch_Detect_Enter_Btn.Long_Press=1; //this variable is reset by the code in the main program
			Switch_Detect_Enter_Btn.Cntr=0;
		}
		else
		{
			Switch_Detect_Enter_Btn.Cntr=0;
		}
	}
}

void Switch_Set_and_Enter_Detect()
{
   if (Set_and_Enter_Bttn_Pressed) // S_Check_SW2_ON os defined as #define
	{
		Switch_Detect_Set_Btn.Cntr = 0;
		Switch_Detect_Enter_Btn.Cntr = 0;
		if ((Switch_Detect_Set_Enter_Btn.Cntr>1000))
		{
			Switch_Detect_Set_Enter_Btn.Cntr=1000;// should perform an increment operation every 50 milli seconds
		}
	}
   else
   {
   	if(Switch_Detect_Set_Enter_Btn.Cntr>=1000)
   	{
			Switch_Detect_Set_Enter_Btn.Pressed=1;//should be reset once this request is serviced
   		Switch_Detect_Set_Enter_Btn.Cntr = 0;
   	}
   	else
   	{
			Switch_Detect_Set_Enter_Btn.Cntr=0;//should be reset once this request is serviced
   	}

   }
}
