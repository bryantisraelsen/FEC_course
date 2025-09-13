#include "BinLFSR.hpp"
#include <iostream>

int main (int argc, char** argv)
{
   int iterations = 16;
   uint32_t g = 0x17;
   uint32_t n = 4;
   uint32_t init_state = 0x1;
   if (argc < 5)
   {
      std::cout << "Please give iterations, polynomial, max degree of polynomial, and initial state\n";
      return -1;
   }
   char* endptr;
   iterations = atoi(argv[1]);
   g = (uint32_t)std::strtol(argv[2], &endptr, 0);
   n = (uint32_t)std::strtol(argv[3], &endptr, 0);
   init_state = (uint32_t)std::strtol(argv[4], &endptr, 0);
   std::cout << "g is 0x" << std::hex << g << "\n\n";
   std::cout << "n is 0x" << std::hex << n << "\n\n";
   std::cout << "init_state is 0x" << std::hex << init_state << "\n\n";
   uint32_t state = init_state;
   uint8_t output;
   BinLFSR lfsr(g, 4, state);
   output = lfsr.get_cur_output();
   std::cout << "State is 0x" << std::hex << state << std::endl;
   std::cout << "Output is " << (uint32_t)output << "\n\n";
   char output_array[100];
   uint32_t state_array[100];
   state_array[0] = state;
   output_array[0] = output;
   for(int i = 0; i<iterations; i++)
   {
      output = lfsr.step(state);
      std::cout << "State is 0x" << std::hex << state << std::endl;
      std::cout << "Output is " << (uint32_t)output << "\n\n";
      state_array[i+1] = state;
      output_array[i+1] = output;
   }

   //print the result
   for(int i = 0; i <= iterations; i++)
   {
      std::cout << "For iteration " << std::dec << i << " state was 0x" << std::hex << state_array[i] << " and output was " << (uint32_t)output_array[i] << "\n";
   }

}
