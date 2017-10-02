// test lower triangular matrix class

#include <iostream>
#include "lowerTriangularMatrix.h"

using namespace std;

int main(void)
{
   lowerTriangularMatrix<int> x(20);
   x.set(1,1,22);
   x.set(5,3,44);
   x.set(8,5,0);
   x.set(10,2,55);
   x.set(8,5,0);
   cout << x.get(10,2) << endl;
   cout << x.get(5,3) << endl;
   cout << x.get(1,1) << endl;
   cout << x.get(10,14) << endl;
   cout << x.get(8,5) << endl;

   return 0;
}
