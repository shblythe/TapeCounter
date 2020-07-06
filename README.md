# TapeCounter
An Arduino-based replacement tape counter using a rotary encoder and LED display

## The basics
The circuit is very simple, all you need to do is connect the rotary encoder's 3 pins, and the LED display's four pins, to the Arduino.
I used an Arduino Nano, but any will do.

## The LED display
The LED display is based on the TM1637 chip, which does all the heavy lifting, and makes it easy to connect.
On my LED display, the pins are labelled CLK, DIO, VCC, GND.
Wire the VCC pin to 5V on the Arduino, and the GND pin to GND.
I wired the CLK pin to pin D4, and the DIO pin to pin 5, but you can wire them elsewhere.  If you do, you need to change the definitions of the PIN_CLK and PIN_DIO constants in TapeCounter.ino.

## The Rotary Encoder
I bought a rotary encoder with indexing, unfortunately, which means it clicks as it turns.  You want one that turns smoothly (without indexing), that way you avoid the micro-surgery I had to do on mine.

Somehow, you are going to need to get the belt which comes from your tape recorder, which used to turn your old tape counter, to turn the new one.  I got lucky.  I bought an encoder with a splined shaft with a slot in the top, and the spindle from my old counter fitted into the slot nice and tight.  The mechanics will differ for each tape recoder and each encoder, though, so I'm afraid that's your problem.

Usually a rotary encoder will have three pins to connect it.  If yours has five, two are probably for a switch which actuates when you push the shaft.  Useless for this application really.  Anyway, the three main pins are what we need.  Usually the middle one is for GND, and the other two are the encoder pins.  So, connect the middle one to GND, and connect the other two to ports D2 and D3.  If you run the code and the timer goes backwards when you play and forwards when you rewind, either swap those two wires or swap the values of the ENC_PIN1 and ENC_PIN3 constants in the code.

You can use pins other than 2 and 3, but see below.

The codes use this excellent library: https://github.com/mathertel/RotaryEncoder

I tried a few, and this is the most accurate I found.

I use it in a simple poll mode, rather than using interrupts, and it works very well.  It might be better with interrupts in some cases, in which case you can see mathertel's documentation here on how to do that: http://www.mathertel.de/Arduino/RotaryEncoderLibrary.aspx

If you do use interrupts, though, it's best to stick with pins 2 and 3

## Reset
I could have implemented a reset button, but I just press the reset button on the Arduino when I need to, it restarts the program and resets the counter to 0, so no need.
If you wanted to hide the Arduino away (but why?) then you could extend connect and external switch between RST and GND, or you could implement a software counter reset easily enough.

## Hex or decimal?
Since I know the size of the display, and exactly what I'm displaying, I wrote a custom conversion from the counter number to the string for display, it's called dec2str.
However, while I was messing with that, it occurred to me that converting to hex would be really efficient, and of course cool, so I did that as well.

The default here is decimal, but if you prefer hex, you can comment out the line in loop() which calls dec2str, and uncomment the one which calls dec2hex.
