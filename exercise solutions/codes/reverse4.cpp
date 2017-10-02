// reverse the chain

#include <iostream.h>
#include "achain.h"

void main(void)
{
   int n = 15;
   Chain<int> C;
   for (int i = 0; i < n; i++)
      C.Insert(0,i);
   cout << "The chain is" << endl;
   cout << C << endl;

   C.Reverse();
   cout << "After reversal, the chain is" << endl;
   cout << C << endl;
}
