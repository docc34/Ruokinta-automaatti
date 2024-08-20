// #include <Adafruit_SSD1306.h>
#include <EEPROM.h>
#include "Adafruit_SSD1306_Modified.h"
#include "timeClass.h"
#include "RtcObject.h"
#ifndef encoderClass_h
#define encoderClass_h

class encoderClass{
    //Define class vairables, that will be defined in the ino file
    public: long encoderPosition;//Ei ehkä tarvita tallentaa, päivittyvät joka kerta
    int newPosition;//Ei ehkä tarvita tallentaa, päivittyvät joka kerta
    int oldPosition;
    int cursorPosition;

    int buttonState;

    int menuNumber;

    bool buttonPressed;
    bool modifyInProgress;
    bool searchNewAlarms;

    String encoderString;

    timeClass timeClassO;
    //This list will contain all the alarms that the user will set
    RtcObject RtcObjects [4];
    //Constructor
    encoderClass();
    //Functions for each of the menus
    encoderClass mainMenu(encoderClass o);
    
    encoderClass alarmsMenu(encoderClass o);
    //This function is currently only used internally in encoderClass
    // encoderClass alarmModification(encoderClass o, int alarmNumber);

    encoderClass Menu2(encoderClass o);

};

#endif