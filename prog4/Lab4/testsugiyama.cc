//
//  Program: testpolygcd.cc

#include <math.h>
#include "ModArnew.h"
#include "polynomialT.cc"
#include "sugiyama.cc"
//#include "gcdpoly.cc"

// create instantiations of the polynomial class of type ModAr
template class polynomialT<ModAr<5> >;
template class polytemp<ModAr<5> >;
// create instantiations of the polynomial class of type double
template class polynomialT<double>;
template class polytemp<double>;

typedef ModAr<5> Z5;

// Create an instantiation of the gcd function, for polynomials of type ModAr
template <class Z5 > void
gcd(const polynomialT<Z5> &a, const polynomialT<Z5> &b, 
	polynomialT<Z5> &g,
	polynomialT<Z5> &s, polynomialT<Z5> &t, int sdeg);

// Create an instantiation of the gcd function, for polynomials of type double
// template <double> void
// gcd(const polynomialT<double> &a, const polynomialT<double> &b, 
// 	polynomialT<double> &g,
// 	polynomialT<double> &s, polynomialT<double> &t, int sdeg);


int main()
{
   POLYC(Z5,a,{0,0,0,0,0,0,0,0,1}); // x^8
   POLYC(Z5,nega,{0,0,0,0,0,0,0,0,-1}); // -x^8
   POLYC(Z5,b,{3,2,3,1,4,0,4,3});       // 3+2x+3x^2+x^3+4x^4+4x^6+3x^7
   int p = 4;
   polynomialT<Z5> s_0, t, r;
   a.setprintdir(1);

   cout << "a=" << a << endl;
   cout << "b=" << b << endl;
   sugiyama(a,b,r,s_0,t,p);
   cout << "r=" << r << endl;
   cout << "s=" << s_0 << endl;
   cout << "t=" << t << endl;

   cout << "\n";
   polynomialT<Z5> bt,rhs;
   bt = b*t;
   rhs = r+s_0*nega;
   cout << "bt=" << bt << endl;
   cout << "r-as=" << rhs << endl;

   cout << "\n\n\n";
   int taps[4] = {2,4,2,1}; //t(x) = 1 + 2 x + 4 x^2 + 2 x^3 + 1 x^4

   // initial state s0..s3 are the first 4 terms of the sequence
   int s[8];
   s[0] = 3; s[1] = 2; s[2] = 1; s[3] = 0;
   int L = 4;
   // generate up to N terms (we already have first 4)
   for (int n = 4; n < 8; n++)
   {
      int acc = 0;
      // compute inner = c1*s[n-1] + c2*s[n-2] + ... + cL*s[n-L]
      for (int i = 1; i <= L; ++i)
         acc += taps[i-1] * s[n - i];
      // s[n] = -inner (mod 5)
      s[n] = (-1*acc)%5;
   }

   for (int i; i < 8; i++)
   {
      if (s[i] >= 0)
      {
         cout << "s[" << i << "] = " << (s[i]) << endl;
      }
      else
      {
         cout << "s[" << i << "] = " << (s[i]) + 5 << endl;
      }
   }





   POLYC(Z5,a_1,{0,0,0,0,0,0,0,0,1}); // x^8
   POLYC(Z5,nega_1,{0,0,0,0,0,0,0,0,-1}); // -x^8
   POLYC(Z5,b_1,{3,2,1,0,4,3,2,1});       // 3+2x+3x^2+x^3+4x^4+4x^6+3x^7
   polynomialT<Z5> s_1, t_1, r_1;
   a.setprintdir(1);

   cout << "\n\n\na=" << a_1 << endl;
   cout << "b=" << b_1 << endl;
   sugiyama(a_1,b_1,r_1,s_1,t_1,p);
   cout << "r=" << r_1 << endl;
   cout << "s=" << s_1 << endl;
   cout << "t=" << t_1 << endl;

   cout << "\n";
   polynomialT<Z5> bt_1,rhs_1;
   bt_1 = b_1*t_1;
   rhs_1 = r_1+s_1*nega_1;
   cout << "bt=" << bt_1 << endl;
   cout << "r-as=" << rhs_1 << endl;

   cout << "\n\n\n";
   int taps_1[2] = {3,1}; //t(x) = 1 + 3 x + x^2

   cout << "taps set" << endl;
   // initial state s0,s1 are the first 2 terms of the sequence
   int s_2[8];
   s_2[0] = 3; s_2[1] = 2;
   L = 2;
   // generate rest of terms
   for (int n = 2; n < 8; n++)
   {
      //cout << "n is " << n << endl;
      int acc = 0;
      // compute inner = c1*s[n-1] + c2*s[n-2] + ... + cL*s[n-L]
      for (int i = 1; i <= L; ++i)
         acc += taps_1[i-1] * s_2[n - i];
      // s[n] = -inner (mod 5)
      s_2[n] = (-1*acc)%5;
   }

   for (int i; i < 8; i++)
   {
      if (s_2[i] >= 0)
      {
         cout << "s[" << i << "] = " << (s_2[i]) << endl;
      }
      else
      {
         cout << "s[" << i << "] = " << (s_2[i]) + 5 << endl;
      }
   }

}

/*
Local Variables:
compile-command:"g++ -o testpolygcd -g testpolygcd.cc"
End:
*/


