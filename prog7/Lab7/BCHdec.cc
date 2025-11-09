// BCHdec.cc -- a general BCH decoder
// Todd K. Moon
#include "BCHdec.h"
//#include "berlmass2.cc"
#include "berlmass.cc"
#include "polynomialT.cc"
template class polynomialT<GFNUM2m>;
template class polytemp<GFNUM2m>;

BCHdec::BCHdec(int t_in, int n_in, GFNUM2m A1_in) :
   Searcher(t_in)
{
   t = t_in;
   t2 = 2*t_in;
   n = n_in;
   A1 = A1_in;
   s = new GFNUM2m[2*t];
   Lambda = new GFNUM2m[t+1];
}

void
BCHdec::decode(GF2 *r, GF2 *dec)
{
   int i,j;
   int errloc;
   GFNUM2m p;
   GFNUM2m x;
   GFNUM2m *rs;					// array of roots

   // Step 1: evaluate the syndromes
   for (j = 0; j < t2; j++) {
      s[j] = GFNUM2m(0);         // clear syndrome
      GFNUM2m Aj = A1 ^ (j + 1);

      for (i = 0; i < n; i++) {
         if (r[i] == 1) {
            s[j] += (A1 ^ ((i * (j + 1)) % GFNUM2m::getN()));
         }
      }
   }

   // Step 2: Determine the error locator polynomial
   polynomialT<GFNUM2m> Lambda_poly = berlmass(s, t2);
   nu = Lambda_poly.getdegree();
   for (i = 0; i <= nu; i++) {
      Lambda[i] = Lambda_poly[i];
   }

   // Step 3: Find the roots of the error locator polynomial
   int nroots; 
   rs = Searcher.Search(Lambda,nu,nroots); // from ChienSearch

   // Step 4: Find error values: Not necessary for binary BCH codes

   // Step 5: Correct errors corresponding to inverse roots
   for (i = 0; i < n; i++) {
      dec[i] = r[i];  // copy received bits
   }

   for(i = 0; i < nroots; i++) {
	  errloc = (GFNUM2m::getN() - rs[i].getp()) % GFNUM2m::getN();
	  dec[errloc] = 1+dec[errloc];  // complement the bits
   }
}


/*
Local Variables:
compile-command: "g++ -c -g BCHdec.cc"
End:
*/
	  
