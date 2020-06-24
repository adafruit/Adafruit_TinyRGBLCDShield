/*!
 * @file Adafruit_TinyMCP23017.h
 */

#ifndef _Adafruit_TinyMCP23017_H_
#define _Adafruit_TinyMCP23017_H_

#include <stdint.h>

// Don't forget the Wire library
/*!
 * @brief MCP23017 main class
 */
class Adafruit_TinyMCP23017 {
public:
  /*!
   * Initializes the MCP23017 given its HW selected address, see datasheet for
   * Address selection.
   * @param addr Selected address
   */
  void begin(uint8_t addr);
  /*!
   * Initializes the default MCP23017, with 000 for the configurable part of the
   * address
   */
  void begin(void);

  /*!
   * Sets the pin mode to either INPUT or OUTPUT
   * @param p Pin to set
   * @param d Mode to set the pin
   */
  void pinMode(uint8_t p, uint8_t d);
  /*!
   * @brief Writes to a pin on the MCP23017
   * @param p Pin to write to
   * @param d What to write to the pin
   */
  void digitalWrite(uint8_t p, uint8_t d);
  /*!
   * @brief Enables the pull-up resistor on the specified pin
   * @param p Pin to set
   * @param d Value to set the pin
   */
  void pullUp(uint8_t p, uint8_t d);
  /*!
   * @brief Reads the specified pin
   * @param p Pin to read
   * @return Value of the pin
   */
  uint8_t digitalRead(uint8_t p);

  /*!
   * Writes all the pins in one go. This method is very useful if you are
   * implementing a multiplexed matrix and want to get a decent refresh rate.
   */
  void writeGPIOAB(uint16_t);
  /*!
   * Reads all 16 pins (port A and B) into a single 16 bits variable.
   * @return Returns the 16 bit variable representing all 16 pins
   */
  uint16_t readGPIOAB();

private:
  uint8_t i2caddr;
};

#define MCP23017_ADDRESS 0x20 //!< MCP23017 I2C address

// registers
#define MCP23017_IODIRA 0x00   //!< I/O direction register A
#define MCP23017_IPOLA 0x02    //!< Input polarity port register A
#define MCP23017_GPINTENA 0x04 //!< Interrupt-on-change pins A
#define MCP23017_DEFVALA 0x06  //!< Default value register A
#define MCP23017_INTCONA 0x08  //!< Interrupt-on-change control register A
#define MCP23017_IOCONA 0x0A   //!< I/O expander configuration register A
#define MCP23017_GPPUA 0x0C    //!< GPIO pull-up resistor register A
#define MCP23017_INTFA 0x0E    //!< Interrupt flag register A
#define MCP23017_INTCAPA 0x10  //!< Interrupt captured value for port register A
#define MCP23017_GPIOA 0x12    //!< General purpose I/O port register A
#define MCP23017_OLATA 0x14    //!< Output latch register 0 A

#define MCP23017_IODIRB 0x01   //!< I/O direction register B
#define MCP23017_IPOLB 0x03    //!< Input polarity port register B
#define MCP23017_GPINTENB 0x05 //!< Interrupt-on-change pins B
#define MCP23017_DEFVALB 0x07  //!< Default value register B
#define MCP23017_INTCONB 0x09  //!< Interrupt-on-change control register B
#define MCP23017_IOCONB 0x0B   //!< I/O expander configuration register B
#define MCP23017_GPPUB 0x0D    //!< GPIO pull-up resistor register B
#define MCP23017_INTFB 0x0F    //!< Interrupt flag register B
#define MCP23017_INTCAPB 0x11  //!< Interrupt captured value for port register B
#define MCP23017_GPIOB 0x13    //!< General purpose I/O port register B
#define MCP23017_OLATB 0x15    //!< Output latch register 0 B

#endif
