#include "encoderClass.h"

//Constructor class sets default values
encoderClass::encoderClass(){
    //Position of the cursor
    cursorPosition = 1;
    //Controls which menu is currently selected
    menuNumber = 0;
    //maximum number of rows for that menu
    oldPosition = -999;

    searchNewAlarms = true;
    modifyInProgress = false;
    buttonPressed = false;
}

//Listaa käytetään näyttämään käyttäjälle viikonpäivät.
const String weekdays [] = {"Ma","Ti","Ke","To","Pe","La","Su"};

//Function for rendering and handling the main menu
encoderClass encoderClass::mainMenu(encoderClass o){
    
    if(o.menuNumber == 0 && o.buttonState == 0 && o.buttonPressed == false){
        //There is a "Sub menu" for each row in the main menu
        o.menuNumber = o.cursorPosition;
        o.cursorPosition = 0;
        o.buttonPressed == true;
        // delay(50);
    }

    //menuNumber defines which rows submenus are opened.
    //menuNumber 0 is the main menu menuNumber 1 is the submenu for row 1, menuNumber 2 is the submenu for row 2
    if(o.menuNumber == 0){
        //This goes to renderStaticMenu Component

        display.setCursor(0,rowHeights[0]); //Row 1           // Start at top-left corner and go down from there
        display.println("Alarm's menu");

        display.setCursor(0,rowHeights[1]); //Row 2
        display.println("2 Row");
        
    }
    return o;
}
//Save the alarms that were modified to the EEPROM
void writeAlarmsToEEPROM(encoderClass o)
{
    int addr = 0;

    EEPROM.write(addr, o.timeClassO.currentlyActiveAlarm);
    addr = addr + 1;

    for(int i=0;i<3;i++)
    {
        // write alarmDay, alarmHour, alarmMinute, alarmSecond
        EEPROM.write(addr, o.RtcObjects[i].alarmDay);
        addr = addr + 1;
        EEPROM.write(addr,  o.RtcObjects[i].alarmHour);
        addr = addr + 1;
        EEPROM.write(addr, o.RtcObjects[i].alarmMinute);
        addr = addr + 1;
  }
}

#pragma region 
//Function for rendering and handling menu 1
encoderClass encoderClass::alarmsMenu(encoderClass o){
    

    if(o.menuNumber == 1){
        display.setCursor(0,rowHeights[0]);
        display.println("Alarms:");
        o.timeClassO.printAlarmStatus(o.RtcObjects[0], 0,o.timeClassO.currentlyActiveAlarm, rowHeights, weekdays);
        o.timeClassO.printAlarmStatus(o.RtcObjects[1], 1,o.timeClassO.currentlyActiveAlarm, rowHeights, weekdays);
        o.timeClassO.printAlarmStatus(o.RtcObjects[2], 2,o.timeClassO.currentlyActiveAlarm, rowHeights, weekdays);
        o.timeClassO.printAlarmStatus(o.RtcObjects[3], 3,o.timeClassO.currentlyActiveAlarm, rowHeights, weekdays);
    }
    else if(o.menuNumber == 11){ 
        o = alarmModification(o, o.timeClassO.alarmBeingModified, o.timeClassO.currentlyActiveAlarm);
    }
    return o;
}


//Function for rendering and handling menu 1
// encoderClass encoderClass::alarmModification(encoderClass o, int alarmNumber, int currentlyActiveAlarm){
encoderClass alarmModification(encoderClass o, int alarmNumber, int currentlyActiveAlarm){

    alarmNumber = alarmNumber - 1;
    int temporaryNumber;
    //Rendering of the modify Alarm submenu
    if(o.menuNumber == 11 && alarmNumber >= 0 && alarmNumber < 5){

        int numberBeingModified = o.timeClassO.numberBeingModified;
        display.setCursor(0,rowHeights[0]); 
        display.println("Set Alarm:");
        display.setCursor(0, rowHeights[1]);

        if(numberBeingModified == 0){
            temporaryNumber = o.RtcObjects[alarmNumber].alarmDay + o.encoderPosition;
        }
        else{
            display.println("Weekdays:");
            display.setCursor(55, rowHeights[1]);
            display.print(weekdays[o.RtcObjects[alarmNumber].alarmDay]);
        }

        display.setCursor(0, rowHeights[2]);
        display.println("Hour:");
        if(numberBeingModified == 1){
            temporaryNumber = o.RtcObjects[alarmNumber].alarmHour + o.encoderPosition;
        }
        else{
            display.setCursor(30, rowHeights[2]);
            display.print(o.RtcObjects[alarmNumber].alarmHour);
        }

        display.setCursor(0, rowHeights[3]);
        display.println("Minute:");
        if(numberBeingModified == 2){
            temporaryNumber = o.RtcObjects[alarmNumber].alarmMinute + o.encoderPosition * 5;//Modify the minutes with increments of 5
        }
        else{
            display.setCursor(45, rowHeights[3]);
            display.print(o.RtcObjects[alarmNumber].alarmMinute);
        }

        if(o.timeClassO.modifyBlinker == 4 && numberBeingModified < 3){
            o.timeClassO.modifyBlinker = 1;
        }
        //Render the blinker and the number being currently modified
        else if(o.timeClassO.modifyBlinker >= 1 && numberBeingModified < 3){

            //Special rendering conditions for weekdays
            if(numberBeingModified == 0){
                //Set the cursor in the starting position
                display.setCursor(0, rowHeights[1]);

                //Check that the selected number dosent allow an array overflow
                if(temporaryNumber >= 7 || temporaryNumber <= -1){
                    display.print("Number over limit!:");
                    display.setCursor(100, rowHeights[1]);
                    display.print(temporaryNumber);
                }
                else{
                    display.println("Weekdays:");
                    display.setCursor(55, rowHeights[1]);
                    display.print(weekdays[temporaryNumber]);
                }
            }
            else{
                //Set the cursor in the right place
                if(numberBeingModified == 1)
                    display.setCursor(30, rowHeights[2]);
                else if(numberBeingModified == 2)
                    display.setCursor(45, rowHeights[3]);

                //This is the regular displaying of a number currently being modified
                display.print(temporaryNumber);
            }
                
            o.timeClassO.modifyBlinker = o.timeClassO.modifyBlinker +1;
        }

        //Onclicks for modifying
        if(o.buttonState == 0 && o.buttonPressed == false){ 
            o.buttonPressed = true;
            //Reset the encoder position.
            o.encoderPosition = 0;
            o.oldPosition = 0;
            //Change the number that is being modified
            numberBeingModified++;

            //This gets called when the modifying menu is first opened
            if(numberBeingModified == 0){
                //set the encoder position as the current day being modified
                o.encoderPosition = o.RtcObjects[alarmNumber].alarmDay;
                
            }
            else if(numberBeingModified == 1){
                //Save the modified days in the runtime
                o.RtcObjects[alarmNumber].alarmDay = temporaryNumber;//o.RtcObjects[alarmNumber].alarmDay + o.encoderPosition;
            }
            else if(numberBeingModified == 2){
                //Save the modified hours in the runtime
                o.RtcObjects[alarmNumber].alarmHour = temporaryNumber;//o.RtcObjects[alarmNumber].alarmHour + o.encoderPosition;
            }
            else if(numberBeingModified == 3){
                //Save the modified minutes in the runtime
                o.RtcObjects[alarmNumber].alarmMinute = temporaryNumber;//o.RtcObjects[alarmNumber].alarmMinute + o.encoderPosition;
            }
            else if(numberBeingModified > 4){
                //Save the modifications
                //Only the currently active alarm gets saved to the RTC

                o.timeClassO.modifyAlarm(o.RtcObjects[alarmNumber], alarmNumber, currentlyActiveAlarm);//

                //Then save the alarms to the eeprom
                writeAlarmsToEEPROM(o);
                // o.RtcObjects[alarmNumber] = o.timeClassO.getAlarmStatus(o.RtcObjects[alarmNumber], alarmNumber);

                numberBeingModified = 0;
                o.searchNewAlarms = true;
                o.modifyInProgress = false;
                o.menuNumber = 1;
            }

        }
        //pass the value "back down" to the encoder class object, so that it would be saved.
        o.timeClassO.numberBeingModified = numberBeingModified; 
    }
    return o;
}

#pragma endregion

//Function for rendering and handling menu 2
encoderClass encoderClass::Menu2(encoderClass o){

    //What gets shown on the second menu
    if(o.menuNumber == 2){
        display.setCursor(0,rowHeights[0]); //Row 1
        display.println("Menu 2");
        display.setCursor(0,rowHeights[1]); //Row 2
        display.println("Menu 2");
    }
    return(o);
}