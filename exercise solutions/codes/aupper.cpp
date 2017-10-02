
#include<iostream.h>
#include "blower.h"
#include "aupper.h"

void main(void)
{
const int n = 4;
LowerMatrix<int> X(4);
UpperMatrix<int> Y(4);

// initialize X
for (int i = 1; i <= n; i++)
   for (int j = 1; j <= i; j++)
      X.Store(i+j,i,j);

Y.Transpose(X);

// output Y
for (i = 1; i <= n; i++) {
   for (int j = 1; j <= n; j++)
      cout << Y.Retrieve(i,j) << ' ';
   cout << endl;
   }
}
