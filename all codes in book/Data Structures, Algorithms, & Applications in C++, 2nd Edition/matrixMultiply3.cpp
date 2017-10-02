// another code to multiply square matrices

#include <iostream>
#include "make2dArrayNoCatch.h"

using namespace std;

void fastSquareMatrixMultiply(int ** a, int ** b, int ** c, int n)
{
   for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
         c[i][j] = 0;

   for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
         for (int k = 0; k < n; k++)
            c[i][j] += a[i][k] * b[k][j];
}


int main()
{
   int **a, **b, **c;
   make2dArray(a,2,2);
   make2dArray(b,2,2);
   make2dArray(c,2,2);

   a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
   b[0][0] = 5; b[0][1] = 6; b[1][0] = 1; b[1][1] = 2;

   cout << "The first matrix is" << endl;
   cout << a[0][0] << ' ' << a[0][1] << endl;
   cout << a[1][0] << ' ' << a[1][1] << endl;

   cout << "The second matrix is" << endl;
   cout << b[0][0] << ' ' << b[0][1] << endl;
   cout << b[1][0] << ' ' << b[1][1] << endl;

   fastSquareMatrixMultiply(a,b,c,2);

   cout << "Their product is" << endl;
   cout << c[0][0] << ' ' << c[0][1] << endl;
   cout << c[1][0] << ' ' << c[1][1] << endl;

   return 0;
}
