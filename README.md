# Using an Arduino Uno as USB device.

The first thing we need to do is reprogram the usb chip on the arduino, the chip is called 16u2 and we are going to use HoodLoader2 to do this.

** HUGE THANK YOU TO NICO HOOD FOR HIS AMAZING WORK ON THE HOODLOADER2 PROJECT! **

## Installing the neccessary software and Hardware
**TODO** copy text from the other tutorial I wrote somewear.
Short; install hoodloader2 libarry on Arduino IDE, then install the HID-project board manager in the Arduino IDE (both by Nico Hood). 

Then do the wireing instructed on HoodLoader2, then upload the avr/examples/install\_sketch.ino  (link: https://github.com/NicoHood/HoodLoader2/tree/master/avr/examples/Installation\_Sketch)

## Uploading to the BOOTLOADER (16u2 \ USB)
Select kort: hoodloader 16u2 and the coorrect port 16u2 
Select Board  should be Hoodloader 2 Uno 

## Uploading to the IO (regular ARDUINO / IO)
select kort: hoodlader Uno and the correct port, might be called 16u2
Select board: should be Hoodloader 2 Uno

## Serial vs Serial1 AKA BRIDGE between IO and USB
Serial is the IO chip and Serial1 is then the USB chip. SO we can send info from IO (serial) to the usb (serial1)

 
