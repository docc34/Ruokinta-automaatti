#include "setup.h"
#include "encoderOledControl.h"
#include <Encoder.h>
#include <Wire.h>
#include <DS3231.h>
#include "encoderClass.h"
#include "timeClass.h"
#include "RtcObject.h"
#include "Adafruit_SSD1306_Modified.h"
#include <EEPROM.h>
//Arduino Unossa
//Encoder myEnc(2, 3);

//Leonardossa 
Encoder myEnc(0, 1);

encoderClass encoder;
timeClass timeClassObject;

// RtcObject RtcObjects[4];
DS3231 myRTC;


const int encoderButton = 4;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3c ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306_Modified display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup_lcd(){
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
}

//Read data from EEPROM to encoder class
encoderClass readAlarmsFromEEPROM()
{
    encoderClass o;
    //Read the currently active alarm and return it with the encoder class
    int addr = 0;
    o.timeClassO.currentlyActiveAlarm = EEPROM.read(addr);
    addr = addr + 1;

    for(int i=0;i<3;i++)
    {
        o.RtcObjects[i].alarmDay = EEPROM.read(addr);
        addr = addr + 1;
        o.RtcObjects[i].alarmHour = EEPROM.read(addr);
        addr = addr + 1;
        o.RtcObjects[i].alarmMinute =  EEPROM.read(addr);
        addr = addr + 1;
    }

    return o;
}

// the setup function runs once when you press reset or power the board
void setup()
{
  Serial.begin(9600);
  delay(4000);
  Wire.begin();
  //Setups lcd screens settings
  setup_lcd();

  //Read data from eeprom during startup
  encoder = readAlarmsFromEEPROM();
  timeClassObject = encoder.timeClassO;

  myRTC.turnOffAlarm(2);
  // aseta hälytys. (kk päivä/viikonpäivä, tunnit,minuutit,sekunnit, hälytysbitit, kk päivä/viikonpäivä, 12/24 aika, AM/PM)
  // myRTC.setA1Time(2, 21, 57, 02, 0b01100000, false, false, false);
  myRTC.turnOnAlarm(2);
  myRTC.checkIfAlarm(2);

  //Only set for testing alarm
  pinMode(LED_BUILTIN, OUTPUT);


  //Set encoder button pin
  pinMode(encoderButton,INPUT);
}


// the loop function runs over and over again forever
void loop()
{
  display.display();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  //This is set so that the alarm string is made, and the current alarm is being searched from the RTC module
  //And it dosent work
  encoder.searchNewAlarms = true;

  //Only set for testing alarm
  digitalWrite(LED_BUILTIN, LOW);
  int i = 0;
  while (i < 100000)
  {
    //Read state of the encoder button
    encoder.buttonState = digitalRead(encoderButton);
    
    encoder.newPosition = myEnc.read() / 4; //Divide the reading by 4 because our encoder jumps 4 readings with 1 click

    //Pass the saved timeclassobject data back to the timeclass every run
    encoder.timeClassO = timeClassObject;

    display.clearDisplay(); // Clear display buffer

    //This function handles the controlling of the menu's through the encode class
    //The class it self has functions for each menu with their rendering
    //And the parameters used in the controlling of these menus are stored in the encode class
    encoder = EncoderController(encoder);

    //This is done to save the timeclass data on each "run"
    timeClassObject = encoder.timeClassO;

    //JOS ON ONGELMIA KOODIN UPLOADAAMISESSA
    //This actually has purpose. If you open the serial monitor connection, and then upload code. It will most likely upload.
    Serial.println("A");
    Serial.println(timeClassObject.currentlyActiveAlarm);
    
    //Tarkistaa onko RTC:n hälytys lauennut
    if (myRTC.checkIfAlarm(2, false)) {

      //Move to the next active alarm
      int activeAlarm = timeClassObject.currentlyActiveAlarm;
      if(activeAlarm >= 0 && activeAlarm < 3){
        activeAlarm = activeAlarm + 1;
      }
      else{
        //If alarm is outside of active alarm range start from the first alarm
        activeAlarm = 0;
      }

      //Save the currently active alarm to the RTC module
      timeClassObject.modifyAlarm(encoder.RtcObjects[activeAlarm],activeAlarm,activeAlarm);

      //Save the changed active alarm to the EEPROM, the currently active alarm is saved in slot 0
      EEPROM.write(0, activeAlarm);
      //And save the change to the current runtime, since the eeprom is only read on startup
      timeClassObject.currentlyActiveAlarm = activeAlarm;

      //Tähän vielä servokoodit
      Serial.println("!");
      Serial.println("HÄLYTYS!");
      Serial.println("!");

      //Only set for testing alarm
      digitalWrite(LED_BUILTIN, HIGH);

      // nollaa hälytys 2
      myRTC.checkIfAlarm(2, true);
    }

    //Delay for running code
    delay(150);
  }
}