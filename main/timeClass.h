#include <DS3231.h>
#include "RtcObject.h"

#ifndef timeClass_h
#define timeClass_h

class timeClass{
    //Define class variables, that will be defined in the ino file
    public: 

    bool modifyAlarm1Save;

    //an integer that runs between 1 and 2 to create a blinking effect while editing date
    int modifyBlinker;
    //saves the state of alarm modification 0 = modifying the dow, 1 = modifying the hour, 2 = modifying the minute
    int numberBeingModified;

    //tells which one of the 4 alarms is currently being modified
    int alarmBeingModified;

    //Tells which alarm is currently active in the RTC VERY IMPORTANT VALUE IN HANDLING DATA IN EEPROM
    int currentlyActiveAlarm;

    //Constructor
    timeClass();
    
    //Functions for handling alarms
    void printAlarmStatus(RtcObject o, int alarmNumber,int currentlyActiveAlarmNumber,const int rowHeights [],const String weekdays []);
    RtcObject modifyAlarm(RtcObject o, int alarmNumber, int currentlyActiveAlarm);
};

#endif