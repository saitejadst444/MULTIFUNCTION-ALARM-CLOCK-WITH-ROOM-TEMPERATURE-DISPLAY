# ENVIROCLOCK:MULTIFUNCTION ALARM CLOCK WITH ROOM TEMPERATURE DISPLAY

#### OBJECTIVE:

EnviroClock is a project using LPC2148 that shows the current time,alarm and room temperature on an LCD Users can set or change the time and alarm using keypad.
When the alarm time is reached, a buzzer sounds.The system combines clock,temperature sensing and alarm features in one easy-to-use device.

#### REQUIREMENTS:

##### HARDWARE REQUIREMENTS:

LPC2148,LCD,KEYPAD,LM35 SENSOR,BUZZER,SWITCHES

##### SOFTWARE REQUIREMENTS:

PROGRAMMING IN EMBEDDED C,FLASH MAGIC

#### WORK FLOW OF THE PROJECT:

In this project the required peripherials such as lcd,keypad,rtc,adc and external interrupt are initialized inside the main function before enter the 
super loop.This project is multifunction based clock the clock displays the current time and date ,temperatureand alarm.It allows user to modify their time and setting alarm 
by raise a interrupt.when the user raise a interrupt it displays three options.

**1.Edit Rtc Information**

**2.Set Alarm 3.Exit**

If the user selects exit,the program simply resumes the main loop,if user select the Edit Rtc then Lcd shows a second menu allowing modification of Hours,Minutes,seconds,Day,Date,Month,and Year with exit option.

The user can navigate these options through the keypad,enter teh new values and each input is validated against allowed ranges.Invalid inputs error message and retry request,while valid inputs update the RTC registers.The editing continues until the user chooses the exit option from this menu,after which the LCD confirms that RTC is updated and the system return back to menu.If the user selects **SET ALARM** option they are prompted to enter the alarm time based on user requirment through keypad.

This process supports an interactive multifunction clock and environment moniter where the system runs real-time timekeeping with temperature display,alarm functionality and user-friendly time and alarm editing routine via interrupt and keypad input.

#### FEATURES:

1.Real-Time Clock->displays current hour,minute,seconds in real time.

2.Temperature Monitoring->displays live temperature on LCD.

3.Alarm Functionality->user configurable alarm ,Alarm triggers buzzer activation when RTC time matches alarm time.

4.LCD-Based User Interface->shows time on 16X2 LCD.

5. 4X4 Keypad Input System->supports numeric and backspace and finishes input, Backspace with Cursor Control.
