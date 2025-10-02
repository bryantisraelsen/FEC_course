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
      std::cout << "Usage: `fastcrcdec K filein fileout`" << std::endl;
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
   std::cout << "buffer size is " << fileSize << std::endl;

   //entire content of the input file into the buffer
   inputFile.read(reinterpret_cast<char*>(buffer.data()), fileSize);
   if (!inputFile)
   {
      std::cerr << "Error: Failed to read from input file." << std::endl;
      inputFile.close();
      outputFile.close();
      return -1;
   }

   std::vector<uint8_t> message(buffer.begin(), buffer.begin() + num_bytes - 2);;

   const size_t block_len = 1024 + 2;
   uint32_t g = 0x8005;
   FastCRC16 crc(g);
   size_t num_blocks = fileSize/block_len;
   size_t leftover = fileSize%block_len;
   if (leftover != 0)
   {
      num_blocks += 1;
   }

   int err_cnt = 0;
   for (int i=0; i < buffer.size(); i+=block_len)
   {
      size_t start = i;
      size_t end = start + std::min(block_len, buffer.size()-i);

      //data portion
      size_t data_len = (end-start)-2;

      uint32_t result = crc.CRC(&buffer[i], static_cast<int>(data_len));
      uint16_t calc_crc = static_cast<uint16_t>(result);

      uint16_t recv_crc = (static_cast<uint16_t>(buffer[end - 2]) << 8) |
                           static_cast<uint16_t>(buffer[end - 1]);

      if (calc_crc != recv_crc)
      {
         err_cnt++;
         std::cout << "Block " << i/block_len << ": CRC ERROR — received 0x" << std::hex << recv_crc << ", calculated 0x" << calc_crc << std::dec << "\n";
      }

      outputFile.write(reinterpret_cast<const char*>(&buffer[start]), data_len);
      if (!outputFile)
      {
         std::cerr << "Error: Failed writing decoded block " << i/block_len << "\n";
         return -1;
      }
   }

   std::cout << "error count is " << err_cnt << std::endl;
   inputFile.close();
   outputFile.close();
   std::cout << "Successfully decoded " << num_blocks << " blocks.\n";
   return 0;
}
