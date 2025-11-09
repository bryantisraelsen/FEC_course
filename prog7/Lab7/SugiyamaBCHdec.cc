// BCHdec.cc -- a general BCH decoder
// Todd K. Moon
#include "SugiyamaBCHdec.h"
#include "sugiyama.cc"
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
   GFNUM2m s[t2];
    for (int j = 0; j < t2; j++) {
        s[j] = GFNUM2m(0);
        for (int i = 0; i < n; i++) {
            if (r[i] == 1)
                s[j] += (A1 ^ ((i * (j + 1)) % GFNUM2m::getN()));
        }
    }

   // Step 2: Determine the error locator polynomial
   polynomialT<GFNUM2m> a, b, r_poly, s0, tpoly;

   a.buildspace(2*t);
   a.setc(2*t, GFNUM2m(1));

   // Construct b(x) = S(x)
   b.buildspace(t2 - 1);
   for (int j = 0; j < t2; j++)
       b[j] = s[j];

   // Run Sugiyama algorithm
   int p_0 = t;
   sugiyama(b, a, r_poly, s0, tpoly, p_0);

   // The error locator polynomial is s0
   polynomialT<GFNUM2m> Lambda_poly = s0;

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
	  
