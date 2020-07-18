#include <iBus.h>

#define MAX_CHANNELS 14
iBus receiver(Serial, MAX_CHANNELS);

void setupTimer(){
  cli();
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2  = 0;
  TCCR2B |= (1 << CS22);       // 64 prescaler
  OCR2A = 125;                // 500us period
  TCCR2A |= (1 << WGM21);    // turn on CTC mode
  TIMSK2 |= (1 << OCIE2A);  // enable timer compare interrupt
  sei();
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  receiver.begin();
  setupTimer();
}

void loop() {

  digitalWrite(LED_BUILTIN, receiver.available());  // turn led on if connected

  for(byte i = 1; i <= MAX_CHANNELS; i++){  // get channel values starting from 1
    Serial.print(receiver.get(i));
    Serial.print('\t');
  }
  Serial.println(receiver.get(0));  //  indicates received packet quality. If 0 -> there are some corrupted values
  delay(10);

}

ISR(TIMER2_COMPA_vect)
{
  receiver.process();
}
