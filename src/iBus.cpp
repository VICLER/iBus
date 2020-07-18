#include "iBus.h"

void iBus::begin()
{
    _serial.begin(115200);
}

void iBus::process()
{
    static uint8_t buffer[BUFFERSIZE] = {0};
    static uint8_t buffer_index = 0;
    static uint16_t chksum = 0xFFFF;

    while (_serial.available())
    {
        uint8_t rx = _serial.read();
        if (buffer_index == 0 && rx != FIRST_BYTE)
            continue;
        if (buffer_index == 1 && rx != SECOND_BYTE)
        {
            buffer_index = 0;
            chksum = 0xFFFF;
            continue;
        }
        if (buffer_index == BUFFERSIZE)
        {
            _channels[0] = (chksum == (uint16_t)((buffer[31] << 8) | buffer[30]));
            for (uint8_t i = 0; i < _max_channels; i++)
                _channels[i + 1] = (buffer[i * 2 + 3] << 8) | buffer[i * 2 + 2];
            buffer_index = 0;
            chksum = 0xFFFF;
            _last_available = millis();
            return;
        }
        buffer[buffer_index] = rx;
        chksum -= rx * (buffer_index < 30);
        buffer_index++;
    }
}

uint16_t iBus::get(uint8_t channel)
{
    return _channels[channel];
}

uint8_t iBus::getPWM(uint8_t channel)
{
    return (_channels[channel] - MIN_PULSE) * 0.255f;
}

uint16_t iBus::getServo_us(uint8_t channel)
{
    return ((_channels[channel] - 706.89655) * 1.856); // range 0 -> 180 using WriteMicroseconds
}

bool iBus::available()
{
    return (millis() - _last_available < 20);
}