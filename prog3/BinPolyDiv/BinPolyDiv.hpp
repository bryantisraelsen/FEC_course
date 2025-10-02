#ifndef BinPolyDiv_HPP
#define BinPolyDiv_HPP
#include <cstdint>
#include <iostream>
#include <cstring>
class BinPolyDiv {
public:
   BinPolyDiv(uint8_t *g_i, uint32_t p_i)
   {
      p = p_i;
      std::memset(g, 0, sizeof(g));
      std::memcpy(g, g_i, p + 1);
   }

   uint32_t div(uint8_t *d, uint32_t ddegree, uint8_t *q, uint32_t &quotientdegree, uint32_t &remainderdegree)
   {
      ddegree++;
      flipArray(d, ddegree);
      uint32_t answer = 0;
      uint32_t remainder = 0;
      uint8_t output = 0;
      uint32_t int_g = toUint(g, p+1);
      uint32_t remainder_top_bit_mask = 1<<p;
      int_g = int_g - remainder_top_bit_mask;
      int order = ddegree-1;
      uint32_t mask1 = 1;
      uint8_t answer_started = 0;
      for(int i = 0; i < p-1; i++)
      {
         mask1 = mask1 << 1;
         mask1 += 1;
      }
      for(int i = 0; i < ddegree; i++)
      {
         order--;
         remainder = remainder << 1;
         remainder &= mask1;
         remainder += d[i];
         if (output == 1)
         {
            remainder ^= int_g;
         }
         if (remainder & (remainder_top_bit_mask>>1))
         {
            output = 1;
            if (i != ddegree-1)
            {
               if (answer_started == 0)
               {
                  answer_started = 1;
                  quotientdegree = order;
               }
               answer |= 1<<(order);
               *(q+order) = 1;
            }
            else
            {
               *(q+order) = 0;
            }
         }
         else
         {
            output = 0;
         }
         remainderdegree = highestBitIndex(remainder);
      }

      return answer;
   }

   uint32_t remainder(uint8_t *d, uint32_t n, uint32_t &remainderdegree)
   {
      n++;
      flipArray(d, n);
      uint32_t answer = 0;
      uint32_t remainder = 0;
      uint8_t output = 0;
      uint32_t int_g = toUint(g, p+1);
      uint32_t remainder_top_bit_mask = 1<<p;
      int_g = int_g - remainder_top_bit_mask;
      int order = n-1;
      uint32_t mask1 = 1;
      uint8_t answer_started = 0;
      for(int i = 0; i < p-1; i++)
      {
         mask1 = mask1 << 1;
         mask1 += 1;
      }
      for(int i = 0; i < n; i++)
      {
         order--;
         remainder = remainder << 1;
         remainder &= mask1;
         remainder += d[i];
         if (output == 1)
         {
            remainder ^= int_g;
         }
         if (remainder & (remainder_top_bit_mask>>1))
         {
            output = 1;
            if (i != n-1)
            {
               if (answer_started == 0)
               {
                  answer_started = 1;
               }
               answer |= 1<<(order);
            }
         }
         else
         {
            output = 0;
         }
         remainderdegree = highestBitIndex(remainder);
      }

      return remainder;
   }

   uint32_t toUint(uint8_t* arr, size_t n)
   {
      uint32_t value = 0;
      for (size_t j = 0; j < n; j++) {
         if (arr[j]) {
            value |= (1u << j);
         }
      }
      return value;
   }

   int highestBitIndex(uint32_t x)
   {
      if (x == 0)
      {
         return -1;
      }
      int index = 0;
      while (x >>= 1)
      { //shift until x becomes 0
         index++;
      }
    return index;
   }

   void flipArray(uint8_t* arr, size_t n)
   {
      size_t i = 0;
      size_t j = n - 1;
      while (i < j)
      {
         uint8_t temp = arr[i];
         arr[i] = arr[j];
         arr[j] = temp;
         i++;
         j--;
      }
   }

   void printPolynomial(uint32_t poly)
   {
      bool first = true;

      //from highest bit to lowest
      for (int i = 31; i >= 0; i--)
      {
         if (poly & (1u << i))
         {
            if (!first)
            {
               std::cout << "+";
            }

            if (i == 0)
            {
               std::cout << "1";
            }
            else if (i == 1)
            {
               std::cout << "x";
            }
            else
            {
               std::cout << "x^" << std::dec << i;
            }

            first = false;
         }
      }

    if (first) {
        std::cout << "0";
    }

    std::cout << std::endl;
   }

private:
   uint8_t g[100];  //divisor
   uint32_t p; //order of divisor
};
#endif
