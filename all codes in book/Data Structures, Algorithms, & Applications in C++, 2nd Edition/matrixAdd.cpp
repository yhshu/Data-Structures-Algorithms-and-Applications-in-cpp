// matrix addition

#include <iostream>
#include "make2dArrayNoCatch.h"

using namespace std;

template<class T>
void matrixAdd( T **a, T **b, T **c, int numberOfRows,
                                     int numberOfColumns)
{// Add matrices a and b to obtain matrix c.
   for (int i = 0; i < numberOfRows; i++)
      for (int j = 0;  j < numberOfColumns; j++)
         c[i][j] = a[i][j] + b[i][j];
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

   matrixAdd(a,b,c,2,2);

   cout << "Their sum is" << endl;
   cout << c[0][0] << ' ' << c[0][1] << endl;
   cout << c[1][0] << ' ' << c[1][1] << endl;

   return 0;
}
