/*********************************************************************************************************
   Originally based on Tick Tock Shield Basic Lesson 10: Clock
   Writen by Luke Miller (@lukeallister)
   Updated by Joel Miller (@LittleMiller4) on 12/8/17


   Dawn-Simulator. A programmable simulator of the dawn.
   Copyright (C) 2017  Luke and Joel Miller

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
*********************************************************************************************************/

#include <Wire.h>
#include <TTSDisplay.h>
#include<EEPROM.h>
#include <TTSTime.h>
//#include <TTSTempF.h>
#include <TTSButton.h>


TTSDisplay disp;                                    // instantiate an object of display
TTSTime time;
//TTSTemp temp;
TTSButton but1(TTSK1);
TTSButton but2(TTSK2);
TTSButton but3(TTSK3);


int hour = 0;                                       // hour
int min  = 0;                                       // minutes
int second = 0;
int alarmHour = 0;
int alarmMin = 0;
int led = 5;
int brightness = 0;                                 // how bright the LED is
int fadeAmount = 1;

void setup()
{
  //  time.setTime(22, 9, 20);                       // set time to 14:14:20
  pinMode(led, OUTPUT);
  disp.pointOn();
}

void loop()
{
  alarmHour=EEPROM.read(0);
  alarmMin=EEPROM.read(1);

  displayTime();

  while (but3.pressed())
  {
    set_alarm();
  }

  while (but1.pressed())
  {
    disp.time(EEPROM.read(0),EEPROM.read(1));
//    analogWrite(led, brightness);
//    if (brightness < 255)
//      brightness = brightness + fadeAmount;
//    delay(30);
  }
  while (but2.pressed())
  {
    analogWrite(led, brightness);
    if (brightness > 0)
      brightness = brightness - fadeAmount;
    delay(30);
  }
  checkAlarm();
}

void set_alarm() {
   if (alarmHour > 12) {
    disp.time(alarmHour - 12, alarmMin);                         // display hour:min
    disp.pointOn();                                     // use display point as our PM
  }
  else {
    disp.time(alarmHour, alarmMin);
    disp.pointOff(); //use display point as pm
  }

  if (but2.pressed()) {
    delay(100); //debounce
    if (but2.pressed()) {
    alarmHour = alarmHour+1;
    if(alarmHour==24) {
      alarmHour=0;
    }
    }
  }

   if (but1.pressed()) {
    delay(100); //debounce
    if (but1.pressed()) {
    alarmMin = alarmMin+1;
    if(alarmMin==60) {
      alarmMin=0;
    }
    }
  }
  EEPROM.update(0,alarmHour);
  EEPROM.update(1,alarmMin);
}

//void temp_display() {
//
//  int valTemp = temp.get();                       // get temperature
//
//  disp.num(valTemp);                              // display temperature
//
//  delay(100);
//}

void checkAlarm() {
  int startLight=0;
  if((hour==EEPROM.read(0))&&(min==EEPROM.read(1)))
    startLight=1;
  while (startLight==1) { //check the alarm and fade up the clock
    analogWrite(led, brightness);
    if (brightness < 255)
      brightness = brightness + fadeAmount;
    delay(2000); //for 30-minute fade it should by 7 seconds
    displayTime();
    if (brightness==255)
      startLight=0;
    if (but2.pressed()) {
    delay(100); //debounce
    if (but2.pressed()) {
      startLight=0;

    }
}
}}

void displayTime() {
  hour = time.getHour();                          // get hour
  min  = time.getMin();                           // get minutes
  second = time.getSec();                         // get seconds
   if (hour > 12) {
    disp.time(hour - 12, min);                         // display hour:min
    disp.pointOn();                                     // use display point as our PM
  }
  else
    disp.time(hour, min);
  }


/*********************************************************************************************************
END FILE
***********************************************************************************************************/
