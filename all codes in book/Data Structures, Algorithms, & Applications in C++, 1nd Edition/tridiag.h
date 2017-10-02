
// file tridiag.h

#ifndef Tridiagonal_
#define Tridiagonal_

// tridiagonal matrix

#include <stdlib.h>
#include <iostream.h>
#include "xcept.h"


template<class T>
class TridiagonalMatrix {
public:
   TridiagonalMatrix(int size = 10)
      {n = size; t = new T [3*n-2];}
   ~TridiagonalMatrix() {delete [] t;}
   TridiagonalMatrix<T>& Store
           (const T& x, int i, int j);
   T Retrieve(int i, int j) const;
   private:
      int n; // matrix dimension
      T *t;  // 1D array for tridiagonal
};

template<class T>
TridiagonalMatrix<T>& TridiagonalMatrix<T>::
                Store(const T& x, int i, int j)
{// Store x as T(i,j)
if ( i < 1 || j < 1 || i > n || j > n)
    throw OutOfBounds();

switch (i - j) {
   case 1: // lower diagonal
      t[i - 2] = x; break;
   case 0: // main diagonal
      t[n + i - 2] = x; break;
   case -1: // upper diagonal
      t[2 * n + i - 2] = x; break;
   default: if(x != 0) throw MustBeZero();
   }
return *this;
}

template <class T>
T TridiagonalMatrix<T>::Retrieve(int i, int j) const
{// Retrieve T(i,j)
if ( i < 1 || j < 1 || i > n || j > n)
    throw OutOfBounds();
 
switch (i - j) {
   case 1: // lower diagonal
           return t[i - 2];
   case 0: // main diagonal
           return t[n + i - 2];
   case -1: // upper diagonal
           return t[2 * n + i - 2];
   default: return 0;
   }
}

#endif
