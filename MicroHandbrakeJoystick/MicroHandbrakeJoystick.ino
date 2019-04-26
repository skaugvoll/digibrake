#include <Joystick.h>

const int potMeter = A0;

// DECLARE joystick library and gamecontroller
Joystick_ Joystick;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  
  Joystick.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(potMeter);
  Joystick.setThrottle(val);
  Serial.println(val);
  delay(1);  
}
