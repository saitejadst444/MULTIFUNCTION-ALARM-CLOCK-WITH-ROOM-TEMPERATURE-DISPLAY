MULTIFUNCTION ALARM CLOCK WITH ROOM TEMPERATURE DISPLAY
OBJECTIVE:Envir0Clock is a project using LPC2148 that shows the current time,alarm and room temperature on an LCD Users can set or change the time and alarm using keypad.
When the alarm time is reached, a buzzer sounds.
The system combines clock,temperature sensing and alarm features in one easy-to-use device.
REQUIREMENTS:
HARDWARE REQUIREMENTS:
LPC2148,LCD,KEYPAD,LM35 Sensor,BUZZER,SWITCHES
SOFTWARE REQUIREMENTS:
PROGRAMMING IN EMBEDDED C
FLAG MAGIC
WORK FLOW OF THE PROJECT:in this project the required peripherials such as lcd,keypad,rtc,adc and external interrupt are initialized inside the main function before enter the 
super loop.This project is multifunction based clock the clock displays the current time and date ,temperatureand alarm.It allows user to modify their time and setting alarm 
by raise a interrupt.when the user raise a interrupt it displays three options 1.Edit Rtc Information 2.Set Alarm 3.Exit if the user selects exit,the program simply resumes the main loop,if user select the Edit Rtc then Lcd shows a second menu allowing modification of Hours,Minutes,seconds,Day,Date,Month,and Year with exit option.
