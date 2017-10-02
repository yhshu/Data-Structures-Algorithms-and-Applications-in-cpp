// test tridiagonal matrix class

#include <iostream.h>
#include "tridiag.h"

void main(void)
{
   TridiagonalMatrix<int> X(20);
   X.Store(22,1,1).Store(44,5,5).Store(0,8,5).Store(55,7,8);
   cout << X.Retrieve(7,8) << endl;
   cout << X.Retrieve(5,5) << endl;
   cout << X.Retrieve(1,1) << endl;
   cout << X.Retrieve(10,1) << endl;
   cout << X.Retrieve(1,5) << endl;
}
