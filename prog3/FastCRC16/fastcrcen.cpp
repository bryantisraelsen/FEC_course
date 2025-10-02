#include "FastCRC16.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

uint16_t FastCRC16::crctable[256];

int main (int argc, char** argv)
{

   //parse args
   if (argc != 4)
   {
      std::cout << "ERROR: Incorrect number of args" << std::endl;
      std::cout << "Usage: `fastcrcenc K filein fileout`" << std::endl;
      return -1;
   }

   uint32_t num_bytes = (uint32_t)atoi(argv[1]);
   //input file
   std::ifstream inputFile(argv[2], std::ios::binary | std::ios::in);
   if (!inputFile.is_open())
   {
      std::cerr << "Error: Could not open input file " << argv[2] << std::endl;
      return -1;
   }
   std::ofstream outputFile(argv[3], std::ios::binary | std::ios::out);
   if (!outputFile.is_open())
   {
      std::cerr << "Error: Could not open output file " << argv[3] << std::endl;
      inputFile.close();
      return -1;
   }

   //size of the input file
   inputFile.seekg(0, std::ios::end);
   long long fileSize = inputFile.tellg();
   inputFile.seekg(0, std::ios::beg);
   //input file contents buffer
   std::vector<uint8_t> buffer(fileSize);

   // Read the entire content of the input file into the buffer
   inputFile.read(reinterpret_cast<char*>(buffer.data()), fileSize);
   if (!inputFile)
   {
      std::cerr << "Error: Failed to read from input file." << std::endl;
      inputFile.close();
      outputFile.close();
      return -1;
   }

   size_t bitCount = buffer.size() * 8;
   uint8_t* bitArray = static_cast<uint8_t*>(malloc(bitCount * sizeof(uint8_t)));
   if (!bitArray)
   {
        return -1;
   }

   uint32_t g = 0x8005;
   FastCRC16 crc(g);

   const size_t block_len = 1024;  //block size in bytes
   std::vector<uint8_t> wanted;
   wanted.reserve(buffer.size() + (buffer.size() / block_len + 1) * 2); //preallocate for CRC bytes

   for (size_t i = 0; i < buffer.size(); i += block_len)
   {
      size_t current_block_len = std::min(block_len, buffer.size() - i);
      for (int j = 0; j < current_block_len; j++)
      {
         printf("buffer[%d] is 0x%X\n", j, buffer[j]);
      }
      uint32_t result = crc.CRC(&buffer[i], static_cast<int>(current_block_len));

      auto start_iter = buffer.begin() + i;
      auto end_iter   = start_iter + current_block_len;
      wanted.insert(wanted.end(), start_iter, end_iter);

      uint16_t crc16 = static_cast<uint16_t>(result);
      wanted.push_back(static_cast<uint8_t>((crc16 >> 8) & 0xFF));
      wanted.push_back(static_cast<uint8_t>(crc16 & 0xFF));

      std::cout << "Block " << (i / block_len) << " CRC = 0x" << std::hex << crc16 << std::dec << std::endl;
   }

   //write to output file
   outputFile.write(reinterpret_cast<const char*>(wanted.data()), wanted.size());
   if (!outputFile)
   {
      std::cerr << "Error: Failed to write to output file." << std::endl;
      inputFile.close();
      outputFile.close();
      return -1;
   }

   // Close the files
   inputFile.close();
   outputFile.close();

   std::cout << "Successfully ran!" << std::endl;

   return 0;

}
