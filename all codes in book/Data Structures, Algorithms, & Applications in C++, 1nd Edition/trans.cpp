// in-place matrix transpose

#include <iostream.h>
#include "swap.h"
#include "make2db.h"

template<class T>
void Transpose(T **a, int rows)
{// In-place transpose of matrix a[0:rows-1][0:rows-1].
   for (int i = 0; i < rows; i++)
      for (int j = i+1;  j < rows; j++)
         Swap(a[i][j], a[j][i]);
}

void main(void)
{
   int **a;
   Make2DArray(a,2,2);
   a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
   Transpose(a,2);
   cout << a[0][0] << ' ' << a[0][1] << endl;
   cout << a[1][0] << ' ' << a[1][1] << endl;
}
