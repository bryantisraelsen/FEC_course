//  Program: testconvdec.cc
//
//  Todd K. Moon
//
// Copyright 2004 by Todd K. Moon
// Permission is granted to use this program/data
// for educational/research only

#include <iostream>
#include <fstream>
using namespace std;

extern "C" {
#include <stdio.h>
}

#include "BinConvFIR.h"
#include "BinConvdec01.h"
#include "BinConvdecBPSK.h"
#include "matalloc.h"
#include "BPSKmodvec.h"
#include <random>

double gauss_noise(double stddev)
{
   static mt19937_64 rng(12345);
   static normal_distribution<double> dist(0.0, 1.0);
   return dist(rng)*stddev;
}

double mod_uncoded(unsigned char b)
{
   if (b==0)
   {
      return -1.0;
   }
   else
   {
      return 1.0;
   }
}

double Q(double x)
{
   return 0.5 * erfc(x/sqrt(2.0));
}

unsigned char flip(unsigned char b, double flip_prob)
{
   if ((double)rand()/RAND_MAX < flip_prob)
   {
      return 1-b;
   }
   else
   {
      return b;
   }
}

int main()
{
   int i;
   int decout;
   ofstream outfile("results.txt");

   unsigned int **h;

   int k = 1;					// two inputs
   int n = 2;					// three outputs
   CALLOCMATRIX(h,unsigned int, k,n);
   // G = [D^2+1 D^2+D+1]
   h[0][0] = 3;  h[0][1] = 5;  // first row of G
   int p[] = {2};        // degrees of rows of G

   BinConvFIR conv(k,n,p,h);
   BinConvdec01 decoder(conv,8);
   BinConvdecBPSK decoderBPSK(conv,8);
   BPSKmodvec modulator(n);

   for(double EcN0_dB = 0; EcN0_dB <= 7.0; EcN0_dB += 1.0) {
      cout << "EcN0_dB is " << EcN0_dB << endl;
      double EcN0_lin = pow(10.0, EcN0_dB/10.0);
      double sigma = sqrt( 1.0 / (2*EcN0_lin) );
      double flip_prob = Q(sqrt(2*EcN0_lin));

      int errors_uncoded = 0;
      int errors_hard = 0;
      int errors_soft = 0;
      int total_bits = 0;
      int total_bits_hard = 0;
      int total_bits_soft = 0;
      unsigned int *out;

      while(errors_uncoded < 1000)
      {
         unsigned char b = rand() & 1;

         double tx = mod_uncoded(b);
         double rx = tx + gauss_noise(sigma);
         unsigned char b_hat_uncoded;
         if(rx < 0)
         {
            b_hat_uncoded = 0;
         }
         else
         {
            b_hat_uncoded = 1;
         }

         total_bits++;
         if(b != b_hat_uncoded)
         {
            errors_uncoded++;
         }
      }

      unsigned char d[8] = {1,1,0,0,1,0,1,0};
      unsigned char d_out[8] = {0};
      for(int i = 0; i < 8; i++) d_out[i] = 0;
      while (errors_hard < 1000)
      {
         int N = sizeof(d)/k;
         unsigned int *out;
         for(i = 0; i < N; i++) {
	        out = conv.encode(&d[i]);
	        // corrupt the data
	        for(int j = 0; j < 2; j++)
           {
               out[0] = flip(out[0], flip_prob);
               out[1] = flip(out[1], flip_prob);
           }
	        decout = decoder.decode(out);
         }
         int j = 0;
         while(decoder.getinpnow(1)) {
           d_out[j] = decoder.inputs;
           j++;
         }
         d_out[j] = decoder.inputs;

         for (int j = 0; j < 8; j++)
         {
            if (d_out[j] != d[j])
            {
               errors_hard++;
               //cout << "errors hard is " << errors_hard << endl;
            }
         }
         total_bits_hard+=8;
      }

      for(int i = 0; i < 8; i++) d_out[i] = 0;
      while(errors_soft < 100 && total_bits_soft < 1e8)
      {
         int N = sizeof(d)/k;
         unsigned int *out;
         for(i = 0; i < N; i++) {
	        out = conv.encode(&d[i]);
           double *mod = modulator.mod(out);
           double rx_soft[2];
	        // corrupt the data
           rx_soft[0] = mod[0] + gauss_noise(sigma);
           rx_soft[1] = mod[1] + gauss_noise(sigma);

	        decout = decoderBPSK.decode(rx_soft);
         }
         int j = 0;
         while(decoderBPSK.getinpnow(1)) {
           d_out[j] = decoderBPSK.inputs;
           j++;
         }
         d_out[j] = decoderBPSK.inputs;

         for (int j = 0; j < 8; j++)
         {
            //cout << "d_out[" << j << "] is " << (float)d_out[j] << " and d[" << j << "] is " << (float)d[j] << endl;
            if (d_out[j] != d[j])
            {
               errors_soft++;
               //cout << "errors soft is " << errors_soft << endl;
               //cout << "d_out[" << j << "] is " << (float)d_out[j] << " and d[" << j << "] is " << (float)d[j] << endl;
            }
         }
         total_bits_soft+=8;

      }

      // Output one line to file
      outfile << EcN0_dB << " "
            << (double)errors_uncoded/total_bits << " "
            << (double)errors_hard/total_bits_hard << " "
            << (double)errors_soft/total_bits_soft << "\n";
   }
   outfile.close();

}


/*
Local Variables:
compile-command: "g++ -o testconvdec -g testconvdec.cc Convdec.cc BinConvFIR.cc BinConvdec01.cc BinConvdecBPSK.cc"
End:
*/
