// BinConv.cc -- (n,k) binary convolutional coder
// Todd K. Moon

// Copyright 2004 by Todd K. Moon
// Permission is granted to use this program/data
// for educational/research only

#include "BinConvFIR.h"			// the multi-input convolutional object
#include "matalloc.h"
#include <iostream>
using namespace std;

static inline unsigned int bit_parity(unsigned int x)
{
    unsigned int p = 0;
    while(x) {
        p ^= (x & 1);
        x >>= 1;
    }
    return p;
}

BinConvFIR::BinConvFIR(int in_k, int in_n, int *degs, unsigned int** h_in)
   : BinConv(in_k,in_n)
{
   int i,j;

   CALLOCMATRIX(h,unsigned int, k,n);
   nui = new int[k];
   mem = new unsigned int[k];
   maxdeg = 0;
   nu = 0;
   for(i = 0; i < k; i++) {
	  nui[i] = degs[i];
	  if(nui[i] > maxdeg) maxdeg = nui[i];
	  nu += nui[i];
	  for(j = 0; j < n; j++) {
		 h[i][j] = h_in[i][j];
	  }
   }
}


// encode ins[0] ... ins[k-1] to get the n outputs
unsigned int *
BinConvFIR::encode(const unsigned char *ins)
{
   bool shifting_off_one[k];
   //update shift register
   for(int i = 0; i < k; i++)
   {
      if (mem[i] & (1U << (nui[i]-1)) )
      {
         shifting_off_one[i] = true;
         //cout << "shifting off a 1 for " << i << endl;
      }
      else
      {
         //cout << "not shifting off a 1 for " << i << endl;
         shifting_off_one[i] = false;
      }
      mem[i] <<= 1;
      mem[i] |= (ins[i] & 1);    //new bit at lsb
      mem[i] &= ((1U << (nui[i])) - 1); //mask bits that are over the storage elements
   }

   for(int j = 0; j < n; j++)
   {
      unsigned int outbit = 0;

      for(int i = 0; i < k; i++)
      {
         unsigned int poly = h[i][j];   //generator polynomial for input i, output j
         //cout << "h[" << i << "][" << j << "] = " << h[i][j] << endl;
         unsigned int taps = mem[i] & poly;
         //cout << "taps = " << taps << endl;

         outbit ^= bit_parity(taps);
         //cout << "outbit before last xor is " << outbit << endl;
         //cout << "poly is " << poly << endl;
         //cout << "(1U << (nui[i])) is " << (1U << (nui[i])) << endl;
         if (shifting_off_one[i] && (poly & (1U << (nui[i]))))
         {
            outbit ^= 1;
         }
         //cout << "outbit after last xor is " << outbit << endl;
      }

      outs[j] = outbit & 1; //1 bit out
   }
   return outs;
}

unsigned int
BinConvFIR::getstate() const
{
   unsigned int state = 0;

   for(int i = k - 1; i >= 0; i--)
   {
      state <<= nui[i];
      state |= mem[i];
   }
   return state;
}

void
BinConvFIR::setstate(unsigned int state)
{
   for(int i = 0; i < k; i++)
   {
      mem[i] = state & ((1U << nui[i]) - 1);
      state >>= nui[i];
   }
}

/*
Local Variables:
compile-command: "g++ -o testconvFIR -g testconvFIR.cc BinConvFIR.cc"
End:
*/
