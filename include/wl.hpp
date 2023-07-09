#include <Arduino.h>
#include <RF24.h>
#include <SPI.h>
#include "config.h"

SPIClass SPI_WL(WL_MOSI, WL_MISO, WL_CLK);
RF24 radio(WL_CE, WL_CS);
namespace WLModule
{
    constexpr uint8_t MSG_REG[] = {0x0b, 0x00, 0x10, 0x00, 0x7b, 0x01, 0xc8, 0x00, 0x00, 0x00, 0x00, 0x00};
    constexpr uint8_t MSG_EXIT[] = {0x0b, 0x01, 0x10, 0x00, 0x7b, 0x01, 0xc8, 0x00, 0x00, 0x1e, 0x69, 0x53};
    constexpr uint8_t MSG_FUCK[] = {0x0b, 0x00, 0x10, 0x00, 0x7b, 0x01, 0xc8, 0x01, 0x00, 0x1E, 0x67, 0x68};
    constexpr uint8_t localAddr[] = "sb114";
    constexpr uint8_t remoteAddr[] = "sb514";

    void init()
    {
        radio.begin(&SPI_WL);
        radio.openWritingPipe(localAddr);
        radio.openReadingPipe(1, remoteAddr);
        radio.setPALevel(RF24_PA_MIN);
        radio.startListening();
    }
    inline bool available()
    {
        return radio.available();
    }
    inline bool send(const uint8_t *data, uint8_t len)
    {
        radio.stopListening();
        bool report = radio.write(data, len);
        radio.startListening();
        return report;
    }

    inline void readInto(uint8_t *buf)
    {
        radio.read(buf, 32);
    }

    inline void flushRx()
    {
        radio.flush_rx();
    }

}