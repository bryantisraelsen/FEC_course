//  Program: ChienSearch.cc
//  Todd K. Moon

#include "ChienSearch.h"

GFNUM2m *
ChienSearch::Search(GFNUM2m *poly, int nu, int & nroots)
// Lambda(x) = poly[0] + poly[1] x + ... + poly[nu]x^nu
{
   nroots = 0;
   for (int j = 0; j <= t; j++) {
      if (j <= nu) Lambdas[j] = poly[j];
      else Lambdas[j] = GFNUM2m(0);
   }

   alphapowers[0] = GFNUM2m(1);
   for (int j = 1; j <= t; j++) {
      alphapowers[j] = (A ^ (-j));
   }

   int n = (1 << GFNUM2m::getm()) - 1;


   GFNUM2m val;
   for (int i = 0; i < n; i++) {
      val = Lambdas[0];
      for (int j = 1; j <= nu; j++) {
         val += Lambdas[j];
      }

      if (val == GFNUM2m(0)) {
         roots[nroots++] = (A^(-i));
      }

      for (int j = 1; j <= nu; j++) {
         Lambdas[j] *= alphapowers[j];
      }
   }

   return roots;

}


/*
Local Variables:
compile-command: "g++ -c -g ChienSearch.cc"
End:
*/


