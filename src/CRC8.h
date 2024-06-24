#ifndef CRC8_H_
#define CRC8_H_

#include <stdint.h>

void CalculateTable_CRC8(uint8_t* crctable, const uint8_t polynomial = 0x9B) {
  for (int dividend = 0; dividend < 256; dividend++) {
    uint8_t currByte = (uint8_t)dividend;
    for (uint8_t bit = 0; bit < 8; bit++) {
      if ((currByte & 0x80) != 0) {
          currByte <<= 1;
          currByte ^= polynomial;
      } else {
          currByte <<= 1;
      }
    }
    crctable[dividend] = currByte;
  }
}

uint8_t Compute_CRC8(uint8_t* bytes, int length, uint8_t* crctable,
                     const uint8_t initial_XOR = 0xFF,
                     const uint8_t final_XOR = 0x00) {
  uint8_t crc = initial_XOR;
  for (int i = 0; i < length; i++) {
    uint8_t data = (uint8_t)(bytes[i] ^ crc);
    crc = (uint8_t)(crctable[data]);
  }
  crc = crc ^ final_XOR;
  return crc;
}

#endif  // CRC8_H_