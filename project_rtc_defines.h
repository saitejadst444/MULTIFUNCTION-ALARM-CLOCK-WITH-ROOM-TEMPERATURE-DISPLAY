
//lcd commands
#define CLEAR_LCD  0X01
#define SHIFT_CUR_RIGHT 0X06
#define SHIFT_CUR_LEFT  0X07
#define SHIFT_DISP_LEFT 0X10
#define DSP_ON_CUR_ON 0X0E
#define MODE_8BIT_1LINE 0X30
#define MODE_8BIT_2LINE 0X38
#define GOTO_LINE1_POS0 0X80
#define GOTO_LINE2_POS0 0XC0
#define DSP_ON_CUR_OFF 0X0C
#define GOTO_CGRAM_START 0X40
#define LCD_DATA 8
#define LCD_RS 16
#define LCD_RW 18
#define LCD_EN 17
//adc
//clock	defines
#define FOSC 12000000
#define CCLK (FOSC*5)
#define PCLK (CCLK/4)
#define ADCCLK 3000000 //<=4.5MHz
#define CLKDIV ((PCLK/ADCCLK)-1)
//ADCR sfr defines
#define CLKDIV_BITS    8
#define PDN_BIT       21
#define ADC_START_BIT 24

//ADDR sfr defines
#define RESULT_BITS 6
#define DONE_BIT    31
//RTC
#define PREINT_VAL ((int)((PCLK / 32768) - 1))
#define PREFRAC_VAL (PCLK - ((PREINT_VAL+1)*32768))
#define RTC_ENABLE (1<<0) 
#define RTC_RESET  (1<<1) 
//PIN CONNECT BLOCK
#define pin_func1 0
#define pin_func2 1
#define pin_func3 2
#define pin_func4 3
#define EINT0_0_1 3
#define EINT1_0_3 3
#define READBIT(WORD,BIT) ((WORD>>BIT)&1)
#define WRITENIBBLE(WORD,NIBBLESTARTBITPOS,VAL) \
        WORD=((WORD&~(15<<NIBBLESTARTBITPOS))| \
		          (((VAL&15)<<NIBBLESTARTBITPOS)))

#define READNIBBLE(WORD,NIBBLESTARTBIT) \
        ((WORD>>NIBBLESTARTBIT)&15)
				
#define WRITEBYTE(WORD,BYTESTARTBITPOS,VAL) \
        WORD=((WORD&~(0xFF<<BYTESTARTBITPOS))| \
		          ((VAL<<BYTESTARTBITPOS)))

#define WRITEBIT(WORD,BITPOS,BIT) \
        WORD=((WORD&~(1<<BITPOS))|(((BIT<<BITPOS))));


#define EINT0_VIC_CHN0 14

//kpm
//#define COL0 20
#define ROWs_4  16//@p1.16 to p1.19
#define COLs_4  20
