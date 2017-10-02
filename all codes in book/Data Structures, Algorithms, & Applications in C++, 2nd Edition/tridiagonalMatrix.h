// tridiagonal matrix

#ifndef tridiagonal_
#define tridiagonal_


#include "myExceptions.h"

using namespace std;

template<class T>
class tridiagonalMatrix 
{
   public:
      tridiagonalMatrix(int theN = 10);
      ~tridiagonalMatrix() {delete [] element;}
      T get(int, int) const;
      void set(int, int, const T&);
   private:
      int n;       // matrix dimension
      T *element;  // 1D array for tridiagonal
};

template<class T>
tridiagonalMatrix<T>::tridiagonalMatrix(int theN)
{// Constructor.
   // validate theN
   if (theN < 1)
       throw illegalParameterValue("Matrix size must be > 0");

   n = theN;
   element = new T [3 * n - 2];
}

template <class T>
T tridiagonalMatrix<T>::get(int i, int j) const
{// Return (i,j)th element of matrix.

   // validate i and j
   if ( i < 1 || j < 1 || i > n || j > n)
       throw matrixIndexOutOfBounds();
 
   // determine lement to return
   switch (i - j) 
   {
      case 1: // lower diagonal
              return element[i - 2];
      case 0: // main diagonal
              return element[n + i - 2];
      case -1: // upper diagonal
              return element[2 * n + i - 2];
      default: return 0;
   }
}

template<class T>
void tridiagonalMatrix<T>::set(int i, int j, const T& newValue)
{// Store newValue as (i,j)th element

   // validate i and j
   if ( i < 1 || j < 1 || i > n || j > n)
      throw matrixIndexOutOfBounds();

   switch (i - j) 
   {
      case 1: // lower diagonal
         element[i - 2] = newValue; break;
      case 0: // main diagonal
         element[n + i - 2] = newValue; break;
      case -1: // upper diagonal
         element[2 * n + i - 2] = newValue; break;
      default: if (newValue != 0)
                  throw illegalParameterValue
                        ("non-tridiagonal elements must be zero");
   }
}

#endif
