


// test formula-based linear list class
// with zero fill

#include <iostream.h>
#include "klist.h"
#include "xcept.h"

void main(void)
{
   try {
      LinearList<int> L(15);
      L.Insert(0,9).Insert(0,8).Insert(0,7).Insert(0,6);
      L.Insert(0,5).Insert(0,4).Insert(0,3);
      cout << "List is " << L << endl;
      cout << "List with 5 zeroes inserted after element 2 is "
           << endl << L.InsertZero(2,5)
           << endl;
      }
   catch (...) {
      cerr << "An exception has occurred" << endl;
      }
}
