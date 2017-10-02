
#ifndef Array1D_
#define Array1D_

// One-dimensional arrays.

#include <iostream.h>
#include "xcept.h"

template<class T>
class Array1D {
   friend ostream& operator<<
          (ostream&, const Array1D<T>&);
   public:
      Array1D(int size = 0);
      Array1D(const Array1D<T>& v); // copy constructor
      ~Array1D() {delete [] element;}
      T& operator[](int i) const;
      int Size() {return size;}
      Array1D<T>& operator=(const Array1D<T>& v);
      Array1D<T> operator+() const; // unary +
      Array1D<T> operator+(const Array1D<T>& v) const;
      Array1D<T> operator-() const; // unary minus
      Array1D<T> operator-(const Array1D<T>& v) const;
      Array1D<T> operator*(const Array1D<T>& v) const;
      Array1D<T>& operator+=(const T& x);
      Array1D<T>& ReSize(int sz);
   private:
       int size;
       T *element; // 1D array
};  

template<class T>
Array1D<T>::Array1D(int sz)
{// Constructor for one-dimensional arrays.
   if (sz < 0) throw BadInitializers();
   size = sz;
   element = new T[sz];
}

template<class T>
Array1D<T>::Array1D(const Array1D<T>& v)
{// Copy constructor for one-dimensional arrays.
   size = v.size;
   element = new T[size];  // get space
   for (int i = 0; i < size; i++) // copy elements
      element[i] = v.element[i];
}

template<class T>
T& Array1D<T>::operator[](int i) const
{// Return reference to element i.
   if (i < 0 || i >= size) throw OutOfBounds();
   return element[i];
}

template<class T>
Array1D<T>& Array1D<T>::operator=(const Array1D<T>& v)
{// Overload assignment operator.
   if (this != &v) {// not self-assignment
      size = v.size;
      delete [] element; // free old space
      element = new T[size]; // get right amount
      for (int i = 0; i < size; i++) // copy elements
         element[i] = v.element[i];
      }
   return *this;
}

template<class T>
Array1D<T> Array1D<T>::
           operator+(const Array1D<T>& v) const
{// Return w = (*this) + v.
   if (size != v.size) throw SizeMismatch();

   // create result array w
   Array1D<T> w(size);
   for (int i = 0; i < size; i++)
       w.element[i] = element[i] + v.element[i];

   return w;
}

template<class T>
Array1D<T> Array1D<T>::
           operator-(const Array1D<T>& v) const
{// Return w = (*this) - v.
   if (size != v.size) throw SizeMismatch();

   // create result array w
   Array1D<T> w(size);
   for (int i = 0; i < size; i++)
       w.element[i] = element[i] - v.element[i];

   return w;
}

template<class T>
Array1D<T> Array1D<T>::operator-() const
{// Return w = -(*this).
   // create result array w
   Array1D<T> w(size);
   for (int i = 0; i < size; i++)
       w.element[i] = -element[i];

   return w;
}

template<class T>
Array1D<T> Array1D<T>::operator*(const Array1D<T>& v) const
{// Return w = (*this) * v. Pairwise multiply.
   if (size != v.size) throw SizeMismatch();

   // create result array w
   Array1D<T> w(size);
   for (int i = 0; i < size; i++)
       w.element[i] = element[i] * v.element[i];

   return w;
}

template<class T>
Array1D<T>& Array1D<T>::operator+=(const T& x)
{// Add x to each element of (*this).
   for (int i = 0; i < size; i++)
       element[i] += x;
   return *this;
   }

template<class T>
ostream& operator<<(ostream& out,
                    const Array1D<T>& x)
{// Put the elements of x into the stream out.
   for (int i = 0; i < x.size; i++)
      out << x.element[i] << "  ";
   return out;
}

template<class T>
Array1D<T>& Array1D<T>::ReSize(int sz)
{// Change the size to sz.
 // Do not copy array elements to new space.
   if (sz < 0) throw BadInitializers();
   delete [] element;
   size = sz;
   element = new T [size];
   return *this;
}

#endif
