

#include <iostream.h>
#include "kchain.h"

void main(void)
{
   try {
      Chain<int> C;
      C.Insert(0,1).Insert(1,3).Insert(2,4).Insert(3,5);
      cout << "The chain " << C;
      if (C.Bitonic()) cout << " is bitonic" << endl;
      else cout << " is not bitonic" << endl;

      C.Insert(4,4).Insert(5,2).Insert(6,1);
      cout << "The chain " << C;
      if (C.Bitonic()) cout << " is bitonic" << endl;
      else cout << " is not bitonic" << endl;

      C.Insert(2,2);
      cout << "The chain " << C;
      if (C.Bitonic()) cout << " is bitonic" << endl;
      else cout << " is not bitonic" << endl;
      }
   catch (...) {
      cerr << "An exception has occurred" << endl;
      }
}
