
// test circular list Append

#include <iostream.h>
#include "jcircle.h"

void main(void)
{
   try {
      int x;
      HCircular<int> L;
      L.Insert(0,1).Insert(1,2).Insert(2,3).Delete(1,x).Delete(2,x);
      L.Append(2).Append(5).Append(7).Append(8);
      L.Append(3).Append(1).Append(6).Append(9);
      cout << "List is " << L << endl;
      }
   catch (...) {
      cerr << "An exception has occurred" << endl;
      }
}
