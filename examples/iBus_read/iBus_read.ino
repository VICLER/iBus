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

  for(byte i = 1; i <= MAX_CHANNELS; i++){  // get channel values starting from 1
    Serial.print(receiver.get(i));
    Serial.print('\t');
  }
  Serial.println(receiver.get(0));  // received packet quality. If 0 -> there are some corrupted values
  delay(10);
  
}
