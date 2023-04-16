#include "RF24.h"
#include "wl.h"
#include "config.h"
#include <Arduino.h>
#include <SPI.h>

RF24 *radio;

void WLModule::init()
{
    SPIClass SPI_WL(WL_MOSI, WL_MISO, WL_CLK, WL_CS);
    radio = new RF24(WL_CE, WL_CS);
    radio->begin(&SPI_WL);
}