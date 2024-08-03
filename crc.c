/**
 * @file crc.c
 * @brief CRC
 */

//------------------------------------------------------------------------------
// include
//------------------------------------------------------------------------------
#include "crc.h"
#include "bitwise.h"

/** ----------------------------------------------------------------------------
 * @brief CRC-8テーブルの作成
 *
 * @param [in] param : 演算設定
 */
void Make_CRC8Table(const CRC8_PARAMETER *param)
{
  uint8_t  c, j;
  uint16_t i;

  if (param->shift_dir == ShiftLeft) {
    for (i = 0; i < 256; i++) {
      c = (uint8_t)i;
      for (j = 0; j < 8; j++) {
        if ((uint8_t)(c & 0x80) == 0U) {
          c <<= 1;
        } else {
          c = (uint8_t)(c << 1) ^ param->polynomial;
        }
      }
      param->ptable[i] = c;
    }
  } else {
    for (i = 0; i < 256; i++) {
      c = (uint8_t)i;
      for (j = 0; j < 8; j++) {
        if ((uint8_t)(c & 0x01) == 0U) {
          c >>= 1;
        } else {
          c = param->polynomial ^ (uint8_t)(c >> 1);
        }
      }
      param->ptable[i] = c;
    }
  }
}

/** ----------------------------------------------------------------------------
 * @brief CRC-16テーブルの作成
 *
 * @param [in] param : 演算設定
 */
void Make_CRC16Table(const CRC16_PARAMETER *param)
{
  uint8_t  j;
  uint16_t c;
  uint16_t i;

  if (param->shift_dir == ShiftLeft) {
    for (i = 0; i < 256; i++) {
      c = (uint16_t)(i << 8);
      for (j = 0; j < 8; j++) {
        if ((uint16_t)(c & 0x8000) == 0U) {
          c <<= 1;
        } else {
          c = (uint16_t)(c << 1) ^ param->polynomial;
        }
      }
      param->ptable[i] = c;
    }
  } else {
    for (i = 0; i < 256; i++) {
      c = i;
      for (j = 0; j < 8; j++) {
        if ((uint16_t)(c & 0x0001) == 0U) {
          c >>= 1;
        } else {
          c = param->polynomial ^ (uint16_t)(c >> 1);
        }
      }
      param->ptable[i] = c;
    }
  }
}

/** ----------------------------------------------------------------------------
 * @brief CRC-32テーブルの作成
 *
 * @param [in] param : 演算設定
 */
void Make_CRC32Table(const CRC32_PARAMETER *param)
{
  uint8_t  j;
  uint32_t c;
  uint32_t i;

  if (param->shift_dir == ShiftLeft) {
    for (i = 0; i < 256; i++) {
      c = (uint32_t)(i << 24);
      for (j = 0; j < 8; j++) {
        if ((uint32_t)(c & 0x80000000) == 0UL) {
          c <<= 1;
        } else {
          c = (uint32_t)(c << 1) ^ param->polynomial;
        }
      }
      param->ptable[i] = c;
    }
  } else {
    for (i = 0; i < 256; i++) {
      c = i;
      for (j = 0; j < 8; j++) {
        if ((uint32_t)(c & 0x00000001) == 0UL) {
          c >>= 1;
        } else {
          c = param->polynomial ^ (uint32_t)(c >> 1);
        }
      }
      param->ptable[i] = c;
    }
  }
}

/** ----------------------------------------------------------------------------
 * @brief CRC-8の計算
 *
 * @param [in] buf : データ
 * @param len : データ長
 * @param [in] param : 演算設定
 * @return CRC-8
 */
uint8_t Calc_CRC8(const uint8_t buf[], size_t len, const CRC8_PARAMETER *param)
{
  uint8_t c = param->initial_value;
  uint8_t tmp;
  size_t  i;

  if (param->shift_dir == ShiftLeft) {
    for (i = 0; i < len; i++) {
      tmp = buf[i];
      if (param->reflect_input == true) {
        tmp = Reverse_Bit8(tmp);
      }
      c = param->ptable[c ^ tmp];
    }
  } else {
    for (i = 0; i < len; i++) {
      tmp = buf[i];
      if (param->reflect_input == true) {
        tmp = Reverse_Bit8(tmp);
      }
      c = param->ptable[c ^ tmp] ^ c;
    }
  }

  c ^= param->final_xor;

  if (param->reflect_output == true) {
    c = Reverse_Bit8(c);
  }

  return c;
}

/** ----------------------------------------------------------------------------
 * @brief CRC-16の計算
 *
 * @param [in] buf : データ
 * @param len : データ長
 * @param [in] param : 演算設定
 * @return CRC-16
 */
uint16_t Calc_CRC16(const uint8_t buf[], size_t len, const CRC16_PARAMETER *param)
{
  uint8_t  adr, tmp;
  uint16_t c = param->initial_value;
  size_t   i;

  if (param->shift_dir == ShiftLeft) {
    for (i = 0; i < len; i++) {
      tmp = buf[i];
      if (param->reflect_input == true) {
        tmp = Reverse_Bit8(tmp);
      }
      adr = (uint8_t)((uint8_t)(c >> 8) ^ tmp) & 0xff;
      c   = (uint16_t)(c << 8) ^ param->ptable[adr];
    }
  } else {
    for (i = 0; i < len; i++) {
      tmp = buf[i];
      if (param->reflect_input == true) {
        tmp = Reverse_Bit8(tmp);
      }
      adr = (uint8_t)(c ^ tmp) & 0xFF;
      c   = param->ptable[adr] ^ (uint16_t)(c >> 8);
    }
  }

  c ^= param->final_xor;

  if (param->reflect_output == true) {
    c = Reverse_Bit16(c);
  }

  return c;
}

/** ----------------------------------------------------------------------------
 * @brief CRC-32の計算
 *
 * @param [in] buf : データ
 * @param len : データ長
 * @param [in] param : 演算設定
 * @return CRC-32
 */
uint32_t Calc_CRC32(const uint8_t buf[], size_t len, const CRC32_PARAMETER *param)
{
  uint8_t  adr, tmp;
  uint32_t c = param->initial_value;
  size_t   i;

  if (param->shift_dir == ShiftLeft) {
    for (i = 0; i < len; i++) {
      tmp = buf[i];
      if (param->reflect_input == true) {
        tmp = Reverse_Bit8(tmp);
      }
      adr = (uint8_t)((uint8_t)(c >> 24) ^ tmp) & 0xff;
      c   = (uint32_t)(c << 8) ^ param->ptable[adr];
    }
  } else {
    for (i = 0; i < len; i++) {
      tmp = buf[i];
      if (param->reflect_input == true) {
        tmp = Reverse_Bit8(tmp);
      }
      adr = (uint8_t)(c ^ tmp) & 0xFF;
      c   = param->ptable[adr] ^ (uint32_t)(c >> 8);
    }
  }

  c ^= param->final_xor;

  if (param->reflect_output == true) {
    c = Reverse_Bit32(c);
  }

  return c;
}
