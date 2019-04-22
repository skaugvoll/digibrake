/*

TODO, on the IO chip,
map the values from pot. from 0 - 1023 to 0 - 255,
then send the value over the Serial.

On the USB - MCU chip, map the values from 0 - 255 to 0 - 9,
since it makes big interval into a small, requires bigger change on the value to "skip to next value on small interval".

Reason for / Idea of this changes is that the potentiometer sends values bigger then 255m but they are overflown and restarts from 0, over the serial
*/


#include "HID-Project.h"
//#include "HID.h"


// DECLARE CONSTANTS
const int reading_pause = 100;
const int ignition = 1; // WHERE TO READ THE IGNITION FROM HARDWARE
const int starter = 2; // WHERE TO READ THE STARTER FROM HARDWARE


// DECLARE Varaibles
uint8_t ignitionValue = 0;
uint8_t ignitionControllerButton = 2;

uint8_t starterValue = 0;
uint8_t starterControllerButton = 3;

uint16_t prevHandbrake = 0;


int treatValue(int data) {
    return (data * 9 / 256);
  }


void setup() {
  // Start the Serial1 which is connected with the IO MCU.
  // Make sure both baud rates are the same
  // you can go up to 2000000 for very fast data transmission.
  Serial1.begin(2000000);

  // Sends a clean report to the host. This is important on any Arduino type.
  // Keyboard.begin();

  // Start the USB Serial for debugging
  Serial.begin(2000000);

  // MARK THE DIGITAL INPUTS AS INPUTS
  pinMode(ignition, OUTPUT);    // Not sure why this has to be output, but if input, the value when ignition is OFF, is randomly alternating between 0 and 1
  pinMode(starter, OUTPUT);    // Not sure why this has to be output, but if input, the value when ignition is OFF or ON , is randomly alternating between 0 and 1

  // Sends a clean report to the host. This is important on any Arduino type.
  Gamepad.begin();
}

void loop() {
  // Relsease (unpress all the buttons);
//  Gamepad.release(ignitionControllerButton);
//  Gamepad.release(starterControllerButton);

  // ############   Potentiometer / handbrake
  // Check if any Serial data from the IO MCU was received (-1 if no data)
  uint16_t handbrake = Serial1.read();
  
  // If it's a character, print it!
//  if (c >= 'a' && c <= 'z') {
//    Serial.print(F("USB: "));
//    Serial.print(c);
//    Keyboard.print(c);
//  }
  //Serial.print(F("USB: "));
  Serial.print(handbrake);
  Serial.print(" :: ");
  //Serial.println(map(handbrake, 0, 255, 0, 0xFFFF));
  //Serial.println();
  
  // Map the potentiometer value from 0-255 to the full range of 16bit, to make the movement in direction noticable
  //handbrake = map(handbrake, 0, 255, 0, 60);
  handbrake = treatValue(handbrake);
  Serial.println(handbrake);
  // Move the Y axis on the "controller"
  //if (prevHandbrake != handbrake){
  Gamepad.zAxis(handbrake);
    //prevHandbrake = handbrake;
  //}


// Tenningslaas
  // ############   ignition
  ignitionValue = digitalRead(ignition);
  //Serial.print("IGNITION: ");
  //Serial.println(ignitionValue);
  delay(50);
  
  // Press the ignition button on  a gamecontroller
  if (ignitionValue == 1) {
    Gamepad.press(ignitionControllerButton);
  }
  else {
    Gamepad.release(ignitionControllerButton);
  }
  // ############   starter
  starterValue = digitalRead(starter);
  //Serial.print("Starter: ");
  //Serial.println(starterValue);

  // Press the starterbutton button on a gamecontroller
  if (starterValue == 1){
    Gamepad.press(starterControllerButton);
  }
  else {
    Gamepad.release(starterControllerButton);
  }
  
  // Functions above only set the values.
  // This writes the report to the host.
  Gamepad.write();
  
  // Delay reading because the IO chip has to have a pause to get the correct potentionmeter value 
  delay(reading_pause);

  
}
