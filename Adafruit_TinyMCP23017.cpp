/***************************************************
  This is a library for the MCP23017 i2c port expander

  These displays use I2C to communicate, 2 pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <TinyWireM.h>
#include <avr/pgmspace.h>
#include "Adafruit_TinyMCP23017.h"

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

 // minihelper
static inline void wiresend(uint8_t x) {
#if ARDUINO >= 100
  TinyWireM.write((uint8_t)x);
#else
  TinyWireM.send(x);
#endif
}

static inline uint8_t wirerecv(void) {
#if ARDUINO >= 100
  return TinyWireM.read();
#else
  return TinyWireM.receive();
#endif
}

////////////////////////////////////////////////////////////////////////////////

void Adafruit_TinyMCP23017::begin(uint8_t addr) {

  i2caddr = MCP23017_ADDRESS | addr;

  TinyWireM.begin();

  // set defaults! IODIRB is 1 greater than IODIRA
  for (uint8_t port = 0; port < 2; port++)
  {
    TinyWireM.beginTransmission(i2caddr);
    wiresend(MCP23017_IODIRA + port);
    wiresend(0xFF);
    TinyWireM.endTransmission();
  }
}


void Adafruit_TinyMCP23017::begin(void) {
  begin(0);
}

void Adafruit_TinyMCP23017::pinMode(uint8_t p, uint8_t d) {
  uint8_t iodir;
  uint8_t iodiraddr;

  if (p < 8)
    iodiraddr = MCP23017_IODIRA;
  else {
    iodiraddr = MCP23017_IODIRB;
    p -= 8;
  }

  // read the current IODIR
  TinyWireM.beginTransmission(i2caddr);
  wiresend(iodiraddr);
  TinyWireM.endTransmission();

  TinyWireM.requestFrom(i2caddr, 1);
  iodir = wirerecv();

  // set the pin and direction
  if (d == INPUT) {
    iodir |= 1 << p;
  }
  else {
    iodir &= ~(1 << p);
  }

  // write the new IODIR
  TinyWireM.beginTransmission(i2caddr);
  wiresend(iodiraddr);
  wiresend(iodir);
  TinyWireM.endTransmission();
}

uint16_t Adafruit_TinyMCP23017::readGPIOAB() {
  uint16_t ba = 0;
  uint8_t a;

  // read the current GPIO output latches
  TinyWireM.beginTransmission(i2caddr);
  wiresend(MCP23017_GPIOA);
  TinyWireM.endTransmission();

  TinyWireM.requestFrom(i2caddr, 2);
  a = wirerecv();
  ba = wirerecv();
  ba <<= 8;
  ba |= a;

  return ba;
}

void Adafruit_TinyMCP23017::writeGPIOAB(uint16_t ba) {
  TinyWireM.beginTransmission(i2caddr);
  wiresend(MCP23017_GPIOA);
  wiresend(ba & 0xFF);
  wiresend(ba >> 8);
  TinyWireM.endTransmission();
}

void Adafruit_TinyMCP23017::digitalWrite(uint8_t pin, uint8_t direction) {
  uint8_t gpio;
  uint8_t gpioaddr, olataddr;

  olataddr = MCP23017_OLATA;
  if (pin >= 8) {
    olataddr = MCP23017_OLATB;
    pin -= 8;
  }
  gpioaddr = olataddr - 2;

  // read the current GPIO output latches
  TinyWireM.beginTransmission(i2caddr);
  wiresend(olataddr);
  TinyWireM.endTransmission();

  TinyWireM.requestFrom(i2caddr, 1);
  gpio = wirerecv();

  // set the pin and direction
  if (direction == HIGH) {
    gpio |= 1 << pin;
  }
  else {
    gpio &= ~(1 << pin);
  }

  // write the new GPIO
  TinyWireM.beginTransmission(i2caddr);
  wiresend(gpioaddr);
  wiresend(gpio);
  TinyWireM.endTransmission();
}

void Adafruit_TinyMCP23017::pullUp(uint8_t p, uint8_t direction) {
  uint8_t gppu;
  uint8_t gppuaddr;

  if (p < 8) {
    gppuaddr = MCP23017_GPPUA;
  }
  else {
    gppuaddr = MCP23017_GPPUB;
    p -= 8;
  }


  // read the current pullup resistor set
  TinyWireM.beginTransmission(i2caddr);
  wiresend(gppuaddr);
  TinyWireM.endTransmission();

  TinyWireM.requestFrom(i2caddr, 1);
  gppu = wirerecv();

  // set the pin and direction
  if (direction == HIGH) {
    gppu |= 1 << p;
  }
  else {
    gppu &= ~(1 << p);
  }

  // write the new GPIO
  TinyWireM.beginTransmission(i2caddr);
  wiresend(gppuaddr);
  wiresend(gppu);
  TinyWireM.endTransmission();
}

uint8_t Adafruit_TinyMCP23017::digitalRead(uint8_t p) {
  uint8_t gpioaddr;

  if (p < 8)
  {
    gpioaddr = MCP23017_GPIOA;
  }
  else {
    gpioaddr = MCP23017_GPIOB;
    p -= 8;
  }

  // read the current GPIO
  TinyWireM.beginTransmission(i2caddr);
  wiresend(gpioaddr);
  TinyWireM.endTransmission();

  TinyWireM.requestFrom(i2caddr, 1);
  return (wirerecv() >> p) & 0x1;
}
