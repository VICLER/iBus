![PROJECT_PHOTO](https://github.com/VICLER/iBus/blob/master/ibus_img.png)

<h3  align="center">iBus Decoder</h3>
<p  align="center">Arduino library for decoding Flysky iBus receiver signal</p>

<!-- FEAUTURES -->
## Features

- Small size and easy to use

- Decoding up to 14 Channels in 7ms

- Fast PPM to PWM (0-255) and Servo (544-2400us) conversion

  

## How to use

```C++
#include <iBus.h>   // include library
```
```C++
iBus(HardwareSerial, MAX_CHANNELS);   // Constructor. iBus signal should be connected to RX pin of Hardware Serial
```
```C++
void begin(); // initialization
```
```C++
void process(); // decoding process. Should be called as often as possible to update receiver data
```
```C++
bool available();   // returns false if not connected
```
```C++
uint16_t get(CHANNEL_NUMBER);   // get channel value in us
```
```C++
bool get(0);    // returns false if there is some corrupted data in last received packet
```
```C++
uint8_t getPWM(CHANNEL_NUMBER);    // get pwm (0-255) channel value
```
```C++
uint16_t getServo_us(CHANNEL_NUMBER);   // get Servo value (0-180)deg for using with Servo.writeMicroseconds() in range (544-2400)us
```

## Example

```C++
#include <iBus.h>

#define MAX_CHANNELS 14

iBus receiver(Serial, MAX_CHANNELS);  // Serial on ATMega328 boards(Uno, Nano, etc.)
                                     // Serial1 on ATMega32u4 boards(Micro, Leonardo)
void setup() {
  receiver.begin();
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  receiver.process();

  digitalWrite(LED_BUILTIN, receiver.available());  // turn led on if connected

  for(byte i = 1; i <= CHANNELS; i++){  // get channel values starting from 1
    Serial.print(receiver.get(i));
    Serial.print('\t');
  }
  Serial.println(receiver.get(0));  //  indicates received packet quality. If 0 -> there are some corrupted values
  delay(10);
}
```