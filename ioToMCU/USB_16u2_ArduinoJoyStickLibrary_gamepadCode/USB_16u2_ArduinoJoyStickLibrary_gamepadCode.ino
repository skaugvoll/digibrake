//#include "HID-Project.h"
//#include "HID.h"
#include "Joystick.h"

// DECLARE CONSTANTS
const int reading_pause = 100;
const int ignition = 1; // WHERE TO READ THE IGNITION FROM HARDWARE
const int starter = 2; // WHERE TO READ THE STARTER FROM HARDWARE
const uint8_t OFF = 0; // button not pressed
const uint8_t ON = 1; // button pressed


// DECLARE Varaibles
uint8_t ignitionValue = 0;
uint8_t ignitionControllerButton = 2;

uint8_t starterValue = 0;
uint8_t starterControllerButton = 3;

// Create the Joystick
Joystick_ Joystick;


void setup() {
  // Start the Serial1 which is connected with the IO MCU.
  // Make sure both baud rates are the same
  // you can go up to 2000000 for very fast data transmission.
  Serial1.begin(2000000);

  // Sends a clean report to the host. This is important on any Arduino type.
//  Keyboard.begin();

  // Start the USB Serial for debugging
  Serial.begin(2000000);

  // MARK THE DIGITAL INPUTS AS INPUTS
  pinMode(ignition, OUTPUT);    // Not sure why this has to be output, but if input, the value when ignition is OFF, is randomly alternating between 0 and 1
  pinMode(starter, OUTPUT);    // Not sure why this has to be output, but if input, the value when ignition is OFF or ON , is randomly alternating between 0 and 1

  // Initialize Joystick library
  // Sends a clean report to the host. This is important on any Arduino type.
  Joystick.begin();

}

void loop() {
  // ############   Potentiometer / handbrake
  // Check if any Serial data from the IO MCU was received (-1 if no data)
  uint16_t handbrake = Serial1.read();
  
  Serial.print(F("USB: "));
  Serial.print(handbrake);

  
  // Map the potentiometer value from 0-255 to the full range of 16bit, to make the movement in direction noticable
  handbrake = map(handbrake, 0, 255, 0, 1023);
  Serial.print(" :: ");
  Serial.println(handbrake);
  
  // Move the Y axis on the "controller"
  Joystick.setThrottle(handbrake);  

  
// Tenningslaas
  // ############   ignition
  ignitionValue = digitalRead(ignition);
  Serial.print("IGNITION: ");
  Serial.println(ignitionValue);
  delay(10);
  
  // Press the ignition button on  a gamecontroller
  if (ignitionValue == 1) {
    Joystick.setButton(ignitionControllerButton, ON);
  }
  else {
    Joystick.setButton(ignitionControllerButton, OFF);
  }
  // ############   starter
  starterValue = digitalRead(starter);
  Serial.print("Starter: ");
  Serial.println(starterValue);

  // Press the starterbutton button on a gamecontroller
  if (starterValue == 1){
    Joystick.setButton(starterControllerButton, ON);
  }
  else {
    Joystick.setButton(starterControllerButton, OFF);
  }
  
  // Functions above only set the values.
  // This writes the report to the host.
  
  
  // Delay reading because the IO chip has to have a pause to get the correct potentionmeter value 
  delay(reading_pause);
  
}
