#include "encoderOledControl.h"
#include "encoderClass.h"

encoderClass setModificationSettings (encoderClass o, int alarmBeingModified){
      //zero the cursor settings, since they are used in the modification.
  o.cursorPosition = 0;
  o.encoderPosition = 0;
  //Open the modifying menu
  o.menuNumber = 11;
  //Define that the modification has begun      
  o.modifyInProgress = true;      
  //Define the alarm number that is being modified
  o.timeClassO.alarmBeingModified = alarmBeingModified;

  return o;
}

encoderClass EncoderController(encoderClass o){

  //Define the controlling variables for reading the encoder
  if (o.newPosition > o.oldPosition){
    o.encoderPosition++;
    o.oldPosition = o.newPosition;
    o.encoderString = "Ylos "+String(o.newPosition);
    if(o.cursorPosition > 1)
      o.cursorPosition--;
  }
  else if(o.newPosition < o.oldPosition){
    o.encoderPosition--;
    o.oldPosition = o.newPosition;
    o.encoderString = "Alas "+String(o.newPosition);

    if(o.cursorPosition < 6) //Maximum number of rows per menu
      o.cursorPosition++;
  }

  //Each menu has their own render functions, that have the render functions 
  //Most onclicks have been transfered to this file to save space, except for the alarm modification onclick/handling
  o = o.mainMenu(o);

  o = o.alarmsMenu(o);

  o = o.Menu2(o);

  if(o.buttonState == 0 && o.buttonPressed == false){ //Main menus Row 2 
      //all the onclicks for the menus
      if(o.menuNumber == 1){ 
        o.buttonPressed = true;

        //Onclick for alarms menus 1 row
        if(o.cursorPosition == 1){
            o.menuNumber = 0;
        }
        //Onclick for alarms menus 2 row
        if(o.cursorPosition == 2){
          //Function that sets the correct settings for the alarm that is going to be modified
          o = setModificationSettings(o,1);
        }
        //Onclick for alarms menus 3 row
        if(o.cursorPosition == 3){
          o = setModificationSettings(o,2);
        }
        //Onclick for alarms menus 4 row
        if(o.cursorPosition == 4){
          o = setModificationSettings(o,3);
        }
        //Onclick for alarms menus 5 row
        if(o.cursorPosition == 5){
          o = setModificationSettings(o,4);
        }
    }
    else if(o.menuNumber == 2){
      o.buttonPressed = true;

      //onclick for Menu2's 1 row
      if(o.cursorPosition == 1){
          o.menuNumber = 0;
      }
    }
  }
  //The buttonPressed boolean lets the button get pressed only once during every run
  if(o.buttonPressed == true)
    o.buttonPressed = false;
  
  if(o.buttonState == 0 && o.modifyInProgress == false){
    //Reset the cursor to top on each click
    o.cursorPosition = 1;
  }

  
  //Each menu should have their own component, with their own onclicks
  renderCursor(o);
  //Display.display() needs to be called mainly only at the end of the code
  display.display();
  return o;
}

void renderCursor(encoderClass o){
  //Function for rendering the cursor
  if(o.modifyInProgress == false){
      char cursor = '*';
      //Controls which row is "selected". Cursorposition = selectedRow;
      if(o.cursorPosition == 1){ //Row 1
          display.setCursor(80,rowHeights[0]);
          display.println(cursor);
      }
      else if(o.cursorPosition == 2){//Row 2
          display.setCursor(80,rowHeights[1]);
          display.println(cursor);
      }
      else if(o.cursorPosition == 3){//Row 3
          display.setCursor(80,rowHeights[2]);
          display.println(cursor);
      }
      else if(o.cursorPosition == 4){//Row 4
          display.setCursor(80,rowHeights[3]);
          display.println(cursor);
      }
      else if(o.cursorPosition == 5){//Row 4
          display.setCursor(80,rowHeights[4]);
          display.println(cursor);
      }
  }
}