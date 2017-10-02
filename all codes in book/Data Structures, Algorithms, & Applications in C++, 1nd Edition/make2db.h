#ifndef Make2DArray_
#define Make2DArray_

template <class T>
void Make2DArray(T ** &x, int rows, int cols)
{// Create a two-dimensional array.

   // create pointers for the rows
   x = new T * [rows];
      
   // get memory for each row
   for (int i = 0; i < rows; i++)
      x[i] = new T [cols];
}

#endif
