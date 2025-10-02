#include "FastCRC16.hpp"
#include <iostream>
#include <vector>

uint16_t FastCRC16::crctable[256];

int main()
{
   //x^16 + x^15 + x^2 + 1
   FastCRC16 crc(0x8005);

   std::vector<uint8_t> message = {0x6D, 0x27};

   uint16_t result = crc.CRC(message.data(), message.size());

   std::cout << "CRC = 0x" << std::hex << result << std::endl;
   return 0;
}
