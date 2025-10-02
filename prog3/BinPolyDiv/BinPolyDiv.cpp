#include "BinPolyDiv.hpp"
#include <iostream>

int main (int argc, char** argv)
{
   //uint8_t g[6] = {1, 1, 0, 0, 0, 1};
   //uint8_t g[5] = {1, 1, 0, 1, 1};
   uint8_t g[17] = {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1};
   //uint32_t p = 5;
   uint32_t p = 16;
   BinPolyDiv poly(g, p);
   //uint8_t d[9] = {1, 1, 0, 0, 0, 1, 0, 1, 1};
   uint8_t d[31] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1};
   uint8_t q[50] = {0};
   uint32_t d_degree = 30;
   uint32_t quotient_degree;
   uint32_t remainder_degree;
   uint32_t answer = poly.div(d, d_degree, q, quotient_degree, remainder_degree);
   //uint8_t d_1[9] = {1, 1, 0, 0, 0, 1, 0, 1, 1};
   //uint8_t d_1[9] = {1, 1, 0, 1, 1, 1, 0, 1, 1};
   uint8_t d_1[31] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1};
   uint32_t remainder = poly.remainder(d_1, d_degree,remainder_degree);
   std::cout << "Answer is 0x" << std::hex << answer << std::endl;
   std::cout << "Remainder is 0x" << std::hex << remainder << std::endl;
   std::cout << "\n\nIn polynomial form: \nAnswer:\n";
   poly.printPolynomial(answer);
   std::cout << "\nRemainder:\n";
   poly.printPolynomial(remainder);
}
