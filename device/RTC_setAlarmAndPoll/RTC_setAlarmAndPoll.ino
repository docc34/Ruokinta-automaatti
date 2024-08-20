#include <DS3231.h>
#include <Wire.h>

DS3231 myRTC;

void setup() {
  Wire.begin();

  myRTC.turnOffAlarm(1);
  // aseta hälytys. (kk päivä/viikonpäivä, tunnit,minuutit,sekunnit, hälytysbitit, kk päivä/viikonpäivä, 12/24 aika, AM/PM)
  myRTC.setA1Time(16, 20, 43, 20, 0b01100000, false, false, false);
  myRTC.turnOnAlarm(1);
  myRTC.checkIfAlarm(1);

  Serial.begin(9600);
}

void loop() {
  // static variable to keep track of LED on/off state
  static byte state = false;

  // tarkista onko hälytys 1 tapahtunut
  if (myRTC.checkIfAlarm(1, false)) {
    state = ~state;
    digitalWrite(LED_BUILTIN, state);

    Serial.print("HÄLYTYS!");

    // nollaa hälytys 1
    myRTC.checkIfAlarm(1, true);
  }

  // Loop delay to emulate other running code
  delay(10);
}
