/*

LED wiring:
  * TM1637 pin CLK -> Arduino pin D4
  * TM1637 pin DIO -> Arduino pin D5
  * TM1637 pin Vcc -> Arduino pin 5V
  * TM1637 pin GND -> Arduino pin GND
  * Encoder pin 1  -> Arduino pin D2
  * Encoder pin 2  -> Arduino pin GND
  * Encoder pin 3  -> Arduino pin D3

If you find the counter goes backwards, swap the numbers assigned
to ENC_PIN1 and ENC_PIN3 below.
*/

#include <SevenSegmentTM1637.h>

const byte PIN_CLK = 4;
const byte PIN_DIO = 5;
SevenSegmentTM1637 display(PIN_CLK, PIN_DIO);

// Rotary Encoder
#include <RotaryEncoder.h>
const byte ENC_PIN1 = 3;
const byte ENC_PIN3 = 2;
RotaryEncoder encoder(ENC_PIN1,ENC_PIN3);

void setup() {
  display.begin();
  display.setBacklight(100);  // Set 100% brightness
};

// There is no error checking in this function, if the hex pointer
// passed doesn't point to an area with room for 4 characters, you'll
// get a buffer overrun.
const char hex_digit[] = { '0', '1', '2', '3', '4', '5', '6', '7',
                     '8', '9', 'A', 'b', 'C', 'D', 'E', 'F'};
void dec2hex(char *hex, long dec)
{
  for(int digit=3; digit>=0; digit--, dec>>=4)
    hex[digit]=hex_digit[dec & 0x0f];
}

// There is no error checking in this function, if the str pointer
// passed doesn't point to an area with room for 4 characters, you'll
// get a buffer overrun.
void dec2str(char *str, long dec)
{
  while (dec>9999)
    dec-=9999;
  while (dec<0)
    dec+=9999;
  sprintf(str,"%04d",dec);
}

long lastCount=-1;

char str[5]={'0','0','0','0','\0'};

void loop() {
  encoder.tick();
  long counter=encoder.getPosition();
  counter>>=2;  // divide by 4
  if (lastCount!=counter)
  {
    // Choose one of the lines below, depending on whether you want
    // a decimal or hex counter
    dec2str(str,counter);
    //dec2hex(str,counter);
    display.print(str);
    lastCount=counter;
  }
};
