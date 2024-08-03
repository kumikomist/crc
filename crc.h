#ifndef CRCH
#define CRCH

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------
// include
//------------------------------------------------------------------------------
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

//------------------------------------------------------------------------------
// define
//------------------------------------------------------------------------------
//! シフト方向
typedef enum
{
  ShiftLeft,  //!< 左シフト
  ShiftRight  //!< 右シフト
} SHIFT_DIRECTION;

//! CRC-8の演算パラメーター
typedef struct
{
  bool     reflect_input;   //!< 入力反転 [true=Yes / false=No]
  bool     reflect_output;  //!< 出力反転 [true=Yes / false=No]
  uint8_t  polynomial;      //!< 多項式
  uint8_t  initial_value;   //!< 初期値
  uint8_t  final_xor;       //!< 出力XOR
  uint8_t *ptable;          //!< テーブルのポインター

  SHIFT_DIRECTION shift_dir;  //!< シフト方向
} CRC8_PARAMETER;

//! CRC-16の演算パラメーター
typedef struct
{
  bool      reflect_input;   //!< 入力反転 [true=Yes / false=No]
  bool      reflect_output;  //!< 出力反転 [true=Yes / false=No]
  uint16_t  polynomial;      //!< 多項式
  uint16_t  initial_value;   //!< 初期値
  uint16_t  final_xor;       //!< 出力XOR
  uint16_t *ptable;          //!< テーブルのポインター

  SHIFT_DIRECTION shift_dir;  //!< シフト方向
} CRC16_PARAMETER;

//! CRC-32の演算パラメーター
typedef struct
{
  bool      reflect_input;   //!< 入力反転 [true=Yes / false=No]
  bool      reflect_output;  //!< 出力反転 [true=Yes / false=No]
  uint32_t  polynomial;      //!< 多項式
  uint32_t  initial_value;   //!< 初期値
  uint32_t  final_xor;       //!< 出力XOR
  uint32_t *ptable;          //!< テーブルのポインター

  SHIFT_DIRECTION shift_dir;  //!< シフト方向
} CRC32_PARAMETER;

//------------------------------------------------------------------------------
// function
//------------------------------------------------------------------------------
void Make_CRC8Table(const CRC8_PARAMETER *param);
void Make_CRC16Table(const CRC16_PARAMETER *param);
void Make_CRC32Table(const CRC32_PARAMETER *param);

uint8_t  Calc_CRC8(const uint8_t buf[], size_t len, const CRC8_PARAMETER *param);
uint16_t Calc_CRC16(const uint8_t buf[], size_t len, const CRC16_PARAMETER *param);
uint32_t Calc_CRC32(const uint8_t buf[], size_t len, const CRC32_PARAMETER *param);

#ifdef __cplusplus
}
#endif

#endif
