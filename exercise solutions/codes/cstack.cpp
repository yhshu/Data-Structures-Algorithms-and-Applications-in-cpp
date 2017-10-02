

// test formula-based stack class
// with array expansion and reduction

#include <iostream.h>
#include "cstack.h"

void main(void)
{
   try {
      Stack<int> S;
      S.Add(6).Add(5).Add(4).Add(3);
      S.Add(2).Add(1).Add(0);
      cout << "Stack is " << endl
           << S << endl;
      int z;
      for (int i = 1; i < 6; i++) {
         S.Delete(z);
         cout << "Deleted element is " << z << endl;}
      }
   catch (...) {
      cerr << "An exception has occurred" << endl;
      }
}
