#ifndef BinLFSR_HPP
#define BinLFSR_HPP
#include <cstdint>
#include <iostream>
class BinLFSR {
public:
   BinLFSR(void) //Default constructor
   {
      g = 0;
      n = 0;
      initstate = 0;
   };

   BinLFSR(uint32_t g_i, uint32_t n_i, uint32_t initstate_i=1) //constructor
   {
      g = g_i;
      n = n_i;
      initstate = initstate_i;
      curr_state = initstate_i;
      uint32_t highest_degree_mask = 1 << (n-1);
      if (highest_degree_mask & curr_state)
      {
         curr_output = 1;
      }
      else
      {
         curr_output = 0;
      }
   };

   void setstate(uint32_t state_i) //set initial state of LFSR
   {
      initstate = state_i;
      curr_state = state_i;
   };

   uint8_t step(void) //step the lfsr one state, return the 1 bit output
   {
      uint32_t highest_degree_mask = 1 << (n-1);
      if (curr_output == 1)
      {
         curr_state = curr_state << 1;
         curr_state += curr_output;
         uint32_t mask = g - 1;
         mask = mask - (highest_degree_mask << 1);
         //std::cout << "mask is 0x" << std::hex << mask << std::endl;
         curr_state ^= mask;
         uint32_t mask1 = 1;
         for(int i = 0; i < n-1; i++)
         {
            mask1 = mask1 << 1;
            mask1 += 1;
         }
         //std::cout << "mask1 is 0x" << std::hex << mask1 << std::endl;
         curr_state &= mask1;
      }
      else
      {
         //std::cout << "curr output is a 0" << std::endl;
         curr_state = curr_state << 1;
      }
      if (highest_degree_mask & curr_state)
      {
         curr_output = 1;
      }
      else
      {
         curr_output = 0;
      }
      return curr_output;
   };

   uint8_t step(uint32_t &state) //step the lfsr one state, return the 1 bit output and new state
   {
      uint32_t highest_degree_mask = 1 << (n-1);
      if (curr_output == 1)
      {
         curr_state = curr_state << 1;
         curr_state += curr_output;
         uint32_t mask = g - 1;
         mask = mask - (highest_degree_mask << 1);
         //std::cout << "mask is 0x" << std::hex << mask << std::endl;
         curr_state ^= mask;
         uint32_t mask1 = 1;
         for(int i = 0; i < n-1; i++)
         {
            mask1 = mask1 << 1;
            mask1 += 1;
         }
         //std::cout << "mask1 is 0x" << std::hex << mask1 << std::endl;
         curr_state &= mask1;
      }
      else
      {
         //std::cout << "curr output is a 0" << std::endl;
         curr_state = curr_state << 1;
      }
      state = curr_state;
      if (highest_degree_mask & curr_state)
      {
         curr_output = 1;
      }
      else
      {
         curr_output = 0;
      }
      return curr_output;
   };

   void steps(int nsteps, uint8_t *outputs) //step the LFSR nsteps times, return the array of 1-bit outputs
   {
      for(int i = 0; i < nsteps; i++)
      {
         uint32_t highest_degree_mask = 1 << (n-1);
         if (curr_output == 1)
         {
            curr_state = curr_state << 1;
            curr_state += curr_output;
            uint32_t mask = g - 1;
            mask = mask - (highest_degree_mask << 1);
            //std::cout << "mask is 0x" << std::hex << mask << std::endl;
            curr_state ^= mask;
            uint32_t mask1 = 1;
            for(int i = 0; i < n-1; i++)
            {
               mask1 = mask1 << 1;
               mask1 += 1;
            }
            //std::cout << "mask1 is 0x" << std::hex << mask1 << std::endl;
            curr_state &= mask1;
         }
         else
         {
            //std::cout << "curr output is a 0" << std::endl;
            curr_state = curr_state << 1;
         }
         if (highest_degree_mask & curr_state)
         {
            curr_output = 1;
         }
         else
         {
            curr_output = 0;
         }
         *(outputs+i) = curr_output;
      }
   };

   uint8_t get_cur_output(void)
   {
      return curr_output;
   }

private:
   uint32_t g; //connection polynomial
   uint32_t n; //degree of connection polynomial
   uint32_t initstate; //intitial state
   uint32_t curr_state;  //current state of the LFSR
   uint8_t curr_output;  //current state of the LFSR
};

#endif // MYCLASS_HPP
