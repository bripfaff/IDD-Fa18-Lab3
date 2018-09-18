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
   lis.read();      // get X Y and Z data at once
   // Then print out the raw data
   Serial.print("X:  "); Serial.print(lis.x); 
   Serial.print("  \tY:  "); Serial.print(lis.y); 
   Serial.print("  \tZ:  "); Serial.print(lis.z); 

   /* Or....get a new sensor event, normalized */ 
   sensors_event_t event; 
   lis.getEvent(&event);
  
   /* Display the results (acceleration is measured in m/s^2) */
   Serial.print("\t\tX: "); Serial.print(event.acceleration.x);
   Serial.print(" \tY: "); Serial.print(event.acceleration.y); 
   Serial.print(" \tZ: "); Serial.print(event.acceleration.z); 
   Serial.println(" m/s^2 ");

   Serial.println();
 
   delay(200); 
   Serial.print("Ambient: "); Serial.println(vcnl.readAmbient());
   Serial.print("Proximity: "); Serial.println(vcnl.readProximity());
   delay(100);
}
