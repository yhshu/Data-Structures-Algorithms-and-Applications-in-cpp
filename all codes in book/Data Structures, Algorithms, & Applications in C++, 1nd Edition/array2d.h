#ifndef Array2D_
#define Array2D_

#include "xcept.h"
#include "array1d.h"

template<class T>
class Array2D {
   friend ostream& operator<<
          (ostream&, const Array2D<T>&);
   public:
      Array2D(int r = 0, int c = 0);
      Array2D(const Array2D<T>& m); // copy constructor
      ~Array2D() {delete [] row;}
      int Rows() const {return rows;}
      int Columns() const {return cols;}
      Array1D<T>& operator[](int i) const;
      Array2D<T>& operator=(const Array2D<T>& m);
      Array2D<T> operator+() const; // unary +
      Array2D<T> operator+(const Array2D<T>& m) const;
      Array2D<T> operator-() const; // unary minus
      Array2D<T> operator-(const Array2D<T>& m) const;
      Array2D<T> operator*(const Array2D<T>& m) const;
      Array2D<T>& operator+=(const T& x);
   private:
       int rows, cols;  // array dimensions
       Array1D<T> *row; // array of 1D arrays
};  

template<class T>
Array2D<T>::Array2D(int r, int c)
{// Constructor for two-dimensional arrays.

   // validate r and c
   if (r < 0 || c < 0) throw BadInitializers();
   if ((!r || !c) && (r || c))
      throw BadInitializers();

   rows = r;
   cols = c;

   // allocate r 1D arrays of default size
   row = new Array1D<T> [r];

   // make them right size
   for (int i = 0; i < r; i++)
      row[i].ReSize(c);
}

template<class T>
Array2D<T>::Array2D(const Array2D<T>& m)
{// Copy constructor for two-dimensional arrays.
   rows = m.rows;
   cols = m.cols;

   // allocate array of 1D arrays
   row = new Array1D<T> [rows];

   // copy each row
   for (int i = 0; i < rows; i++)
      row[i] = m.row[i];
}

template<class T>
Array2D<T>& Array2D<T>::operator=(const Array2D<T>& m)
{// Assignment. (*this) = m.
   if (this != &m) {// not self assignment
      delete [] row;
      rows = m.rows; cols = m.cols;
      row = new Array1D<T> [rows];

      // copy each row
      for (int i = 0; i < rows; i++)
         row[i] = m.row[i];
      }

   return *this;
}

template<class T>
Array1D<T>& Array2D<T>::operator[](int i) const
{// First index of 2D array.
   if (i < 0 || i >= rows) throw OutOfBounds();
   return row[i];
}

template<class T>
Array2D<T> Array2D<T>::
           operator+(const Array2D<T>& m) const
{// Return w = (*this) + m.
   if (rows != m.rows || cols != m.cols)
      throw SizeMismatch();
 
   // create result array w
   Array2D<T> w(rows,cols);
   for (int i = 0; i < rows; i++)
       w.row[i] = row[i] + m.row[i];

   return w;
}

template<class T>
Array2D<T> Array2D<T>::
           operator-(const Array2D<T>& m) const
{// Return w = (*this) - m.
   if (rows != m.rows || cols != m.cols)
      throw SizeMismatch();

   // create result array w
   Array2D<T> w(rows,cols);
   for (int i = 0; i < rows; i++)
       w.row[i] = row[i] - m.row[i];

   return w;
}

template<class T>
Array2D<T> Array2D<T>::operator-() const
{// Return w = -(*this).

   // create result array w
   Array2D<T> w(rows, cols);
   for (int i = 0; i < rows; i++)
       w.row[i] = -row[i];

   return w;
}

template<class T>
Array2D<T> Array2D<T>::
           operator*(const Array2D<T>& m) const
{// A matrix product. Return w = (*this) * m.
   if (cols != m.rows) throw SizeMismatch();

   // create result array w
   Array2D<T> w(rows, m.cols);
   for (int i = 0; i < rows; i++)
      for (int j = 0; j < m.cols; j++) {
         T sum = (*this)[i][0] * m[0][j];
         for (int k = 1; k < cols; k++)
            sum += (*this)[i][k] * m[k][j];
         w[i][j] = sum;
      }

   return w;
}

template<class T>
Array2D<T>& Array2D<T>::operator+=(const T& x)
{// Increment each element of (*this) by x.
   for (int i = 0; i < rows; i++)
       row[i] += x;
   return *this;
}

template<class T>
ostream& operator<<(ostream& out,
                            const Array2D<T>& x)
{// Put the array elements into the stream out.
   for (int i = 0; i < x.rows; i++)
      out << x.row[i] << endl;
   return out;
}

#endif
