
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

void readAlarmsFromEEPROM()
{
    int addr = 0;
 
    for(int i=0;i<4;i++)
    {
        RtcObjects[i].alarmDay = EEPROM.read(addr );
        addr = addr + 1;
        RtcObjects[i].alarmHour =   EEPROM.read(addr);
        addr = addr + 1;
        RtcObjects[i].alarmMinute =  EEPROM.read(addr);
        addr = addr + 1;
        RtcObjects[i].alarmSecond = EEPROM.read(addr);
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
  readAlarmsFromEEPROM();
  printAlarms();
}

void loop() {


  delay(100);
}
