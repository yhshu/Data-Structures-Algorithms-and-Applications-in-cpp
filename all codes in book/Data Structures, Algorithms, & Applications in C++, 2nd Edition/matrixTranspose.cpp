// in-place matrix transpose

#include <iostream>
#include "make2dArrayNoCatch.h"

using namespace std;

template<class T>
void transpose(T **a, int rows)
{// In-place transpose of matrix a[0:rows-1][0:rows-1].
   for (int i = 0; i < rows; i++)
      for (int j = i+1;  j < rows; j++)
         swap(a[i][j], a[j][i]);
}

int main()
{
   int **a;
   make2dArray(a,2,2);
   a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;

   cout << "The matrix is" << endl;
   cout << a[0][0] << ' ' << a[0][1] << endl;
   cout << a[1][0] << ' ' << a[1][1] << endl;

   transpose(a,2);

   cout << "The transposed matrix is" << endl;
   cout << a[0][0] << ' ' << a[0][1] << endl;
   cout << a[1][0] << ' ' << a[1][1] << endl;
   return 0;
}
