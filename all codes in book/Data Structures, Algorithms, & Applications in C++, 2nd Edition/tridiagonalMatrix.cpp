// test tridiagonal matrix class

#include <iostream>
#include "tridiagonalMatrix.h"

using namespace std;
int main(void)
{
   tridiagonalMatrix<int> x(20);
   x.set(1,1,22);
   x.set(5,5,44);
   x.set(8,5,0);
   x.set(7,8,55);
   cout << x.get(7,8) << endl;
   cout << x.get(5,5) << endl;
   cout << x.get(1,1) << endl;
   cout << x.get(10,1) << endl;
   cout << x.get(1,5) << endl;

   return 0;
}
