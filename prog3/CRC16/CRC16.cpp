#include "CRC16.hpp"
#include <iostream>

int main (int argc, char** argv)
{
   //
   uint32_t g = 0x18005;
   CRC16 crc(g);
   uint8_t g_0[17] = {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1};
   uint32_t p = 16;
   BinPolyDiv poly(g_0, p);
   uint32_t m_degree = 14;
   uint8_t m[m_degree+1] = {1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1};
   uint32_t result = crc.CRC(m, (int)(m_degree+1));

   std::cout << "CRC out is 0x" << std::hex << result << std::endl;
   std::cout << "\n\nIn polynomial form:\n";
   poly.printPolynomial(result);
}
