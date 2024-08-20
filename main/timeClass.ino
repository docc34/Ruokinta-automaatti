#include "timeClass.h"

//Constructor class sets default values
timeClass::timeClass(){
  modifyBlinker = 1;
  numberBeingModified = 0;
}

//Constructor class sets default values
void timeClass::printAlarmStatus(RtcObject o, int alarmNumber,int currentlyActiveAlarmNumber,const int rowHeights [],const String weekdays[]){
  alarmNumber = alarmNumber +1;
  // Serial.println(currentlyActiveAlarmNumber);
  int activeAlarm = currentlyActiveAlarmNumber;
  // Serial.println(currentlyActiveAlarmNumber);
  // Serial.println(currentlyActiveAlarmNumber+1);
  // Serial.println("alarmNumber:");
  // Serial.println(alarmNumber);

  //Tämä on toteutettu tälleen, koska hälytyksen tallennus EEPROM:iin muuttaa sen tyyppiä, 
  //jotenkin siten, ettei se enää parsivoidu stringiksi tai chariksi
  display.setCursor(0, rowHeights[alarmNumber]);
  display.print('A');
  display.setCursor(7, rowHeights[alarmNumber]);
  display.print(alarmNumber);
  display.setCursor(12, rowHeights[alarmNumber]);
  display.print(':');
  display.setCursor(17, rowHeights[alarmNumber]);
  display.print(weekdays[o.alarmDay]);
  display.setCursor(29, rowHeights[alarmNumber]);
  display.print(",");
  display.setCursor(35, rowHeights[alarmNumber]);
  display.print(o.alarmHour);
  display.setCursor(45, rowHeights[alarmNumber]);
  display.print('.');
  display.setCursor(51, rowHeights[alarmNumber]);
  display.print(o.alarmMinute);

  if(alarmNumber == activeAlarm+1){
    display.setCursor(65, rowHeights[alarmNumber]);
    display.print("Active A");
  }
}

// //Constructor class sets default values
RtcObject timeClass::modifyAlarm(RtcObject o, int alarmNumber, int currentlyActiveAlarm){

  //If the alarm is the one currently saved on the RTC, save the modifications to the RTC else do nothing
  if(alarmNumber == currentlyActiveAlarm){
    //Save the alarm to the RTC alarm 2. We dont need to save alarm seconds so use alarm 2 that dosen't save seconds
    myRTC.turnOffAlarm(2);
    myRTC.setA2Time(o.alarmDay, o.alarmHour, o.alarmMinute, 0b01100000, true, false,false);
    myRTC.turnOnAlarm(2);
  }

  return o;
}