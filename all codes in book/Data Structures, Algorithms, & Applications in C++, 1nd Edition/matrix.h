#ifndef Matrix_
#define Matrix_

#include "xcept.h"

template<class T>
class Matrix {
   friend ostream& operator<<
          (ostream&, const Matrix<T>&);
   public:
      Matrix(int r = 0, int c = 0);
      Matrix(const Matrix<T>& m); // copy constructor
      ~Matrix() {delete [] element;}
      int Rows() const {return rows;}
      int Columns() const {return cols;}
      T& operator()(int i, int j) const;
      Matrix<T>& operator=(const Matrix<T>& m);
      Matrix<T> operator+() const; // unary +
      Matrix<T> operator+(const Matrix<T>& m) const;
      Matrix<T> operator-() const; // unary minus
      Matrix<T> operator-(const Matrix<T>& m) const;
      Matrix<T> operator*(const Matrix<T>& m) const;
      Matrix<T>& operator+=(const T& x);
   private:
       int rows, cols; // matrix dimensions
       T *element;     // element array
};  

template<class T>
Matrix<T>::Matrix(int r, int c)
{// Matrix constructor.
   // validate r and c
   if (r < 0 || c < 0) throw BadInitializers();
   if ((!r || !c) && (r || c))
   	throw BadInitializers();

   // create the matrix
   rows = r; cols = c;
   element = new T [r * c];
}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& m)
{// Copy constructor for matrices.
   // create matrix
   rows = m.rows; cols = m.cols;
   element = new T [rows * cols];

   // copy each element of m
   for (int i = 0; i < rows * cols; i++)
      element[i] = m.element[i];
}

template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m)
{// Assignment. (*this) = m.
   if (this != &m) {// do not copy to self
            delete [] element;
            rows = m.rows; cols = m.cols;
            element = new T [rows * cols];
            // copy each element
            for (int i = 0; i < rows * cols; i++)
               element[i] = m.element[i];
               }
   return *this;
}

template<class T>
T& Matrix<T>::operator()(int i, int j) const
{// Return a reference to element (i,j).
   if (i < 1 || i > rows || j < 1
             || j > cols) throw OutOfBounds();
   return element[(i - 1) * cols + j - 1];
}

template<class T>
Matrix<T> Matrix<T>::
          operator+(const Matrix<T>& m) const
{// Return w = (*this) + m.
   if (rows != m.rows || cols != m.cols)
      throw SizeMismatch();

   // create result matrix w
   Matrix<T> w(rows, cols);
   for (int i = 0; i < rows * cols; i++)
      w.element[i] = element[i] + m.element[i];

   return w;
}

template<class T>
Matrix<T> Matrix<T>::
          operator-(const Matrix<T>& m) const
{// Return (*this) - m.
   if (rows != m.rows || cols != m.cols)
      throw SizeMismatch();

   // create result matrix w
   Matrix<T> w(rows, cols);
   for (int i = 0; i < rows * cols; i++)
      w.element[i] = element[i] - m.element[i];

   return w;
}

template<class T>
Matrix<T> Matrix<T>::operator-() const
{// Return w = -(*this).

   // create result matrix w
   Matrix<T> w(rows, cols);
   for (int i = 0; i < rows * cols; i++)
      w.element[i] = -element[i];
   return w;

}

template<class T>
Matrix<T> Matrix<T>::
          operator*(const Matrix<T>& m) const
{// Matrix multiply.  Return w = (*this) * m.
   if (cols != m.rows) throw SizeMismatch();

   Matrix<T> w(rows, m.cols);  // result matrix

   // define cursors for *this, m, and w
   // and initialize to location of (1,1)
   int ct = 0, cm = 0, cw = 0;

   // compute w(i,j) for all i and j
   for (int i = 1; i <= rows; i++) {

      // compute row i of result
      for (int j = 1; j <= m.cols; j++) {

         // compute first term of w(i,j)
         T sum =  element[ct] * m.element[cm];

         // add in remaining terms
         for (int k = 2; k <= cols; k++) {
            ct++;  // next term in row i of *this
            cm += m.cols;  // next in column j of m
            sum += element[ct] * m.element[cm];
            }
         w.element[cw++] = sum;  // save w(i,j)

         // reset to start of row and next column
         ct -= cols - 1;
         cm = j;
         }

      // reset to start of next row and first column
      ct += cols;
      cm = 0;
      }

   return w;
}

template<class T>
Matrix<T>& Matrix<T>::operator+=(const T& x)
{// Increment all elements of *this by x.
   for (int i = 0; i < rows * cols; i++)
       element[i] += x;
   return *this;
}

template<class T>
ostream& operator<<(ostream& out,
                    const Matrix<T>& x)
{// Put matrix x into the stream out.
 // One row per line.
   int k = 0;  // index into element array
   for (int i = 0; i < x.rows; i++) {

      // do row i
      for (int j = 0; j < x.cols; j++)
         out << x.element[k++] << "  ";

      // row i finished
      out << endl;}

   return out;
}

#endif
