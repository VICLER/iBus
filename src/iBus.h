/* Arduino library for decoding Flysky iBus receiver signal
 *
 * Copyright (c) 2020 Victor Glekler
 *
 * MIT License
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/**
 * @file iBus.h
 * @brief Base class for iBus Decoder
 * @author Victor Glekler
 * Contact: victor.glekler@gmail.com
 * https://github.com/VICLER
*/

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