//  Program: testgfnum.cc
//  test basic operations on GFNUM2m class

// Copyright 2004 by Todd K. Moon
// Permission is granted to use this program/data
// for educational/research only

#include "GFNUM2m.h"

int main()
{
   int g = 0x11D;  // 1 0001 1101 = 1+x^2+x^3+x^4+x^8
   GFNUM2m::initgf(8,g);
   GFNUM2m a,b,c;
   GF2 a2,b2,c2;
   // GFNUM2m::setouttype(vector);
   a = A^203;
   cout << "a = " << a << endl;
   b = A^18;
   cout << "b = " << b << endl;
   cout << "a+b=" << a+b << endl;
   cout << "a+=b=" << (a+= b) << endl;
   a = A^67;
   cout << "a = " << a << endl;
   cout << "a+A^2=" << a+4 << endl;
   cout << "a+A^2=" << 4+a << endl;
   cout << "a=" << a << "  b=" << b << endl;
   cout << "a*b=" << a*b << endl;
   cout << "a*=b=" << (a*=b) << endl;
   a = A^84;
   cout << "a = " << a << endl;
   cout << "a*4=" << (a*4) << endl;
   cout << "a*4=" << (4*a) << endl;
   cout << "a*=4=" << (a*=4) << endl;
   a = A^3;
   cout << "a = " << a << endl;
   cout << "a*A^5=" << a*(A^5) << endl;
   cout << "a^4=" << (a^4) << endl;
   cout << "a^{-4}=" << (a^(-4)) << endl;
   cout << "a^=4=" << (a^=4) << endl;
   a = A^22;
   cout << "a = " << a << endl;
   cout << "a^=(-4)=" << (a^=(-4)) << endl;
   a = A^92;
   cout << "a = " << a << endl;
   cout << "a/b=" << a/b << endl;
   cout << "a/=b=" << (a/=b) << endl;
   a = A^3;
   cout << "a = " << a << endl;
   cout << "a/6=" << a/6 << endl;
   cout << "a/=6=" << (a/=6) << endl;
   a = A^3;
   cout << "1/a=" <<  (1/a) << endl;
   a = A^3;
   cout << "a==b" << (a==b) << endl;
   if (a == b)
   {
      cout << "error on ==" << endl;
   }
   else
   {
      cout << "== is correctly evaulated" << endl;
   }
   cout << "a!=b" << (a!=b) << endl;
   if (a != b)
   {
      cout << "!= is correctly evaulated" << endl;
   }
   else
   {
      cout << "error with !=" << endl;
   }
   cout << "-a=" << -a << endl;
   a2 = 1;
   b = a+a2;
   cout << "a=" << a << "  b=" << b << endl;
   cout << "a-b=" << (a-b) << endl;
   cout << "a-=b=" << (a-=b) << endl;
}

/*
Local Variables:
compile-command: "g++ -g -o testgfnum testgfnum.cc GFNUM2m.cc"
End:
*/


