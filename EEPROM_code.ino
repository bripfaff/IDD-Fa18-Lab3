#include <Wire.h>
#include "Adafruit_VCNL4010.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

Adafruit_VCNL4010 vcnl;
#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
// Used for hardware & software SPI
#define LIS3DH_CS 10
Adafruit_LIS3DH lis = Adafruit_LIS3DH();
#include <EEPROM.h>

const int numStates = 3;
const int sensorMin =0;
const int sensorMax = 1024;
const int EEPROMSIZE=1024;
int ledPin = LED_BUILTIN; 

int sensorPin = 0;    // select the input pin for the potentiometer   
int state,lastState = -1;

void setup() {
  Serial.begin(9600);
  Serial.println("VCNL4010 test");
  Serial.println("LIS3DH test!");

  if (! vcnl.begin()){
    Serial.println("Sensor not found :(");
    while (1);
  }
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("LIS3DH found!");
  Serial.println("Found VCNL4010");

  lis.setRange(LIS3DH_RANGE_4_G);
  Serial.print("Range = "); Serial.print(2 << lis.getRange());  
  Serial.println("G");
}


void loop() {
   state = map(analogRead(sensorPin), sensorMin, sensorMax, 0, numStates);

  // do something different depending on the 
  // range value:
  switch (state) {
  case 0:
    doState0();    
    break;
  case 1:
    doState1();
    break;
  case 2:    
    doState2();
    break;
  } 
  lastState = state;

}


% STATE 0 code
// This borrows code from Examples->EEPROM->eeprom_clear

void state0Setup() {
  digitalWrite(ledPin, LOW);
  Serial.println("Clearing EEPROM");
  //if any of the pin settings for the different states differed for the different states, you could change those settings here.
  for (int i = 0; i < EEPROMSIZE; i++) {
    EEPROM.write(i, 0);
  }

  // turn the LED on when we're done
  Serial.println("EEPROM cleared");
}

void state0Loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
}

void doState0() {
  if (lastState != 0) { state0Setup(); }
  state0Loop();
}

% STATE 1 code
// This borrows code from Examples->EEPROM->eeprom_read

byte value;

void state1Setup() {
  Serial.println("Reading from EEPROM");

  Serial.print("\t\tX: "); Serial.print(EEPROM.read(0));
  Serial.print(" \tY: "); Serial.print(EEPROM.read(20)); 
  Serial.print(" \tZ: "); Serial.print(EEPROM.read(40)); 

  Serial.print("\t\tX: "); Serial.print(EEPROM.read(60));
  Serial.print(" \tY: "); Serial.print(EEPROM.read(80)); 
  Serial.print(" \tZ: "); Serial.print(EEPROM.read(100));   

  Serial.print("Ambient: "); Serial.println(EEPROM.read(120));
  Serial.print("Proximity: "); Serial.println(EEPROM.read(140));
  Serial.println();

  Serial.println("Done reading from EEPROM");
}

void state1Loop() {
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
}

void doState1() {
  if (lastState != 1) { state1Setup(); }
  state1Loop();
}

% State 2 code:
// This borrows code from Examples->EEPROM->eeprom_write

String textarray = "hello cornell tech!";
int endAddr;

void state2Setup() {
  lis.read();
  digitalWrite(ledPin, LOW);
  Serial.println("Writing to EEPROM");
  
  //if any of the pin settings for the different states differed for the different states, you could change those settings here.
  EEPROM.put(0,lis.x);
  EEPROM.put(20,lis.y);
  EEPROM.put(40,lis.z);
  sensors_event_t event; 
  lis.getEvent(&event);
  EEPROM.put(60,event.acceleration.x);
  EEPROM.put(80,event.acceleration.y);
  EEPROM.put(100,event.acceleration.z);
  EEPROM.put(120,vcnl.readAmbient());
  EEPROM.put(140,vcnl.readProximity());

  Serial.println("String committed to EEPROM!");
}

void state2Loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
}

void doState2() {
  if (lastState != 2) state2Setup();
  state2Loop();
}

