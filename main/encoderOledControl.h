// #include <Adafruit_SSD1306.h>
#include "Adafruit_SSD1306_Modified.h"
#include "encoderClass.h"

#ifndef encoderOledControl_h
#define encoderOledControl_h

const int rowHeights[] = {0,14,26,38,50};
encoderClass EncoderController(encoderClass encoder);

#endif //encoderOledControl