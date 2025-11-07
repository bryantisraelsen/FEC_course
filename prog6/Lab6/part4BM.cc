//  Program: testBM.cc --- test the Berlekamp Massey algorithm
//  Todd K. Moon

#include "GF2.h"                // provide binary arithmetic
#include "GFNUM2m.h"            // provide GF(2^m) arithmetic
#include "ModArnew.h"              // Provide arithmetic mod 5
#include "polynomialT.cc"       // provide polynomial operations
#include "berlmass.cc"          // Berlekamp-Massey algorithm

// create instantiations of the polynomial class of type GF2
template class polynomialT<GF2>;
template class polytemp<GF2>;
typedef ModAr<5> Z5;


// create instantiations of the polynomial class of type GFNUM2m
template class polynomialT<GFNUM2m>;
template class polytemp<GFNUM2m>;

// create instantiations of the polynomial class of type ModAr
template class polynomialT<Z5>;
template class polytemp<Z5>;

int main()
{
   int j;
   int l;
   GFNUM2m::initgf(4,0x13);             // Initialize field: 1 011 = 1+x+x^4

   GFNUM2m d4[] = {0,0,A^5,0,1,A^10};
   GFNUM2m c4a[6];
   polynomialT<GFNUM2m> c4 = berlmass(d4,6);// polynomial form
   cout << "GF(16) c=" << c4 << endl << endl << endl;
}

/*
Local Variables:
compile-command: "g++ -o testBM -g testBM.cc GFNUM2m.cc"
End:
*/
