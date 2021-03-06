
const int potentiometer = 0;
const int reading_pause = 1;
//int val = 0;

void setup() {
  // Start the Serial which is connected with the USB MCU.
  // Make sure both baud rates are the same
  // you can go up to 2000000 for very fast data transmission.
  Serial.begin(2000000);
}

void loop() {
  // READ THE POTENTIOMETER VALUE
  int val = analogRead(potentiometer);
  val = map(val, 0,1023, 0,255);
  // Send random letters to the USB MCU
  Serial.write(val); // send a byte with the value val e.g 45 if val == 45
//  Serial.println(val); // debug to see what value we are reading.
  // take a short break before reading the value to actually read the correct next value
  delay(reading_pause);
}
