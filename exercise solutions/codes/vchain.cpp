
#include <iostream.h>
#include "vchain.h"
#include "ilist.h"

void main(void)
{
   try {
      Chain<int> C;
      LinearList<int> L(10);
      L.Insert(0,2).Insert(1,6).Insert(2,7).Insert(3,8).Insert(4,9);
      cout << "List is " << L << endl;
      C.FromList(L);
      cout << "The chain is " << C << endl;
      int z;
      L.Delete(1,z).Delete(2,z);
      cout << "List is " << L << endl;
      C.ToList(L);
      cout << "List is " << L << endl;
      }
   catch (...) {
      cerr << "An exception has occurred" << endl;
      }
}
