#include "Keyboard.h"
#include "HID.h"


// DECLARE CONSTANTS
const int reading_pause = 100;
const int ignition = 1;
const int starter = 2;


// DECLARE Varaibles
int ignitionValue = 0;
int starterValue = 0;


void setup() {
  // Start the Serial1 which is connected with the IO MCU.
  // Make sure both baud rates are the same
  // you can go up to 2000000 for very fast data transmission.
  Serial1.begin(115200);

  // Sends a clean report to the host. This is important on any Arduino type.
//  Keyboard.begin();

  // Start the USB Serial for debugging
  Serial.begin(115200);

  // MARK THE DIGITAL INPUTS AS INPUTS
  pinMode(ignition, OUTPUT);    // Not sure why this has to be output, but if input, the value when ignition is OFF, is randomly alternating between 0 and 1
  pinMode(starter, OUTPUT);    // Not sure why this has to be output, but if input, the value when ignition is OFF or ON , is randomly alternating between 0 and 1

}

void loop() {
  // Check if any Serial data from the IO MCU was received
  int v = Serial1.read();
  

  // If it's a character, print it!
//  if (c >= 'a' && c <= 'z') {
//    Serial.print(F("USB: "));
//    Serial.print(c);
//    Keyboard.print(c);
//  }
  Serial.print(F("USB: "));
  Serial.println(v);
  
// Tenningslaas
  //ignition
  ignitionValue = digitalRead(ignition);
  Serial.print("IGNITION: ");
  Serial.println(ignitionValue);
  delay(100);
  // starter
  starterValue = digitalRead(starter);
  Serial.print("Starter: ");
  Serial.println(starterValue);
  
  // Delay reading because the IO chip has to have a pause to get the correct potentionmeter value 
  delay(reading_pause);

  

  
}
