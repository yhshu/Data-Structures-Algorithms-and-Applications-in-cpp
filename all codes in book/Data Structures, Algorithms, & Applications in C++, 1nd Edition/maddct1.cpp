// step count for matrix addition

#include <iostream.h>
#include "make2db.h"

int count = 0;

template<class T>
void Add( T **a, T **b, T **c, int rows, int cols)
{// Add matrices a and b to obtain matrix c.
   for (int i = 0; i < rows; i++) {
      count++; // preceding for loop
      for (int j = 0;  j < cols; j++) {
         count++; // preceding for loop
         c[i][j] = a[i][j] + b[i][j];
         count++; // assignment
         }
      count++; // last time of j for loop
      }
   count++; // last time of i for loop
}

void main(void)
{
   int **a, **b, **c;
   Make2DArray(a,2,2);
   Make2DArray(b,2,2);
   Make2DArray(c,2,2);
   a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
   b[0][0] = 1; b[0][1] = 2; b[1][0] = 3; b[1][1] = 4;
   Add(a,b,c,2,2);
   cout << c[0][0] << ' ' << c[0][1] << endl;
   cout << c[1][0] << ' ' << c[1][1] << endl;
   cout << count << endl;
}
