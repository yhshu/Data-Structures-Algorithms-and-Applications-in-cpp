
// change the size of a 1D array

#include "xcept.h"

template<class T>
void ChangeSize1D(T * &a, int n, int ToSize)
{// Change the size of the one-dimensional
 // array a to ToSize.  n is the number
 // of elements in the array at present.

   // make sure new size is adequate
   if (n > ToSize) throw BadInput();

   // allocate a new array of desired size
   T *temp = new T [ToSize];

   // copy from old space to new space
   for (int i = 0; i < n; i++)
      temp[i] = a[i];

   // free old space
   delete [] a;

   // make a point to new space
   a = temp;
}
