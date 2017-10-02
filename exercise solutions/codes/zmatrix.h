

// Z-matrix

#ifndef ZMatrix_
#define ZMatrix_

#include <stdlib.h>
#include <iostream.h>
#include "xcept.h"


template<class T>
class ZMatrix {
   public:
      ZMatrix(int size = 10)
         {n = size; t = new T [3*n-2];}
      ~ZMatrix() {delete [] t;}
      ZMatrix<T>& Store(const T& x, int i, int j);
      T Retrieve(int i, int j);
   private:
      int n;    // dimension
      T *t;     // 1D array
};

template<class T>
ZMatrix<T>& ZMatrix<T>::
     Store(const T& x, int i, int j)
{// Store x as N(i,j).
   if ( i < 1 || j < 1 || i > n || j > n)
       throw OutOfBounds();
   if (i == 1) t[j-1] = x;          // first row
   else if (i == n) t[n+j-1] = x;   // last row
        else if (i+j == n+1) t[2*n+i-2] = x;
                   // rest of cross diagonal
             else if (x != 0) throw MustBeZero();
   return *this;
}
  
template <class T>
T ZMatrix<T>::Retrieve(int i, int j)
{// Retrieve C(i,j)
   if ( i < 1 || j < 1 || i > n || j > n)
       throw OutOfBounds();
   if (i == 1) return t[j-1];   // first column
   if (i == n) return t[n+j-1]; // last column
   if (i+j == n+1) return t[2*n+i-2]; 
             // rest of cross diagonal
   return 0; // outside the Z
}

#endif
