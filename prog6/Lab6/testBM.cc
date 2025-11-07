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
   // GF2 test
   GF2 d1[] = {1,1,1,0,1,0,0};           // array of data
   GF2 c1a[6];
   polynomialT<GF2> c = berlmass(d1,7);  // polynomial form
   cout << "F2 polynomial form: c=" << c << endl << endl << endl;

   // ModAr test
   Z5 d2[] = {2,3,4,2,2,3};          // array of data
   Z5 c2a[6];
   polynomialT<Z5> c2 = berlmass(d2,6); // polynomial form
   cout << "Z5 c=" << c2 << endl << endl << endl;


   GFNUM2m::initgf(4,0x13);             // Initialize field: 1 011 = 1+x+x^4

   GFNUM2m d4[] = {0,A^3,A^4,A^7};
   GFNUM2m c4a[4];
   polynomialT<GFNUM2m> c4 = berlmass(d4,4);// polynomial form
   cout << "GF(16) c=" << c4 << endl << endl << endl;
}

/*
Local Variables:
compile-command: "g++ -o testBM -g testBM.cc GFNUM2m.cc"
End:
*/
