// code to test the function delete2dArray

#include <iostream>
#include "make2dArray.h"
#include "delete2dArray.h"

using namespace std;

int main()
{
   int **a;
   
   // create a 2 x 2 array
   make2dArray(a,2,2);

   // assign values
   a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;

   // output values
   cout << a[0][0] << ' ' << a[0][1] << endl;
   cout << a[0][0] << ' ' << a[1][1] << endl;

   // delete the array
   delete2dArray(a,2);

   return 0;
}
