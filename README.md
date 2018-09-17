# Data Logger (and using cool sensors!)

*A lab report by Brian Pfaff*

## The Report

## Part A.  Writing to the Serial Monitor
 
**a. Based on the readings from the serial monitor, what is the range of the analog values being read?**
 
 The range is 0 to 1023.
 
**b. How many bits of resolution does the analog to digital converter (ADC) on the Arduino have?**

10 bits of resolution.

## Part B. RGB LED

**How might you use this with only the parts in your kit? Show us your solution.**

We could connect two of the 225 ohm resistors in series to the red pin in order to give it a higher resistance than the blue and green pins where we would only connect one 225 ohm resistor.


## Part C. Voltage Varying Sensors 
 
### 1. FSR, Flex Sensor, Photo cell, Softpot

**a. What voltage values do you see from your force sensor?**

**b. What kind of relationship does the voltage have as a function of the force applied? (e.g., linear?)**

The relationship is not linear, it is more of a log function with a very fast increase in voltage with minimal force applied however harder the you push, the less the gain in voltage is. 

**c. Can you change the LED fading code values so that you get the full range of output voltages from the LED when using your FSR?**

Yes, I put if statements in the loop with each of them corresponding to a different color in the range of the sensor. 
``` void loop()
{
  a_read = analogRead(A0);
  if (a_read <100){
  setColor(255, 0, 0);
  }
  if (a_read> 100 && a_read<250) {
  setColor(0, 255, 0);  // green
  }
  if (a_read>250 && a_read<500) {
  setColor(0, 0, 255);  // 
  }
  if (a_read> 500 && a_read<900) {
  setColor(80, 0, 80);  // 
  }
  if (a_read> 900) {
  setColor(0, 255, 255);  // aqua
  }
}
```

**d. What resistance do you need to have in series to get a reasonable range of voltages from each sensor?**

**e. What kind of relationship does the resistance have as a function of stimulus? (e.g., linear?)**

### 2. Accelerometer
 
**a. Include your accelerometer read-out code in your write-up.**

### 3. IR Proximity Sensor

**a. Describe the voltage change over the sensing range of the sensor. A sketch of voltage vs. distance would work also. Does it match up with what you expect from the datasheet?**

**b. Upload your merged code to your lab report repository and link to it here.**

## Optional. Graphic Display

**Take a picture of your screen working insert it here!**

## Part D. Logging values to the EEPROM and reading them back
 
### 1. Reading and writing values to the Arduino EEPROM

**a. Does it matter what actions are assigned to which state? Why?**

**b. Why is the code here all in the setup() functions and not in the loop() functions?**

**c. How many byte-sized data samples can you store on the Atmega328?**

**d. How would you get analog data from the Arduino analog pins to be byte-sized? How about analog data from the I2C devices?**

**e. Alternately, how would we store the data if it were bigger than a byte? (hint: take a look at the [EEPROMPut](https://www.arduino.cc/en/Reference/EEPROMPut) example)**

**Upload your modified code that takes in analog values from your sensors and prints them back out to the Arduino Serial Monitor.**

### 2. Design your logger
 
**a. Insert here a copy of your final state diagram.**

### 3. Create your data logger!
 
**a. Record and upload a short demo video of your logger in action.**
