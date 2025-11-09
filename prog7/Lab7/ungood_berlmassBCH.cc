#ifndef BERLMASSBCH_CC
#define BERLMASSBCH_CC

#include "polynomialT.h"

template <class T> polynomialT<T>
berlmassBCH(const T* s, int n)
// s = input coefficients s[0],s[1],... s[n-1]
// returns = final connection polynomial
{
   cout << "starting berlmassBCH.cc" << endl;
   for (int i = 0; i < n; i++)
   {
      cout << "s[" << i << "] = " << s[i] << " ";
   }
   cout << endl;
   int L = 0;
   polynomialT<T> c;
   c[0] = T(1);
   polynomialT<T> p(c), t;      //p is previous, t is temporary
   int shift = 1;               //n-m
   T dm = T(1);                 //previous discrepancy
   T d;                         //current discrepancy
   int j;
   for(int k=0; k < n/2; k+=2)
   {
      d = s[k];
      int maxj = min(L, c.getdegree());
      for (j = 1; j <= maxj; j++)
      {
         d = d + c[j]*s[k-j];
      }
      if (d == 0)
      {
         shift++;
      }
      else
      {
         if (2*L >= k+1)
         {
            c = c - ((p << shift)*(d/dm));
            shift++;
         }
         else
         {
            t = c;
            c = c - ((p << shift)*(d/dm));
            L = k+1 - L;
            p = t;
            dm = d;
            shift = 1;
         }
         shift++;
      }
      cout<< " k="<< k+1 << " s=" << s[k] << " d=" << d << "  c=" << c << "  L=" << L;
      cout << " p=" << p << "  l=" << shift << " dm=" << dm << endl;

   }
   return c;
}


#endif
/*
Local Variables:
compile-command: "g++ -g berlmass.cc"
End:
*/



