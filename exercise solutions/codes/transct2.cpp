// in-place matrix transpose

#include <iostream.h>
#include "swap.h"
#include "make2db.h"

int count = 0;

template<class T>
void Transpose(T **a, int rows)
{// In-place transpose of matrix a
   for (int i = 0; i < rows; i++) {
      count++; //for above for
      for (int j = i+1;  j < rows; j++)
         count += 2;
      count++; // last time of for j
      }
   count++; // last time of for i
}

void main(void)
{
   int **a;
   Make2DArray(a,2,2);
   a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
   Transpose(a,2);
   cout << "Step count is " << count << endl;
}
