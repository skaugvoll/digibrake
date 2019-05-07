/*

*/

// Import the joystick library
#include <Joystick.h>

// DECLARE CONSTANTS AND HARDWARE COMPONENTS
const int reading_pause = 1;
const int handbrakeINPUT   = A0; // WHERE TO READ THE POTENTIOMETER AKA HANDBRAKE VALUES
const int ignition = 1; // WHERE TO READ THE IGNITION FROM HARDWARE
const int starter = 2; // WHERE TO READ THE STARTER FROM HARDWARE
const int rLED = 12; // RED LED
const int yLED = 13; // Yellow/Orange LED

// DECLARE VARIABLES AND BUTTON MAPPING
uint8_t ignitionValue = 0;
uint8_t ignitionControllerButton = 2;

uint8_t starterValue = 0;
uint8_t starterControllerButton = 3;

// Create the Joystick object
Joystick_ Joystick;

void setup() {
  // Start the USB Serial for debugging
  Serial.begin(2000000);

  // MARK THE DIGITAL INPUTS AS INPUTS
  pinMode(ignition, OUTPUT);    // Not sure why this has to be output, but if input, the value when ignition is OFF, is randomly alternating between 0 and 1
  pinMode(starter, OUTPUT);    // Not sure why this has to be output, but if input, the value when ignition is OFF or ON , is randomly alternating between 0 and 1
  pinMode(rLED, OUTPUT);
  pinMode(yLED, OUTPUT);

  // Sends a clean report to the host. This is important on any Arduino type.
  Joystick.begin();

  // Light up the leds, can do it here, since we wont be turning them off.
  digitalWrite(rLED, HIGH); 
  digitalWrite(yLED, HIGH);
}

void loop() {
///////////////////////////////////////////////// HANDBRAKE ///////////////////////////////////////////////
  uint16_t handbrake = analogRead(handbrakeINPUT);
  
  //Serial.print(F("USB: "));
  Serial.print(handbrake);
  Serial.print(" :: ");
  Serial.println(handbrake);

  // send the handbrake signal to the computer as joystick throttle representing an AXIS
  Joystick.setThrottle(handbrake);

//////////////////////////////////////////////// Tenningslaas ///////////////////////////////////////////////
  // ############   ignition
  ignitionValue = digitalRead(ignition);
  //Serial.print("IGNITION: ");
  //Serial.println(ignitionValue);
  delay(reading_pause);
  
  // Press the ignition button on  a gamecontroller
  if (ignitionValue == 1) {
    Joystick.pressButton(ignitionControllerButton);
  }
  else {
    Joystick.releaseButton(ignitionControllerButton);
  }
  // ############   starter
  starterValue = digitalRead(starter);
  //Serial.print("Starter: ");
  //Serial.println(starterValue);

  // Press the starterbutton button on a gamecontroller
  if (starterValue == 1){
    Joystick.pressButton(starterControllerButton);
  }
  else {
    Joystick.releaseButton(starterControllerButton);
  }
  
  // Delay reading because the IO chip has to have a pause to get the correct potentionmeter value 
  delay(reading_pause);

  
}
