#ifndef Delete2DArray_
#define Delete2DArray_

template <class T>
void Delete2DArray(T ** &x, int rows)
{// Delete the two-dimensional array x.

   // delete the memory for each row
   for (int i = 0; i < rows; i++)
      delete [] x[i];
   
   // delete the row pointers
   delete [] x;
   x = 0;
}
#endif
