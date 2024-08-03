#include "CppUTest/TestHarness.h"

#include "crc.h"

// clang-format off
TEST_GROUP(crc){
  TEST_SETUP(){
  }

  TEST_TEARDOWN(){
  }
};
// clang-format on

TEST(crc, Test_CRC8_Maxim)
{
  uint8_t data[] = "123456789";
  uint8_t crc8;
  uint8_t table[256];

  CRC8_PARAMETER crc_param;
  crc_param.reflect_input  = true;
  crc_param.reflect_output = true;
  crc_param.polynomial     = 0x31;
  crc_param.initial_value  = 0x00;
  crc_param.final_xor      = 0x00;
  crc_param.ptable         = table;
  crc_param.shift_dir      = ShiftLeft;

  Make_CRC8Table(&crc_param);
  crc8 = Calc_CRC8(data, 9, &crc_param);
  UNSIGNED_LONGS_EQUAL(crc8, 0xA1);
}
TEST(crc, Test_CRC16_Modbus)
{
  uint8_t  data[] = "123456789";
  uint16_t crc16;
  uint16_t table[256];

  CRC16_PARAMETER crc_param;
  crc_param.reflect_input  = true;
  crc_param.reflect_output = true;
  crc_param.polynomial     = 0x8005;
  crc_param.initial_value  = 0xffff;
  crc_param.final_xor      = 0x0000;
  crc_param.ptable         = table;
  crc_param.shift_dir      = ShiftLeft;

  Make_CRC16Table(&crc_param);
  crc16 = Calc_CRC16(data, 9, &crc_param);
  UNSIGNED_LONGS_EQUAL(crc16, 0x4B37);
}
TEST(crc, Test_CRC32)
{
  uint8_t  data[] = "123456789";
  uint32_t crc32;
  uint32_t table[256];

  CRC32_PARAMETER crc_param;
  crc_param.reflect_input  = true;
  crc_param.reflect_output = true;
  crc_param.polynomial     = 0x04C11DB7;
  crc_param.initial_value  = 0xffffffff;
  crc_param.final_xor      = 0xffffffff;
  crc_param.ptable         = table;
  crc_param.shift_dir      = ShiftLeft;

  Make_CRC32Table(&crc_param);
  crc32 = Calc_CRC32(data, 9, &crc_param);
  UNSIGNED_LONGS_EQUAL(crc32, 0xCBF43926);
}