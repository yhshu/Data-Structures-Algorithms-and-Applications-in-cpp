// test the function make2dArrayNoCatch

#include <iostream>
#include "make2dArrayNoCatch.h"

using namespace std;

int main()
{
   int **a;
   // make a 2 x 2 array
   make2dArray(a,2,2);

   // assign values to all elements of the array
   a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;

   // output assigned values
   cout << a[0][0] << ' ' << a[0][1] << endl;
   cout << a[0][0] << ' ' << a[1][1] << endl;
   return 0;
}
