//miniproject 
 //types.h

typedef unsigned char u8;

typedef signed char s8;

typedef unsigned short int u16;

typedef signed short int s16;

typedef unsigned long int u32;

typedef signed long int s32;

typedef float f32;

typedef double f64;
/*-----------------------dealy-----------------*/
void delayUS(u32);

void delayMS(u32);

void delayS(u32);


//LCD
void Init_LCD(void);
void WriteLCD(u8 byte);
void CmdLCD(u8 cmdByte);
void CharLCD(u8 asciiVal);
void StrLCD(s8 *);
void U32LCD(u32);
void BuildCGRAM(u8 *,u8);
//ADC
void Init_ADC(void);
void Read_ADC(u32 chNo,u32 *adcDVal,f32 *eAR);
//RTC
void RTC_Init(void);
void GetRTCTimeInfo(s32 *,s32 *,s32 *);
void DisplayRTCTime(s32,s32,s32);
void GetRTCDateInfo(s32 *,s32 *,s32 *);
void DisplayRTCDate(u32,u32,u32);

void SetRTCTimeInfo(u32,u32,u32);
void SetRTCDateInfo(u32,u32,u32);

void GetRTCDay(s32 *);
void DisplayRTCDay(u32);
void SetRTCHour(u32);
void SetRTCMin(u32);
void SetRTCSec(u32);
void SetRTCDate(u32);
void SetRTCMonth(u32);
void SetRTCYear(u32);
void SetRTCDay(u32);
void GetRTCHour(s32 *);
void GetRTCMin(s32 *);
void GetRTCSec(s32 *);
//Pin functions
void cfgportpinfunc(u32 portNo,u32 pinNo,u32 pinfunc);
//interrupt
void eint0_isr(void) __irq;
void Initi_irq(void);

 //kpm,
 void Init_KPM(void);
u32  ColScan(void);
u32  RowCheck(void);
u32  ColCheck(void);
u32  KeyScan(void);

void ReadNum(u32 *,u8 *);
//void Buzzer_On(void);
