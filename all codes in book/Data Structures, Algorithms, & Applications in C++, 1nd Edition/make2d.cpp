// test code to create a 2D array

#include <iostream.h>
#include "make2da.h"

void main(void)
{
   int **a;
   Make2DArray(a,2,2);
   a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
   cout << a[0][0] << ' ' << a[0][1] << endl;
   cout << a[0][0] << ' ' << a[1][1] << endl;
}
