
#include <iostream.h>
#include "ichain.h"

void main(void)
{
   try {
      Chain<int> C;
      C.Insert(0,1).Insert(1,3).Insert(2,4).Insert(3,5);
      cout << "The chain " << C;
      if (C.IsSorted()) cout << " is sorted" << endl;
      else cout << " is not sorted" << endl;

      C.Insert(2,2);
      cout << "The chain " << C;
      if (C.IsSorted()) cout << " is sorted" << endl;
      else cout << " is not sorted" << endl;
      }
   catch (...) {
      cerr << "An exception has occurred" << endl;
      }
}
