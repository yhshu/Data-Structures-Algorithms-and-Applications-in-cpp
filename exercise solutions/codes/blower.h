

// lower triangle matrix extended to include +
// and copy constructor

#ifndef Lower_
#define Lower_


#include <stdlib.h>
#include <iostream.h>
#include "xcept.h"

template <class T> class UpperMatrix;

template<class T>
class LowerMatrix {
   friend UpperMatrix<T>;
   public:
      LowerMatrix(int size = 10)
         {n = size; t = new T [n*(n+1)/2];}
      ~LowerMatrix() {delete [] t;}
      LowerMatrix<T>& Store(const T& x, int i, int j);
      T Retrieve(int i, int j) const;
      LowerMatrix(const LowerMatrix<T>& x);
         // copy constructor
      LowerMatrix<T>& operator=(const LowerMatrix<T>& x);
      LowerMatrix<T> operator+(const LowerMatrix<T>& x) const;
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

template<class T>
LowerMatrix<T>::LowerMatrix(const LowerMatrix<T>& x)
{// Copy constructor for lower triangle matrices.
   n = x.n;
   t = new T[n*(n+1)/2];       // get space
   for (int i = 0; i < n*(n+1)/2; i++) // copy elements
      t[i] = x.t[i];
}

template<class T>
LowerMatrix<T>& LowerMatrix<T>::
     operator=(const LowerMatrix<T>& x)
{// Overload assignment operator.
   if (this != &x) {// not self-assignment
      n = x.n;
      delete [] t;           // free old space
      t = new T[n*(n+1)/2];  // get right amount
      for (int i = 0; i < n*(n+1)/2; i++)
         t[i] = x.t[i];
      }
   return *this;
}

template<class T>
LowerMatrix<T> LowerMatrix<T>::
           operator+(const LowerMatrix<T>& x) const
{// Return w = (*this) + x.
   if (n != x.n) throw SizeMismatch();

   // create result array w
   LowerMatrix<T> w(n);
   for (int i = 0; i < n*(n+1)/2; i++)
       w.t[i] = t[i] + x.t[i];

   return w;
}

#endif
