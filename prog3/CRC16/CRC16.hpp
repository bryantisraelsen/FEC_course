#ifndef CRC16_HPP
#define CRC16_HPP
#include <cstdint>
#include <iostream>
#include <cstring>
#include "../BinPolyDiv/BinPolyDiv.hpp"
class CRC16 {
protected:
   BinPolyDiv div;   //divider object

public:
   CRC16(uint32_t crcpoly_i)  //contructor
      : div(polynomialToBitArray(crcpoly_i), orderOfPoly(crcpoly_i))
   {
      crcpoly = crcpoly_i;
      //degree
      int msbIndex = -1;
      for (int i = 31; i >= 0; --i)
      {
         if (crcpoly_i & (1u << i))
         {
            msbIndex = i;
            break;
         }
      }
      if (msbIndex == -1)
      {
         //if polynomial is zero
         order = 0;
      }
      order = static_cast<size_t>(msbIndex + 1);  //number of bits from MSB down to 0
   };



   uint32_t CRC(uint8_t *data, int len){
      uint32_t remainder_degree;
      int extended_len = len + 16;
      uint8_t* extended = static_cast<uint8_t*>(malloc(extended_len));
      std::memset(extended, 0, 16);
      std::memcpy(extended + 16, data, len);
      uint32_t rem = div.remainder(extended, (uint32_t)extended_len, remainder_degree);
      free(extended);
      return rem;
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


   uint32_t orderOfPoly(uint32_t poly)
   {
      //degree
      int msbIndex = -1;
      for (int i = 31; i >= 0; --i)
      {
         if (poly & (1u << i))
         {
            msbIndex = i;
            break;
         }
      }
      if (msbIndex == -1)
      {
         return 0;
      }
      return (uint32_t)(msbIndex);  //number of bits from MSB down to 0
   }



   uint8_t* polynomialToBitArray(uint32_t poly)
   {
      //degree
      uint32_t outLength;
      int msbIndex = -1;
      for (int i = 31; i >= 0; --i)
      {
         if (poly & (1u << i))
         {
            msbIndex = i;
            break;
         }
      }
      if (msbIndex == -1)
      {
         //if polynomial is zero
         outLength = 0;
         return nullptr;
      }
      outLength = (uint32_t)(msbIndex + 1);  //number of bits from MSB down to 0
      uint8_t* bits = static_cast<uint8_t*>(malloc(outLength * sizeof(uint8_t)));
      if (!bits)
      {
         outLength = 0;
         return nullptr; //allocation fail
      }
      for (uint32_t i = 0; i < outLength; ++i)
      {
         bits[i] = (poly & (1u << i)) ? 1 : 0;
      }
      return bits;
   }
private:
   uint32_t crcpoly;   //crc polynomial
   uint32_t order; //order of the crc polynomial
};
#endif
