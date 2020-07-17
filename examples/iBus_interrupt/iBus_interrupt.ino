#include <iBus.h>

#define CHANNELS 14
iBus receiver(Serial, CHANNELS);

void setupTimer(){
  cli();
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2  = 0;
  OCR2A = 125;                              // 500us period
  TCCR2A |= (1 << WGM21);                  // turn on CTC mode
  //TCCR2B |= (1 << CS20) | (1 << CS21);  // 32 prescaler for 8Mhz Clock
  TCCR2B |= (1 << CS22);                 // 64 prescaler for 16Mhz Clock
  TIMSK2 |= (1 << OCIE2A);              // enable timer compare interrupt
  sei();
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  receiver.begin();
  setupTimer();
}

void loop() {
  for(byte i = 1; i <= CHANNELS; i++){  // get channel values starting from 1
    Serial.print(receiver.get(i));
    Serial.print('\t');
  }
  Serial.println(receiver.get(0));  //  indicates received packet quality. If 0 -> there are some corrupted values
  delay(10);

  digitalWrite(LED_BUILTIN, receiver.available());
}

ISR(TIMER2_COMPA_vect)
{
  receiver.process();
}
