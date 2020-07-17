#include <iBus.h>

#define CHANNELS 14
iBus receiver(Serial, CHANNELS);

void setup() {
  receiver.begin();
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  receiver.process();
  
  for(byte i = 1; i <= CHANNELS; i++){  // get channel values starting from 1
    Serial.print(receiver.get(i));
    Serial.print('\t');
  }
  Serial.println(receiver.get(0));  //  indicates received packet quality. If 0 -> there are some corrupted values
  delay(10);

  digitalWrite(LED_BUILTIN, receiver.available());
}
