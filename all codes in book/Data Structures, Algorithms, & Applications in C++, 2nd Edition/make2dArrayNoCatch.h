// create a 2D array but do not catch exception thrown
// when new fails to allocate sufficient memory

#ifndef make2dArrayNoCatch_
#define make2dArrayNoCatch_

using namespace std;

template <class T>
void make2dArray(T ** &x, int numberOfRows, int numberOfColumns)
{// Create a two-dimensional array.

   // create pointers for the rows
   x = new T * [numberOfRows];
      
   // get memory for each row
   for (int i = 0; i < numberOfRows; i++)
      x[i] = new T [numberOfColumns];
}

#endif
