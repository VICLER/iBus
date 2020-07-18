#pragma once

#include "Arduino.h"

#define BUFFERSIZE      32
#define FIRST_BYTE      0x20
#define SECOND_BYTE     0x40
#define MAX_CHANNELS    14
#define MIN_PULSE       1000 // min valid impulse us
#define MAX_PULSE       2000 // max valid impulse us

class iBus
{
public:
    iBus(HardwareSerial &serial, uint8_t channels = MAX_CHANNELS) : _serial(serial), _max_channels(channels) {}
    void begin();
    void process();
    bool available();
    uint16_t get(uint8_t channel);
    uint8_t getPWM(uint8_t channel);
    uint16_t getServo_us(uint8_t channel);

private:
    HardwareSerial &_serial;
    const uint8_t _max_channels;
    uint32_t _last_available = 0;
    uint16_t _channels[MAX_CHANNELS + 1];
};