// project title: cloudy night
// description: interactive led lighting and data logging device
// by: shuyang huang, shiori osakata, nick kunz
// advisor: dr. anthony vanky
// urban informatics II, columbia university gsapp

//---- requirements ----//

// data logger
#include <SPI.h>
#include <SD.h>

// serial clock
#include <RTClib.h>

// human sensor
#include <Wire.h>
#include <SparkFun_AK975X_Arduino_Library.h>

// lights
#include <Adafruit_WS2801.h>
#include <SPI.h>
#ifdef __AVR_ATtiny85__
#include <avr/power.h>
#endif

// hook human sensors object to the library
AK975X movementSensor;

// hook serial clock
RTC_DS3231 rtc;

// initialize human sensor variables
int ir1, ir2, ir3, ir4, upValue, temperature;
int ir1map, ir2map, ir3map, ir4map;

// sd data logger shield pin 10
const int chipSelect = 10;

// initialize pins
int dataPin = 2;
int clockPin = 3;

// first variable to the number of pixels (25 = 25 pixels in a row)
Adafruit_WS2801 strip = Adafruit_WS2801(25, dataPin, clockPin);

//---- setup ----//

// device setup
void setup() {

  // open serial port
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start sd data logger
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    while (1);
  }

  // sd serial clock
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // start human sensor
  Wire.begin();
  if (movementSensor.begin() == false) {
    Serial.println("Device not found. Check wiring.");
    while (1);
  }

  // setup led
  strip.begin();
  strip.show();  // led contents (to start they are all 'off')

} // close device setup

//---- program ----//

// device program
void loop() {

  // initialize sensor
  if (movementSensor.available()) {
    float ir1 = movementSensor.getIR1();
    float ir2 = movementSensor.getIR2();
    float ir3 = movementSensor.getIR3();
    float ir4 = movementSensor.getIR4();
    float upValue = ir1 + ir2 + ir3 + ir4;
    float tempF = movementSensor.getTemperatureF();

    // led lights
    if (ir1 + ir2 + ir3 + ir4 > 4500) {
      colorChange5();
    }

    else if (ir1 + ir2 + ir3 + ir4 > 3500) {
      colorChange4();
    }

    else if (ir1 + ir2 + ir3 + ir4 > 2400) {
      colorChange3();
    }

    else if (ir1 + ir2 + ir3 + ir4 > 1300) {
      colorChange2();
    }

    else {
      blueBlinkCycle(10);
    }

    // dummy register after new data is read
    movementSensor.refresh();

    // open data log file (note: only one file can be open at a time)
    File dataFile = SD.open("cloudy1.csv", FILE_WRITE);

    // log data collection
    if (dataFile) {
      dataFile.print(ir1);
      dataFile.print(',');
      dataFile.print(ir2);
      dataFile.print(',');
      dataFile.print(ir3);
      dataFile.print(',');
      dataFile.print(ir4);
      dataFile.print(',');
      dataFile.print(tempF);
      dataFile.print(',');

      // log date and time
      DateTime now = rtc.now();
      dataFile.print(now.year(), DEC);
      dataFile.print('/');
      dataFile.print(now.month(), DEC);
      dataFile.print('/');
      dataFile.print(now.day(), DEC);
      dataFile.print(',');
      dataFile.print(now.hour(), DEC);
      dataFile.print(':');
      dataFile.print(now.minute(), DEC);
      dataFile.print(':');
      dataFile.print(now.second(), DEC);
      dataFile.println();

      // stop data logging
      dataFile.close();

    } // close data collection

    // data logging fail warning message
    else {
      Serial.println("error opening datalog.txt");
    }

    // view data collection in serial port
    Serial.print("\t1:Up[");
    Serial.print(ir1);
    Serial.print("]\t2:Left[");
    Serial.print(ir2);
    Serial.print("]\t3:Down[");
    Serial.print(ir3);
    Serial.print("]\t4:Right[");
    Serial.print(ir4);
    Serial.print("]\t5:Sum[");
    Serial.print(upValue);
    Serial.print("]\ttempF[");
    Serial.print(tempF);
    Serial.print("]\t");

    // view date and time in serial port
    DateTime now = rtc.now();
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

  } // close human sensor

} // close device program

// create colorChange
void colorChange5(void) {

  colorWipe(Color(255, 0, 0), 4);      // red
  colorWipe(Color(255, 50, 0), 4);     // orange
  colorWipe(Color(255, 255, 0), 4);    // yellow
  colorWipe(Color(255, 255, 255), 4);  // white
  colorWipe(Color(0, 255, 0), 4);      // green
  colorWipe(Color(0, 255, 255), 4);    // aqua
  colorWipe(Color(0, 0, 255), 4);      // blue
  colorWipe(Color(80, 0, 80), 4);      // purple
  colorWipe(Color(255, 20, 20), 4);    // pink
}

// create colorChange
void colorChange4(void) {

  colorWipe(Color(255, 255, 255), 6);  // white
  colorWipe(Color(0, 255, 0), 6);      // green
  colorWipe(Color(0, 255, 255), 6);    // aqua
  colorWipe(Color(0, 0, 255), 6);      // blue
  colorWipe(Color(80, 0, 80), 6);      // purple
  colorWipe(Color(255, 20, 20), 6);    // pink
}

// create colorChange
void colorChange3(void) {

  colorWipe(Color(0, 255, 255), 12);    // aqua
  colorWipe(Color(0, 0, 255), 12);      // blue
  colorWipe(Color(80, 0, 80), 12);      // purple
}

// create colorChange
void colorChange2(void) {

  colorWipe(Color(0, 255, 255), 18);    // aqua
  colorWipe(Color(0, 0, 255), 18);      // blue
}

// create colorChange
void colorChange1(void) {

  colorWipe(Color(0, 255, 255), 36);    // aqua
}


//---- functions ----//


// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b) {

  uint32_t c;

  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

// create colorWipe
void colorWipe(uint32_t c, uint8_t wait) {

  int i;

  for (i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

// blue color wheel
uint32_t Wheel(byte WheelPos) {

  if (WheelPos < 170) {
      WheelPos -= 85;
      return Color(0, 255 - WheelPos, 255);
  }
  
  else {
  }
}

// blue blink color cycle
void blueBlinkCycle(uint8_t wait) {

  int i, j;

  for (j = 0; j < 256 * 1; j++) {   // 1 cycle of all 25 colors in the wheel
    for (i = 0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i * 256 / strip.numPixels()) + j) % 256) );
    }
    
    strip.show();   // write all the pixels out
    delay(wait);
  }
}
// end

/*****************************************************************************
Example sketch for driving Adafruit WS2801 pixels!
  Designed specifically to work with the Adafruit RGB Pixels!
  12mm Bullet shape ----> https://www.adafruit.com/products/322
  12mm Flat shape   ----> https://www.adafruit.com/products/738
  36mm Square shape ----> https://www.adafruit.com/products/683
  These pixels use SPI to transmit the color data, and have built in
  high speed PWM drivers for 24 bit color per pixel
  2 pins are required to interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!
  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
*****************************************************************************/
