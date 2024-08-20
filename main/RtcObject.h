
#ifndef RtcObject_h
#define RtcObject_h

class RtcObject{
    //Define class variables, that will be defined in the ino file
    public: 
    bool century;
    bool h12Flag;
    bool pmFlag;

    byte alarmDay, alarmHour, alarmMinute, alarmSecond, alarmBits;
    bool alarmDy, alarmH12Flag, alarmPmFlag;


    //Constructor
    RtcObject();
};

#endif