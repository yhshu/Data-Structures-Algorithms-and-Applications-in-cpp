// test lower triangular matrix class

#include <iostream.h>
#include "lower.h"

void main(void)
{
   LowerMatrix<int> X(20);
   X.Store(22,1,1).Store(44,5,3).Store(55,10,2).Store(0,8,5);
   cout << X.Retrieve(10,2) << endl;
   cout << X.Retrieve(5,3) << endl;
   cout << X.Retrieve(1,1) << endl;
   cout << X.Retrieve(10,14) << endl;
   cout << X.Retrieve(8,5) << endl;
}
