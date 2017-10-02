// test matrix transpose

#include <iostream>
#include "matrixWithTranspose.h"

using namespace std;
int main(void)
{
   matrix<int> x(3,2), y, z;
   for (int i = 1; i <= 3; i++)
      for (int j = 1; j <= 2; j++)
         x(i,j) = 2*i + j;
   cout << "Initialized x(i,j) = 2*i + j" << endl;
   cout << "x is" << endl;;
   cout << x << endl;

    x.transpose(y);
   cout << "Assigned y = x.transpose" << endl;
   cout << "y is" << endl;
   cout << y << endl;

   return 0;
}
