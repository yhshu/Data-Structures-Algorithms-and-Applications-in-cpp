// create a 2D array; catch exception thrown by new when
// sufficient memory is not available
// return true iff successful in creating the 2d array

#ifndef make2dArray_
#define make2dArray_

#include <exception>

using namespace std;

template <class T>
bool make2dArray(T ** &x, int numberOfRows, int numberOfColumns)
{// Create a two dimensional array.

   try {
          // create pointers for the rows
          x = new T * [numberOfRows];
          
          // get memory for each row
          for (int i = 0; i < numberOfRows; i++)
              x[i] = new int [numberOfColumns];
          return true;
       }
   catch (bad_alloc) {return false;}
}

#endif
