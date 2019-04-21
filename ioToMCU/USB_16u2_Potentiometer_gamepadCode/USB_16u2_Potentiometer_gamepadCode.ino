#include "HID-Project.h"
//#include "HID.h"


// DECLARE CONSTANTS
const int reading_pause = 10;
const int ignition = 1; // WHERE TO READ THE IGNITION FROM HARDWARE
const int starter = 2; // WHERE TO READ THE STARTER FROM HARDWARE


// DECLARE Varaibles
uint8_t ignitionValue = 0;
uint8_t ignitionControllerButton = 2;

uint8_t starterValue = 0;
uint8_t starterControllerButton = 3;

uint16_t prevHandbrake = 0;

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

  // ############   Potentiometer / handbrake
  // Check if any Serial data from the IO MCU was received (-1 if no data)
  uint16_t handbrake = Serial1.read();
  

  Serial.print(F("USB: "));
  Serial.print(handbrake);
  Serial.print(" :: ");
  Serial.println(map(handbrake, 0, 255, 0, 0xFFFF));

  //  To make this work. plug the handbrake into the computer. open controll board, select devices and printers. right click on hoodloader, properties, then settings, then calibrate. when the z-axis is next to callibrate pull the handbrake halfway, then start the calibration
  // pull to full and then release (no pull) then turn on the igniton to actuall save the calibration, (pressing next does not work), then, press next all the way, and finally finished to save.
  // Now unplugg the handbrake and replug it into the computer. now it should work. there is a bit of lag, but I'm working on it.
  handbrake = map(handbrake, 0, 255, 0, 50);

  // Move the Y axis on the "controller"
  if (prevHandbrake != handbrake){
    Gamepad.zAxis(handbrake);
    prevHandbrake = handbrake;
  }


// Tenningslaas
  // ############   ignition
  ignitionValue = digitalRead(ignition);
  Serial.print("IGNITION: ");
  Serial.println(ignitionValue);
  delay(100);
  
  // Press the ignition button on  a gamecontroller
  if (ignitionValue == 1) {
    Gamepad.press(ignitionControllerButton);
  }
  else {
    Gamepad.release(ignitionControllerButton);
  }
  // ############   starter
  starterValue = digitalRead(starter);
  Serial.print("Starter: ");
  Serial.println(starterValue);

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
