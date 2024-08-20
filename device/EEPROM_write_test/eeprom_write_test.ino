#include <EEPROM.h>

class RtcObject{
    //Define class variables, that will be defined in the ino file
    public: bool century;
    bool h12Flag;
    bool pmFlag;

    byte alarmDay, alarmHour, alarmMinute, alarmSecond, alarmBits;
    bool alarmDy, alarmH12Flag, alarmPmFlag;

    RtcObject();
};

//Constructor class
RtcObject::RtcObject(){
  century = false;
}

RtcObject RtcObjects [4];

void writeAlaramsToEEPROM()
{
    int addr = 0;
 
    for(int i=0;i<4;i++)
    {
        // write alarmDay, alarmHour, alarmMinute, alarmSecond
        EEPROM.write(addr, RtcObjects[i].alarmDay);
        addr = addr + 1;
        EEPROM.write(addr,  RtcObjects[i].alarmHour);
        addr = addr + 1;
        EEPROM.write(addr, RtcObjects[i].alarmMinute);
        addr = addr + 1;
        EEPROM.write(addr, RtcObjects[i].alarmSecond);
        addr = addr + 1;
  }
}

void printAlarms()
{
  Serial.begin(9600);
    for(int i=0;i<4;i++)
    {
      Serial.print("\nRtcObjects[");
      Serial.print(i);
      Serial.print("]:\n");
      Serial.print("\nalarmDay:");
      Serial.print(RtcObjects[i].alarmDay);
      Serial.print("\nalarmHour:");
      Serial.print(RtcObjects[i].alarmHour);
      Serial.print("\nalarmMinute:");
      Serial.print(RtcObjects[i].alarmMinute);
      Serial.print("\nalarmSecond:");
      Serial.print(RtcObjects[i].alarmSecond);
    }
}

void setup() {
  RtcObjects[0].alarmDay = 10;
  RtcObjects[0].alarmHour = 2;
  RtcObjects[0].alarmMinute = 3;
  RtcObjects[0].alarmSecond = 4;

  RtcObjects[1].alarmDay = 5;
  RtcObjects[1].alarmHour = 6;
  RtcObjects[1].alarmMinute = 7;
  RtcObjects[1].alarmSecond = 8;
  
  RtcObjects[2].alarmDay = 9;
  RtcObjects[2].alarmHour = 10;
  RtcObjects[2].alarmMinute = 11;
  RtcObjects[2].alarmSecond = 12;

  RtcObjects[3].alarmDay = 13;
  RtcObjects[3].alarmHour = 14;
  RtcObjects[3].alarmMinute = 15;
  RtcObjects[3].alarmSecond = 16;


  writeAlaramsToEEPROM();
  printAlarms();
}

void loop() {


  delay(100);
}
