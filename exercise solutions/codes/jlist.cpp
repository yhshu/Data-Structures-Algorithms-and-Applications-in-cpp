

// test formula-based linear list class
// with right shift

#include <iostream.h>
#include "jlist.h"
#include "xcept.h"

void main(void)
{
   try {
      LinearList<int> L(15);
      L.Insert(0,9).Insert(0,8).Insert(0,7).Insert(0,6);
      L.Insert(0,5).Insert(0,4).Insert(0,3);
      cout << "List is " << L << endl;
      cout << "List shifted by 5 is "
           << L.RightShift(5)
           << endl;
      }
   catch (...) {
      cerr << "An exception has occurred" << endl;
      }
}
