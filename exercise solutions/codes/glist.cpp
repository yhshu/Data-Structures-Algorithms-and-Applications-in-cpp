
// test formula-based linear list class
// with array expansion and reduction

#include <iostream.h>
#include "glist.h"
#include "xcept.h"

void main(void)
{
   try {
      LinearList<int> L;
      L.Insert(0,6).Insert(0,5).Insert(0,4).Insert(0,3);
      L.Insert(0,2).Insert(0,1).Insert(0,0);
      cout << "List is " << L << endl;
      int z;
      for (int i = 1; i < 6; i++) {
         L.Delete(1,z);
         cout << "Deleted element is " << z << endl;}
      }
   catch (...) {
      cerr << "An exception has occurred" << endl;
      }
}
