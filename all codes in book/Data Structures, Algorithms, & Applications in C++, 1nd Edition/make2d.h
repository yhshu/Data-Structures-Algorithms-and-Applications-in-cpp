#ifndef Make2DArray_
#define Make2DArray_

#include <except.h>

template <class T>
bool Make2DArray(T ** &x, int rows, int cols)
{// Create a two dimensional array.

   try {
      // create pointers for the rows
      x = new T * [rows];
      
      // get memory for each row
      for (int i = 0; i < rows; i++)
          x[i] = new int [cols];
      return true;
      }
   catch (xalloc) {return false;}
}

#endif
