// RSenc.cc -- a general RS encoder
// Todd K. Moon
// Copyright 2004 by Todd K. Moon
// Permission is granted to use this program/data
// for educational/research only

#include "RSenc.h"
#include "polynomialT.cc"
#include <iostream>
using namespace std;

template class polynomialT<GFNUM2m>;
template class polytemp<GFNUM2m>;

RSenc::RSenc(int n_in, int k_in, int t_in, int j0_in, GFNUM2m A1_in)
// constructor
{
   n = n_in;
   k = k_in;
   t = t_in;
   j0 = j0_in;
   A1 = A1_in;
   g = GFNUM2m(1);
   GFNUM2m lc[2] = {1,1};
   polynomialT<GFNUM2m> l(1,lc);  // set up the linear term
   for(int i=0; i < 2*t; i++) {
	  l[0] = (A1^(j0+i));
	  g *= l;
   }
   m.setc(k-1,1);				// allocate space for message polynomial
}

GFNUM2m *
RSenc::encode(GFNUM2m *m_in)
// encode from Galios field elements
{
    //load message coefficients into member polynomial m
    for(int i = 0; i < k; ++i) {
        m[i] = m_in[i];
    }

    if ((n-k) == 0) {
        GFNUM2m *cw = new GFNUM2m[n];
        for(int i=0;i<k;i++) cw[i] = m[i];
        return cw;
    }
    else if ((n-k) < 0)
    {
      cout << "n must be greater than k..." << endl;
    }

    c = (m << (n-k)) + (m<<(n-k))%g;
    cout << "message = " << m << endl;
    cout << "code = " << c << endl;

    //return as array
    GFNUM2m *cw = new GFNUM2m[n];
    for (int i = 0; i < n; i++) {
        cw[i] = c[i];
    }
    return cw;
}

void
RSenc::encode(unsigned char *m_in, unsigned char *c_out)
// encode from chars
{
   if (!m_in || !c_out) return;

    // convert input bytes to field elements
    GFNUM2m *mfield = new GFNUM2m[k];
    for(int i = 0; i < k; ++i) {
        mfield[i] = GFNUM2m((int) m_in[i]);
    }

    // call GFNUM2m-based encoder
    GFNUM2m *cw_field = encode(mfield);

    // convert output field elements to bytes (assume cast to int is valid)
    for(int i = 0; i < n; ++i) {
        int val = (int) cw_field[i].getv();   // assumes GFNUM2m -> int
        c_out[i] = static_cast<unsigned char>(val & 0xFF);
    }

    delete[] mfield;
    delete[] cw_field;
}

/*
Local Variables:
compile-command: "g++ -c -g RSenc.cc"
End:
*/
	  
