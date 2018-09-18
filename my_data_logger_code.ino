#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

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
int high_accel = -50;
int accel = 0;
int x_accel = 0;
int sensorPin = A0;    // select the input pin for the potentiometer   
int state,lastState = -1;

void setup() {
  lcd.begin(16, 2);
  lcd.print("ready to start");
  Serial.begin(9600);
  Serial.println("LIS3DH test!");
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("LIS3DH found!");

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

% State 0
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

% state 1 
// This borrows code from Examples->EEPROM->eeprom_read

byte value;

void state1Setup() {
    x_accel= EEPROM.read(0);
    lcd.print("Best Acceleration:");
    lcd.setCursor(0,1);
    lcd.print(x_accel);
}

void state1Loop() {
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
}

void doState1() {
  if (lastState != 1) { state1Setup(); }
  state1Loop();
}

% state 2 
// This borrows code from Examples->EEPROM->eeprom_write

String textarray = "hello cornell tech!";
int endAddr;

void state2Setup() {
      lis.read();
      sensors_event_t event; 
      lis.getEvent(&event);   
      accel = event.acceleration.x;
      if (accel > high_accel){
        high_accel = accel;
        EEPROM.write(0,high_accel);
      }
}

void state2Loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
}

void doState2() {
  if (lastState != 2) state2Setup();
  state2Loop();
}
