#include<LPC214x.h>						                                                                                                                                                                                                                                                                                  s
#include"project_rtc_defines.h"
#include"project_rtc.h"	
u32 int_req;
u32 keyV, num;
u8 key;
u32 AL_Min,AL_Hour;
 /*-------------------delay function definition--------------------------*/
void delayUS(u32 dlyUS)
{
	dlyUS*=12;
	while(dlyUS--);
}
void delayMS(u32 dlyMS)
{
		dlyMS*=12000;
	  while(dlyMS--);
}
void delayS(u32 dlyS)
{
	dlyS*=12000000;
	  while(dlyS--);
}

  /*-------------------delay function defintion end---------------------------*/

 /*-------------------Pin configuration---------------------------*/
void cfgportpinfunc(u32 portNo,u32 pinNo,u32 pinfunc)
{
if(portNo==0)
{
if(pinNo<=15)
{
PINSEL0=((PINSEL0&~(3<<pinNo*2)|(pinfunc<<pinNo*2)));
}
else if((pinNo>=16)&&(pinNo<=31))
{
PINSEL1=(PINSEL1&~(3<<(pinNo-16)*2)|(pinfunc<<((pinNo-16)*2)));
}
}
}
/*-------------------Pin configuration---------------------------*/
/*--------------------ADC start----------------------------------*/
void Init_ADC(void)
{
	//cfg ADCR sfr
	AD0CR|=(1<<PDN_BIT)|(CLKDIV<<CLKDIV_BITS);
	//cfg p0.28 pin as Analog Input pin0 (AIN0)
    cfgportpinfunc(0,28,pin_func2);
}
void Read_ADC(u32 chNo,u32 *adcDVal,f32 *eAR)
{
	//clear any previous channel selection
	AD0CR&=0xFFFFFF00;
	//update req channel select,
	//start analog samping & conversion
	AD0CR|=1<<chNo|1<<ADC_START_BIT;
	delayUS(3);
	while(((AD0GDR>>DONE_BIT)&1)==0);
	AD0CR&=~(1<<ADC_START_BIT);
	*adcDVal=(AD0GDR>>RESULT_BITS)&1023;
	*eAR = (*adcDVal * (3.3/1023));
}
/*--------------------ADC End----------------------------------*/

/*----------------Lcd start------------------------------------*/
void Init_LCD(void)
{
	 IODIR0|=((0XFF<<LCD_DATA)|(1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN));
	//power on delay
	delayMS(15);
	CmdLCD(0x30);
	delayMS(4);
	delayUS(100);
	CmdLCD(0x30);
	delayUS(100);
	CmdLCD(0X30);
	CmdLCD(MODE_8BIT_2LINE);
	CmdLCD(DSP_ON_CUR_OFF);
	CmdLCD(CLEAR_LCD);
	CmdLCD(SHIFT_CUR_RIGHT);
}
void WriteLCD(u8 byte)
{
//select write operation 
	IOCLR0=1<<LCD_RW;
	WRITEBYTE(IOPIN0,LCD_DATA,byte);
	IOSET0=1<<LCD_EN;
	delayUS(1);
	IOCLR0=1<<LCD_EN;
	delayMS(2);
}
void CmdLCD(u8 cmdByte)
{
	IOCLR0=1<<LCD_RS;
	WriteLCD(cmdByte);
}
void CharLCD(u8 asciiVal)
{
	IOSET0=1<<LCD_RS;
	WriteLCD(asciiVal);
}
void StrLCD(s8 *str)
{
	while(*str)
	CharLCD(*str++);
}
void U32LCD(u32 n)
{
	s32 i=0;
	u8 a[10];
	if(n==0)
	{
	CharLCD('0');
	}
	else
	{
	while(n>0)
	{
	a[i++]=(n%10)+48;
	n/=10;
	}
	for(--i;i>=0;i--)
	CharLCD(a[i]);
	}
}
void BuildCGRAM(u8 *p,u8 nBytes)
{
	u32 i;
	CmdLCD(GOTO_CGRAM_START);
	IOSET0=1<<LCD_RS;
	for(i=0;i<nBytes;i++)
	{
	WriteLCD(p[i]);
	}
	CmdLCD(GOTO_LINE1_POS0+10);
}
/*----------------Lcd start------------------------------------*/

/*----------------RTC START------------------------------------*/
// Array to hold names of days of the week
s8 week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};
void RTC_Init(void)
{
  // Disable and reset the RTC
	CCR = RTC_RESET;
	PREINT = PREINT_VAL;
	PREFRAC = PREFRAC_VAL;
  // Enable the RTC
	CCR = RTC_ENABLE|(1<<4);  
}
void GetRTCTimeInfo(s32 *hour, s32 *minute, s32 *second)
{
	*hour = HOUR;
	*minute = MIN;
	*second = SEC;
}

void DisplayRTCTime(s32 hour, s32 minute, s32 second)

{
		CmdLCD(GOTO_LINE1_POS0);
		CharLCD((hour/10)+48);
		CharLCD((hour%10)+48);
		CharLCD(':');
		CharLCD((minute/10)+0x30);
		CharLCD((minute%10)+0x30);
		CharLCD(':');
		CharLCD((second/10)+'0');
		CharLCD((second%10)+'0');
}
void GetRTCDateInfo(s32 *date, s32 *month, s32 *year)
{
	*date = DOM;
	*month = MONTH;
	*year = YEAR;
}

void DisplayRTCDate(u32 date, u32 month, u32 year)

{

		CmdLCD(GOTO_LINE2_POS0);
		CharLCD((date/10)+48);
		CharLCD((date%10)+48);
		CharLCD('/');
		CharLCD((month/10)+0x30);
		CharLCD((month%10)+0x30);
		CharLCD('/');
		U32LCD(year);	
}

void SetRTCTimeInfo(u32 hour, u32 minute, u32 second)

{

	HOUR = hour;

	MIN = minute;

	SEC = second;
}

void SetRTCDateInfo(u32 date, u32 month, u32 year)
{
	DOM = date;

	MONTH = month;

	YEAR = year;
}

void GetRTCDay(s32 *dayofweek)

{
	*dayofweek = DOW; 

}

void DisplayRTCDay(u32 dayofweek)

{

	CmdLCD(GOTO_LINE1_POS0+10);

	StrLCD(week[dayofweek]);  

}

void SetRTCDay(u32 dayofweek)
{
		DOW = dayofweek;

}
/*----------------RTC END------------------------------------*/
/*----------------INTERRUPT START------------------------------------*/
void Initi_irq(void)
{
	  cfgportpinfunc(0,1,EINT0_0_1);
	  VICIntEnable = 1<<EINT0_VIC_CHN0;
	  VICVectCntl0 = (1<<5)|EINT0_VIC_CHN0;
	  VICVectAddr0 = (u32 )eint0_isr;
	  EXTMODE = 1<<0;
}
/*----------------EDIT ALARM START------------------------------------*/
void edit_alarm()
{
	while(1)
	{
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("HH:MM");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("1-HH,2-MM,3-S");
	keyV=KeyScan();
	while(ColScan()==0);
	switch(keyV)
	{
		case '1':CmdLCD(CLEAR_LCD);	CmdLCD(GOTO_LINE1_POS0);StrLCD("HH:");	
			CmdLCD(GOTO_LINE2_POS0);
			ReadNum(&num,&key);
			if(num>=0 && num<=23)
			{
			AL_Hour=num;
			}
			else
			{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("Invalid Inputs");
			delayMS(200);
			}
			break;
	case '2':CmdLCD(CLEAR_LCD);	CmdLCD(GOTO_LINE1_POS0);StrLCD("Min:");	
			CmdLCD(GOTO_LINE2_POS0);
			ReadNum(&num,&key);
			if(num>=0 && num<=59)
			{
			AL_Min=num;
			}
			else
			{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("Invalid Inputs");
			delayMS(200);
			}
			break;
	case'3':CmdLCD(CLEAR_LCD);return;
	default:CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("Invalid Inputs");
			delayMS(200);
			break;
	}
	}

}
/*----------------EDIT ALARM END------------------------------------*/
/*----------------EDIT REAL TIME CLOCK START------------------------------------*/
void edit_rtc()
{
	while(1)
	{
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("1-H 2-M 3-S 4-D");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("5-DD6-MM7-YY8-E");
	keyV=KeyScan();
	while(ColScan()==0);
	delayMS(200);
	switch(keyV)
	{
	case '1':CmdLCD(CLEAR_LCD);	CmdLCD(GOTO_LINE1_POS0);StrLCD("HH:");	
			CmdLCD(GOTO_LINE2_POS0);
			ReadNum(&num,&key);
	         if (num>=0&& num<=23)
			 {
			 	
				HOUR = num;
			 }
			 else
			{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("Invalid Inputs");
			delayMS(200);
			}
			 break;
	case '2':CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);StrLCD("Min:");	
			CmdLCD(GOTO_LINE2_POS0);
			ReadNum(&num,&key);
			if (num>=0&& num<=59)
			 {
			     //CmdLCD(CLEAR_LCD);
				MIN= num;
			 }
			 else
			{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("Invalid Inputs");
			delayMS(200);
			}
			 break;
	case '3':CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);StrLCD("Sec:");	
			CmdLCD(GOTO_LINE2_POS0);
			ReadNum(&num,&key);
			if (num>=0&& num<=59)
			 {
			 	 //CmdLCD(CLEAR_LCD);
				SEC= num;
			 }
			 else
			{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("Invalid Inputs");
			delayMS(200);
			}
			 break;
	case '4':CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);StrLCD("Day:");	
			CmdLCD(GOTO_LINE2_POS0);
			ReadNum(&num,&key);
			if (num>=0&& num<=6)
			 {
			 	//CmdLCD(CLEAR_LCD);
				DOW= num;
			 }
			 else
			{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("Invalid Inputs");
			delayMS(200);
			}
			 break;
	case '5':CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);StrLCD("DOw:");	
			CmdLCD(GOTO_LINE2_POS0);
			ReadNum(&num,&key);
			if (num>0&& num<32)
			 {
			     //CmdLCD(CLEAR_LCD);
				DOM= num;
			 }
			else
			{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("Invalid Inputs");
			delayMS(200);
			}
			 break;
	case '6':CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);StrLCD("Month:");	
			CmdLCD(GOTO_LINE2_POS0);
			ReadNum(&num,&key);
			if (num>=1&& num<=12)
			 {
			 	//CmdLCD(CLEAR_LCD);
				MONTH= num;
			 }
			else
			{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("Invalid Inputs");
			delayMS(200);
			}
			 break;
	case '7':CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);StrLCD("Year:");	
			CmdLCD(GOTO_LINE2_POS0);
			ReadNum(&num,&key);
			if (num>=2000&& num<=2099)
			 {
			 	CmdLCD(CLEAR_LCD);
				YEAR= num;
			 }
			else
			{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("Invalid Inputs");
			delayMS(200);
			}
			 break;
	case '8':CmdLCD(CLEAR_LCD);return;
	//case 'C':CmdLCD(SHIFT_CUR_LEFT );break;
	default:CmdLCD(CLEAR_LCD);CmdLCD(GOTO_LINE1_POS0);StrLCD("Invalid!");delayMS(200);
			break;
	}
	}


}
/*----------------EDIT REAL TIME CLOCK END------------------------------------*/
void eint0_isr(void) __irq
{
	int_req=1;
	Init_KPM();
	if(int_req==1)
	{
		while(1)
		{
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD("1.Ertc 2.set_alrm");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("3.Exit");
		keyV=KeyScan();
		while(ColScan()==0);
		delayMS(200);
		switch(keyV)
		{
		case '1':edit_rtc();//function definition  goto -301
				break;
		case '2':edit_alarm();//function defintion goto line no-246
		         break;
		case '3':CmdLCD(CLEAR_LCD);goto loop;
		}
		}		
}
	loop:EXTINT=1<<0;
	VICVectAddr=0;
}
/*----------------INTERRUPT END------------------------------------*/

