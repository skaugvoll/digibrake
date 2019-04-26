#include <Joystick.h>

const int potMeter = A0;
const int ignition = 8; // WHERE TO READ THE IGNITION FROM HARDWARE
const int starter = 9; // WHERE TO READ THE STARTER FROM HARDWARE

// DECLARE Varaibles
uint8_t ignitionValue = 0;
uint8_t ignitionControllerButton = 2;

uint8_t starterValue = 0;
uint8_t starterControllerButton = 3;

// DECLARE joystick library and gamecontroller
Joystick_ Joystick;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  
  Joystick.begin();
  
  // MARK THE DIGITAL INPUTS AS INPUTS
  pinMode(ignition, INPUT);    // Not sure why this has to be output, but if input, the value when ignition is OFF, is randomly alternating between 0 and 1
  pinMode(starter, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(potMeter);
//  Serial.print("E-brake");
//  Serial.println(val);
  Joystick.setThrottle(val);
  delay(1);

  // Tenningslaas
  // ############   ignition
  ignitionValue = digitalRead(ignition);
//  Serial.print("IG: ");
//  Serial.println(ignitionValue);
  
  // Press the ignition button on  a gamecontroller
  if (ignitionValue == 1) {
   Joystick.pressButton(ignitionControllerButton);
  }
  else {
    Joystick.releaseButton(ignitionControllerButton);
  }

  delay(1);



  
  // ############   starter
  starterValue = digitalRead(starter);
  Serial.print("ST: ");
  Serial.println(starterValue);

  // Press the starterbutton button on a gamecontroller
  if (starterValue == 1){
    Joystick.pressButton(starterControllerButton);
  }
  else {
    Joystick.releaseButton(starterControllerButton);
  }

  delay(1);
  


  
}
