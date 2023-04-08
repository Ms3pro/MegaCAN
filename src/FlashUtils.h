#ifndef FLASH_UTILS_H_
#define FLASH_UTILS_H_

#include <EEPROM.h>

// reads a big endian 16bit signed/unsigned word from EEPROM flash
#define EEPROM_GetBigS16(ADDR) (int16_t)(((uint16_t)(EEPROM.read(ADDR)) << 8) | EEPROM.read(ADDR + 1))
#define EEPROM_GetBigU16(ADDR) (uint16_t)(((uint16_t)(EEPROM.read(ADDR)) << 8) | EEPROM.read(ADDR + 1))

// writes a big endian 16bit signed/unsigned word to EEPROM flash
#define EEPROM_SetBigU16(ADDR,VAL) EEPROM.write(ADDR,(VAL)>>8&0xFF);EEPROM.write(ADDR + 1,(VAL)&0xFF)
#define EEPROM_SetBigS16(ADDR,VAL) EEPROM_SetBigU16(ADDR,VAL)

// reads a big endian 32bit signed/unsigned word from EEPROM flash
#define EEPROM_GetBigS32(ADDR) (int32_t)(((uint32_t)(EEPROM.read(ADDR)) << 24) | ((uint32_t)(EEPROM.read(ADDR + 1)) << 16) | ((uint32_t)(EEPROM.read(ADDR + 2)) << 8) | EEPROM.read(ADDR + 3))
#define EEPROM_GetBigU32(ADDR) (uint32_t)(((uint32_t)(EEPROM.read(ADDR)) << 24) | ((uint32_t)(EEPROM.read(ADDR + 1)) << 16) | ((uint32_t)(EEPROM.read(ADDR + 2)) << 8) | EEPROM.read(ADDR + 3))

// writes a big endian 32bit signed/unsigned word to EEPROM flash
#define EEPROM_SetBigU32(ADDR,VAL) EEPROM.write(ADDR,(VAL)>>24&0xFF);EEPROM.write(ADDR + 1,(VAL>>16)&0xFF);EEPROM.write(ADDR + 2,(VAL>>8)&0xFF);EEPROM.write(ADDR + 3,(VAL)&0xFF)
#define EEPROM_SetBigS32(ADDR,VAL) EEPROM_SetBigU32(ADDR,VAL)

namespace FlashUtils
{

int16_t
lerpS16(
  const size_t &xBinsFlashOffset,
  const size_t &yBinsFlashOffset,
  const size_t &nBins,
  const int16_t &value);

/**
 * Reads a big endian variable from EEPROM
 * 
 * @param[in] offset
 * The flash byte offset to read from
 */
template <typename VAR_T>
VAR_T
flashRead_BE(
  const size_t &offset);

/**
 * Reads a big endian variable from EEPROM
 * 
 * @param[in] offset
 * The flash byte offset to read from
 */
template <typename VAR_T>
void
flashWrite_BE(
  const size_t &offset,
  const VAR_T &value);

}

#endif
