

// N-matrix

#ifndef NMatrix_
#define NMatrix_

#include<stdlib.h>
#include<iostream.h>
#include "xcept.h"


template<class T>
class NMatrix {
   public:
      NMatrix(int size = 10)
         {n = size; t = new T [3*n-2];}
      ~NMatrix() {delete [] t;}
      NMatrix<T>& Store(const T& x, int i, int j);
      T Retrieve(int i, int j);
   private:
      int n;    // dimension
      T *t;     // 1D array
};

template<class T>
NMatrix<T>& NMatrix<T>::
     Store(const T& x, int i, int j)
{// Store x as N(i,j).
   if ( i < 1 || j < 1 || i > n || j > n)
       throw OutOfBounds();
   if (j == 1) t[i-1] = x;          // first column
   else if (j == n) t[n+i-1] = x;   // last column
        else if (i == j) t[2*n+i-2] = x;
                         // rest of diagonal
             else if (x != 0) throw MustBeZero();
   return *this;
}
  
template <class T>
T NMatrix<T>::Retrieve(int i, int j)
{// Retrieve C(i,j)
   if ( i < 1 || j < 1 || i > n || j > n)
       throw OutOfBounds();
   if (j == 1) return t[i-1];   // first column
   if (j == n) return t[n+i-1]; // last column
   if (i == j) return t[2*n+i-2]; 
                  // rest of diagonal
   return 0; // outside the N
}

#endif
