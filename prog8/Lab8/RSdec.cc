// RSdec.cc -- a general Reed-Solomon decoder
// Todd K. Moon
// Copyright 2004 by Todd K. Moon
// Permission is granted to use this program/data
// for educational/research only

#include "RSdec.h"
//#include "berlmass2.cc"

#include "berlmass.cc"

//#include "gcdpoly.cc"
 #define BMALG					// define this to use BM alg. for decoding
// otherwise, Euclidean algorithm is used for decoding


// construtor
RSdec::RSdec(int t_in, int n_in, GFNUM2m A1_in)
   :Searcher(t_in)
{
   t = t_in;
   t2 = 2*t_in;
   n = n_in;
   A1 = A1_in;
   s = new GFNUM2m[2*t];
   Lambda = new GFNUM2m[t+1];
   spoly.setc(t2,1);  // allocate space for this
   Lambdap.setc(t,1); // allocate space for this
}

int RSdec::decode(unsigned char *r, unsigned char *dec)
{
   int i;
   GFNUM2m rgf[n];
   GFNUM2m decgf[n];
   for(i = 0; i < n; i++) {
	  rgf[i] = r[i];
   }
   int ret = decode(rgf,decgf);
   for(i = 0; i < n; i++) {
	  dec[i] = decgf[i].getv();
   }
   return ret;
}


#ifdef BMALG
int
RSdec::decode(GFNUM2m *r, GFNUM2m *dec)
{
   int i,j;
   int errloc;
   GFNUM2m p,dp2;			  // fast computation of formal derivative
   GFNUM2m x;
   GFNUM2m *rs;					// array of roots

   for (i = 0; i < n; i++) {
      //cout << "r[" << i << "] = " << r[i] << endl;
      dec[i] = r[i];  // copy received bits
   }

   // Step 1: evaluate the syndromes
   for (j = 0; j < t2; j++)
   {
      s[j] = GFNUM2m(0);

      for (i = 0; i < n; i++)
      {
         s[j] += r[i] * (A1 ^ ((j+1) * i));   // r[i] is the actual symbol
      }
   }

   // Step 2: Determine the error locator polynomial
   polynomialT<GFNUM2m> Lambda_poly = berlmass(s, t2);
   nu = Lambda_poly.getdegree();
   for (i = 0; i <= nu; i++) {
      Lambda[i] = Lambda_poly[i];
   }
   //cout << "Lambda poly is " << Lambda_poly << endl;


   // Step 3: Find the roots of the error locator polynomial
   int nroots; 
   rs = Searcher.Search(Lambda,nu,nroots); // from ChienSearch
   //for (int i = 0; i < nroots; i++)
   //{
   //   cout << "root " << i << " is " << rs[i] << endl;
   //}
   if (nroots == 0)
   {
      return nroots;
   }
   // Step 4: Find error values
   Lambdap.setc(Lambda, nu);
   polynomialT<GFNUM2m> t2_poly;
   t2_poly.setc(t2, 1);
   for (int i = 0; i <= t2; i++)
   {
      spoly[i] = s[i];
   }
   polynomialT<GFNUM2m> a_x;
   a_x.buildspace(t2 + 1);
   a_x.setc(t2, GFNUM2m(1));
   Omega = (spoly * Lambdap) % a_x;
   polynomialT<GFNUM2m> Lprime;
   Lprime.setc(nu-1, 1);

   for(int i = 1; i <= nu; i++)
   {
      if (i % 2 == 1)
      {
         Lprime[i-1] = Lambda[i];
      }
      else
      {
         Lprime[i-1] = GFNUM2m(0);
      }
   }

   GFNUM2m d_Lambda[t + 1];
   for (int i = 0; i <= t; i++)
   {
      d_Lambda[i] = 0;
   }
   for (int i = 1; i <= nu; i++)
   {
      dp2 = GFNUM2m(0);
      for (int j = 0; j < i; j++)
      {
         dp2 += Lambda[i];
      }
      d_Lambda[i - 1] = dp2;
   }
   polynomialT<GFNUM2m> d_Lambdap;
   d_Lambdap.setc(d_Lambda, t - 1);

   //cout << "spoly is " << spoly << endl;
   //cout << "Omega is " << Omega << endl;
   //cout << "Lambdap is " << Lambdap << endl;
   //cout << "d_Lambdap is " << d_Lambdap << endl;
   GFNUM2m error_vals[n];
   for (int i = 0; i < nroots; i++)
   {
      GFNUM2m r_inv = rs[i]^-1;
      int location = r_inv.getp();
      GFNUM2m omega_val = Omega.evaluate(rs[i]);
      GFNUM2m lambda_val = d_Lambdap.evaluate(rs[i]);
      //cout << "Omega evaluation is " << omega_val << endl;
      //cout << "d_Lambda evaluation is " << lambda_val << endl;
      GFNUM2m error_val = -(omega_val/lambda_val);
      //cout << "error_val is " << error_val << endl;
      dec[location] += error_val;
      if (dec[location].getp() == 0 && error_val == 1)
      {
         dec[location] = error_val + error_val;
      }
      //cout << "dec[location is corrected to " << dec[location] << endl;
      error_vals[location] = (omega_val/lambda_val);
   }

   return nroots;
}


#else
#include "gcdpoly.cc"

// decoding using the Euclidean algorithm
int
RSdec::decode(GFNUM2m *r, GFNUM2m *dec)
{
   int i,j;
   int errloc;
   GFNUM2m p,dp;
   GFNUM2m dp2;					// fast computation of formal derivative
   GFNUM2m x;
   GFNUM2m *rs;					// array of roots

   for(i = 0; i < n; i++) {  // copy over the input bits
      //cout << "r[" << i << "] = " << r[i] << endl;
      dec[i] = r[i];
   }
   polytemp<GFNUM2m> *sS = polytemp<GFNUM2m>::gettemppoly(2*t-1);
   // Step 1: evaluate the syndromes
   for (j = 0; j < t2; j++)
   {
      s[j] = GFNUM2m(0);

      for (i = 0; i < n; i++)
      {
         s[j] += r[i] * (A1 ^ ((j+1) * i));   // r[i] is the actual symbol
      }
   }

   polynomialT<GFNUM2m> a_x;
   a_x.buildspace(t2 + 1);
   a_x.setc(t2, GFNUM2m(1));
   polynomialT<GFNUM2m> Theta,Omega;
   polynomialT<GFNUM2m> spoly_new;
   spoly_new.buildspace(t2-1);
   for (int i = 0; i < t2; i++)
   {
      spoly_new[i] = s[i];
   }
   // Step 2: Solve the key equation
   //cout << "a = a_x = " << a_x << endl << "b = spoly_new = " << spoly_new << endl;
   if (spoly_new[spoly_new.degree] == 0)
   {
      //cout << "ERROR spoly_new[spoly_new.degree] == 0" << endl;
      polynomialT<GFNUM2m> spoly_new_new;
      spoly_new_new.buildspace(t2-2);
      for (int i = 0; i < t2-1; i++)
      {
         spoly_new_new[i] = spoly_new[i];
      }
      gcd(a_x,spoly_new_new,Omega,Theta,Lambdap,t);
   }
   else
   {
      gcd(a_x,spoly_new,Omega,Theta,Lambdap,t);
   }

   nu = Lambdap.getdegree();
   for (i = 0; i <= nu; i++) {
      Lambda[i] = Lambdap[i];
   }

   //cout << "Omega is " << Omega << endl;
   //cout << "Lambdap is " << Lambdap << endl;

   // Step 3: Find the roots of the error locator polynomial
   int nroots; 
   rs = Searcher.Search(Lambda,nu,nroots); // from ChienSearch
   //for (int i = 0; i < nroots; i++)
   //{
   //   cout << "root " << i << " is " << rs[i] << endl;
   //}
   if (nroots == 0)
   {
      return nroots;
   }
   polynomialT<GFNUM2m> Lprime;
   Lprime.setc(nu-1, 1);

   for(int i = 1; i <= nu; i++)
   {
      if (i % 2 == 1)
      {
         Lprime[i-1] = Lambda[i];
      }
      else
      {
         Lprime[i-1] = GFNUM2m(0);
      }
   }

   GFNUM2m d_Lambda[t + 1];
   for (int i = 0; i <= t; i++)
   {
      d_Lambda[i] = 0;
   }
   for (int i = 1; i <= nu; i++)
   {
      dp2 = GFNUM2m(0);
      for (int j = 0; j < i; j++)
      {
         dp2 += Lambda[i];
      }
      d_Lambda[i - 1] = dp2;
   }
   polynomialT<GFNUM2m> d_Lambdap;
   d_Lambdap.setc(d_Lambda, t - 1);

   //cout << "d_Lambdap is " << d_Lambdap << endl;
   GFNUM2m error_vals[n];
   for (int i = 0; i < nroots; i++)
   {
      GFNUM2m r_inv = rs[i]^-1;
      int location = r_inv.getp();
      //cout << "location is " << location << endl;
      GFNUM2m omega_val = Omega.evaluate(rs[i]);
      GFNUM2m lambda_val = d_Lambdap.evaluate(rs[i]);
      //cout << "Omega evaluation is " << omega_val << endl;
      //cout << "d_Lambda evaluation is " << lambda_val << endl;
      GFNUM2m error_val = -(omega_val/lambda_val);
      //cout << "error_val is " << error_val << endl;
      dec[location] += error_val;
      if (dec[location].getp() == 0 && error_val == 1)
      {
         dec[location] = error_val + error_val;
      }
      //cout << "dec[location] is corrected to " << dec[location] << endl;
      error_vals[location] = (omega_val/lambda_val);
   }

   return nroots;
}


#endif
/*
Local Variables:
compile-command: "g++ -c -g RSdec.cc"
End:
*/
	  
