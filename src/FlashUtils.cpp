#include <Arduino.h>
#include "FlashUtils.h"

namespace FlashUtils
{
  
  int16_t
  lerpS16(
    const size_t &xBinsFlashOffset,
    const size_t &yBinsFlashOffset,
    const size_t &nBins,
    const int16_t &value)
  {
    if (nBins <= 1)
    {
      return value;
    }

    int16_t loX_Val, hiX_Val;
    loX_Val = EEPROM_GetBigS16(xBinsFlashOffset);

    // handle case where value is below the x-axis (-) limit
    if (value <= loX_Val)
    {
      return EEPROM_GetBigS16(yBinsFlashOffset);
    }

    size_t offset = sizeof(int16_t);
    for (size_t i=0; i<(nBins-1); i++)
    {
      hiX_Val = EEPROM_GetBigS16(xBinsFlashOffset+offset);

      if (loX_Val <= value && value <= hiX_Val)
      {// found bins to interpolate between
        int16_t loY_Val = EEPROM_GetBigS16(yBinsFlashOffset+offset-sizeof(int16_t));
        int16_t hiY_Val = EEPROM_GetBigS16(yBinsFlashOffset+offset);
        return map(value,loX_Val,hiX_Val,loY_Val,hiY_Val);
      }

      // increment to look at next two x-axis bins
      loX_Val = hiX_Val;
      offset += sizeof(int16_t);
    }

    /**
     * never found any values to interpolate between, so value must be higher than
     * the x-axis (+) limit value. return y-axis (+) limit value as result.
     */
    return EEPROM_GetBigS16(yBinsFlashOffset+(nBins-1)*sizeof(int16_t));
  }
  
  template <>
  uint8_t
  flashRead_BE(
    const size_t &offset)
  {
    return EEPROM.read(offset);
  }

  template <>
  int8_t
  flashRead_BE(
    const size_t &offset)
  {
    return EEPROM.read(offset);
  }
  
  template <>
  uint16_t
  flashRead_BE(
    const size_t &offset)
  {
    return EEPROM_GetBigU16(offset);
  }

  template <>
  int16_t
  flashRead_BE(
    const size_t &offset)
  {
    return EEPROM_GetBigS16(offset);
  }

  template <>
  uint32_t
  flashRead_BE(
    const size_t &offset)
  {
    return EEPROM_GetBigU32(offset);
  }

  template <>
  int32_t
  flashRead_BE(
    const size_t &offset)
  {
    return EEPROM_GetBigS32(offset);
  }

  template <>
  float
  flashRead_BE(
    const size_t &offset)
  {
    uint32_t u32 = EEPROM_GetBigU32(offset);
    return *(float*)((void*)(&u32));
  }

  template <>
  double
  flashRead_BE(
    const size_t &offset)
  {
    // AVR libc doesn't support 64bit doubles (they're really just 32bits floats)
    static_assert(sizeof(double) == 4);
    uint32_t u32 = EEPROM_GetBigU32(offset);
    return *(double*)((void*)(&u32));
  }

  template <>
  void
  flashWrite_BE(
    const size_t &offset,
    const uint8_t &value)
  {
    EEPROM.write(offset,value);
    EEPROM.commit();
  }

  template <>
  void
  flashWrite_BE(
    const size_t &offset,
    const int8_t &value)
  {
    EEPROM.write(offset,value);
    EEPROM.commit();
  }
  
  template <>
  void
  flashWrite_BE(
    const size_t &offset,
    const uint16_t &value)
  {
    EEPROM_SetBigU16(offset,value);
  }
  
  template <>
  void
  flashWrite_BE(
    const size_t &offset,
    const int16_t &value)
  {
    EEPROM_SetBigS16(offset,value);
  }

  template <>
  void
  flashWrite_BE(
    const size_t &offset,
    const uint32_t &value)
  {
    EEPROM_SetBigU32(offset,value);
  }

  template <>
  void
  flashWrite_BE(
    const size_t &offset,
    const int32_t &value)
  {
    EEPROM_SetBigS32(offset,value);
  }

  template <>
  void
  flashWrite_BE(
    const size_t &offset,
    const float &value)
  {
    EEPROM_SetBigU32(offset,*(uint32_t*)((void*)(&value)));
  }

  template <>
  void
  flashWrite_BE(
    const size_t &offset,
    const double &value)
  {
    // AVR libc doesn't support 64bit doubles (they're really just 32bits floats)
    static_assert(sizeof(double) == 4);
    EEPROM_SetBigU32(offset,*(uint32_t*)((void*)(&value)));
  }

}
