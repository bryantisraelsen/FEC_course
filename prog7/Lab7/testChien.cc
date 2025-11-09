//  Program: testChienSearch.cc
//  Todd K. Moon

#include "ChienSearch.h"



int main()
{
   GFNUM2m::initgf(4,0x13);  // 1 011 = 1+x+x^4
   ChienSearch Searcher(3);
   GFNUM2m Lambda[] = {1,1,0,A^5}; // 1+x + A^5 x^3
   int nroots;
   GFNUM2m *p = Searcher.Search(Lambda,3,nroots);
   //for(int i = 0; i < Searcher.getnroots(); i++) {
   for(int i = 0; i < nroots; i++) {
	  cout << p[i] << " ";
   }
   cout << endl;
}
   

/*
Local Variables:
compile-command: "g++ -o testChien -g testChien.cc ChienSearch.cc GFNUM2m.cc"
End:
*/


