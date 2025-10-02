#ifndef FASTCRC16_HPP
#define FASTCRC16_HPP

#include <cstdint>
#include <cstdlib>
#include <iostream>

class FastCRC16 {
protected:
   static uint16_t crctable[256];   // lookup table (size 256)
   uint8_t crc0, crc1;          // two parity bytes (MSB and LSB)
   uint16_t polynomial;        // generator polynomial (e.g. 0x8005)

   void build_table()
   {
      // Build the 256-entry table for all possible byte values
      for (int t = 0; t < 256; t++)
      {
         uint16_t reg = t << 8; // align byte to MSB
         for (int i = 0; i < 8; i++)
         {
            if (reg & 0x8000) {        // MSB is 1
               reg = (reg << 1) ^ polynomial;
            }
            else
            {
               reg = reg << 1;
            }
        }
        crctable[t] = reg & 0xFFFF;
      }
   }

public:
   FastCRC16(uint16_t crcpoly)
   {
      polynomial = crcpoly;
      build_table();
      crc0 = 0x00;
      crc1 = 0x00;
   }

   uint16_t CRC(const uint8_t* data, int len)
   {
      crc0 = 0x00;
      crc1 = 0x00;
      uint16_t crc = 0x0000;

      for (int i = 0; i < len; i++)
      {
         uint8_t byte = data[i];
         uint8_t tbl_index = static_cast<uint8_t>((crc >> 8) ^ byte);
         crc = (crc << 8) ^ (uint16_t)crctable[tbl_index];
      }

      crc0 = static_cast<uint8_t>((crc >> 8) & 0xFF);
      crc1 = static_cast<uint8_t>(crc & 0xFF);

      return crc;
   }
};

#endif

