// file diag.h
#ifndef DiagonalMatrix_
#define DiagonalMatrix_

// diagonal matrix

#include <stdlib.h>
#include <iostream.h>
#include "xcept.h"


template<class T>
class DiagonalMatrix {
   public:
      DiagonalMatrix(int size = 10)
         {n = size; d = new T [n];}
      ~DiagonalMatrix() {delete [] d;} // destructor
      DiagonalMatrix<T>&
         Store(const T& x, int i, int j);
      T Retrieve(int i, int j) const;
   private:
      int n; // matrix dimension
      T *d;  // 1D array for diagonal elements
};

template<class T>
DiagonalMatrix<T>& DiagonalMatrix<T>::
             Store(const T& x, int i, int j)
{// Store x as D(i,j).
   if (i < 1 || j < 1 || i > n || j > n)
       throw OutOfBounds();
   if (i != j && x != 0) throw MustBeZero();
   if (i == j) d[i-1] = x;
   return *this;
}
  
template <class T>
T DiagonalMatrix<T>::Retrieve(int i, int j) const
{// Retrieve D(i,j).
   if (i < 1 || j < 1 || i > n || j > n)
       throw OutOfBounds();
   if (i == j) return d[i-1];
   else return 0;
}

#endif
