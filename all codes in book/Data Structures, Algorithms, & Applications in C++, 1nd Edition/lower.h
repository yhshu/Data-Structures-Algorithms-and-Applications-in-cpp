// file lower.h
#ifndef Lower_
#define Lower_

// lower triangle matrix

#include <stdlib.h>
#include <iostream.h>
#include "xcept.h"

template<class T>
class LowerMatrix {
   public:
      LowerMatrix(int size = 10)
         {n = size; t = new T [n*(n+1)/2];}
      ~LowerMatrix() {delete [] t;}
      LowerMatrix<T>& Store(const T& x, int i, int j);
      T Retrieve(int i, int j) const;
   private:
      int n; //  matrix dimension
      T *t;  // 1D array for lower triangle
};

template<class T>
LowerMatrix<T>& LowerMatrix<T>::
          Store(const T& x, int i, int j)
{// Store x as L(i,j).
   if ( i < 1 || j < 1 || i > n || j > n)
       throw OutOfBounds();


   // (i,j) in lower triangle iff i >= j
   if (i >= j) t[i*(i-1)/2+j-1] = x;
   else if (x != 0) throw MustBeZero();

   return *this;
}
   
template <class T>
T LowerMatrix<T>::Retrieve(int i, int j) const
{// Retrieve L(i,j).
   if ( i < 1 || j < 1 || i > n || j > n)
       throw OutOfBounds();

   // (i,j) in lower triangle iff i >= j
   if (i >= j) return t[i*(i-1)/2+j-1];
   else return 0;
}

#endif
