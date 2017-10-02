// test diagonal matrix class

#include <iostream.h>
#include "diag.h"

void main(void)
{
   DiagonalMatrix<int> X(20);
   X.Store(22,1,1).Store(44,5,5).Store(0,8,5);
   cout << X.Retrieve(5,5) << endl;
   cout << X.Retrieve(1,1) << endl;
   cout << X.Retrieve(10,1) << endl;
}
