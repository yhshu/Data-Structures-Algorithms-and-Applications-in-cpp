
#include <iostream.h>
#include "resize1d.h"

void main()
{
   int *x;
   x = new int [3];
   for (int i = 0; i < 3; i++)
      x[i] = i;

   // increase array size to 8
   ChangeSize1D(x, 3, 8);

   for (i = 3; i < 8; i++)
      x[i] = i;

   // output
   for (i = 0; i < 8; i++)
      cout << x[i] << " ";
   cout << endl;
}
