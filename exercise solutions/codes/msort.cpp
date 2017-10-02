

#include <iostream.h>
#include "fchain.h"

void main()
{
   int i, n = 10;
   Chain<int> X;
   for (i = 1; i <= n; i++) {
      X.Insert(0,10+i);
      X.Insert(0,10-i);}
   cout << "Input chain is " << X << endl;
   X.MergeSort();
   cout << "Sorted chain is " << X << endl;
}
