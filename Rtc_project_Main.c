#include<LPC214x.h>
#include"project_rtc.h"
#include"project_rtc_defines.h"
s32 hour,min,sec,date,month,year,day;
u32 adcDVal,temp,chNo=1,AlarmON,Alarm_Ring=0;
u8 bell[]={0x04,0x0E,0x0E,0x0E,0x01F,0x00,0x0E,0x00};
f32 eAR;
extern u32 AL_Min,AL_Hour;

int main()
{
	Init_ADC();
	Init_LCD();
	RTC_Init();
	Initi_irq();
	SetRTCTimeInfo(14,10,00);
	SetRTCDateInfo(12,11,2025);
	SetRTCDay(3);
		IODIR0|=(1<<0);
	while(1) 
	{
		GetRTCTimeInfo(&hour,&min,&sec);
		DisplayRTCTime(hour,min,sec);
		GetRTCDateInfo(&date,&month,&year);
		DisplayRTCDate(date,month,year);
		GetRTCDay(&day);
		DisplayRTCDay(day);
		Read_ADC(chNo,&adcDVal,&eAR);
		temp=eAR*100;
		CmdLCD(GOTO_LINE2_POS0+12);
		U32LCD(temp);
		CharLCD(0xDF);
		CharLCD('c');
		if(HOUR==AL_Hour && MIN==AL_Min)
		{
			if(Alarm_Ring==0)
			{  
			 BuildCGRAM(bell,8);
			 CmdLCD(GOTO_LINE1_POS0+15);
		      CharLCD(0);
			 IOSET0=1<<0;
			if((IOPIN0>>22&1)==0)//switch for stop the alarm
			{	
		    	IOCLR0=1<<0;
			   CmdLCD(GOTO_LINE1_POS0+15);
			   CharLCD(' ');
			   Alarm_Ring=1;
			}

			}
	}
		else
		{
			Alarm_Ring=0;
		}
	}
}

