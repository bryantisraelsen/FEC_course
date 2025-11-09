// gcdpoly.cc --- Implement a gcd algorithm for a general
// polynomial type.  Also, implement a gcd for polynomials with real
// coefficients, truncating coefficients as necessary to avoid
// roundoff problems.
//
// Copyright 2019 by Todd K. Moon
// Permission is granted to use this program/data
// for educational/research only

#include <math.h>
#include "polynomialT.h"

// declare the gcd function, setting up a default value for the rdeg
template <class T> void
gcd(const polynomialT<T> &a, const polynomialT<T> &b, 
	polynomialT<T> &g,
	polynomialT<T> &s, polynomialT<T> &t, int rdeg=0);
// Function definition: gcd
template <class T>  void
sugiyama(const polynomialT<T> &a, const polynomialT<T> &b, polynomialT<T> &r,
	polynomialT<T> &s, polynomialT<T> &t, int p)
{
   polynomialT<T> g;
   polynomialT<T> qi;  // quotient
   polynomialT<T> ri, rim1, rim2, si, sim1, sim2, ti, tim1, tim2;
   polynomialT<T> *rip, *rim1p, *rim2p, *sip, *sim1p, *sim2p;
   polynomialT<T> *tip, *tim1p, *tim2p;
   polynomialT<T> *temp;
   T norm;
   auto trim_poly = [](polynomialT<T> &p) {
      int deg = p.getdegree();
      // scan down to find true top coefficient
      int newdeg = deg;
      while (newdeg >= 0) {
         if (p.getcoeff(newdeg) != T(0)) break;
            --newdeg;
      }
      if (newdeg < 0) {
         // make it the zero polynomial (degree = 0 with coeff 0)
         p.resizecopy(0);
         p.setc(0, T(0));
      } else if (newdeg != deg) {
         p.resizecopy(newdeg);
      }
   };
   sim2 = {1};
   sim1 = {0};
   tim2 = {0};
   tim1 = {1};
   rim2 = a;
   rim1 = b;
   polynomialT<T> exit_cond = {0};
   ri = b;
   int i = 0;
   int max_iters = 4 * (a.getdegree() + 1) + 1000; // generous cap
   while(ri.degree >= p)
   {
      if (i > max_iters) {
         cout << "sugiyama: exceeded max iterations - aborting EEA" << endl;
         // fallback: set trivial results (or call berlmass)
         r = polynomialT<T>(T(0));
         s = polynomialT<T>(T(1));
         t = polynomialT<T>(T(0));
         return;
      }
      i++;
      if (i == 1)
      {
         //initial conditions
         rim2 = a;
         rim1 = b;
         sim2 = {1};
         sim1 = {0};
         tim2 = {0};
         tim1 = {1};
      }
      else
      {
         //progress along the pipeline
         rim2 = rim1;
         rim1 = ri;
         sim2 = sim1;
         sim1 = si;
         tim2 = tim1;
         tim1 = ti;
      }
      trim_poly(rim2);
      trim_poly(rim1);
      // If rim1 is zero polynomial, cannot divide; fallback
      if ( (rim1.getdegree() == 0 && rim1.getcoeff(0) == T(0)) ) {
         cout << "sugiyama: rim1 is zero polynomial -> aborting EEA" << endl;
         r = polynomialT<T>(T(0));
         s = polynomialT<T>(T(1));
         t = polynomialT<T>(T(0));
         return;
      }

      // Also ensure leading coefficient of rim1 is nonzero (should be after trim)
      if (rim1.getcoeff(rim1.getdegree()) == T(0)) {
         cout << "sugiyama: rim1 leading coeff is zero after trim -> aborting" << endl;
         r = polynomialT<T>(T(0));
         s = polynomialT<T>(T(1));
         t = polynomialT<T>(T(0));
         return;
      }
      qi = rim2/rim1;
      ri = rim2 - qi * rim1;
      si = sim2 - qi * sim1;
      ti = tim2 - qi * tim1;
      trim_poly(ri);
      trim_poly(si);
      trim_poly(ti);
   }
   //cout << "exiting while loop" << endl;
   r = ri;
   g = rim1;
   t = ti;
   s = si;
}

