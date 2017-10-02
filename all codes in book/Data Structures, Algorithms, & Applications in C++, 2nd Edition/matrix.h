#ifndef matrix_
#define matrix_

#include "myExceptions.h"

using namespace std;
template<class T>
class matrix 
{
   friend ostream& operator<<(ostream&, const matrix<T>&);
   public:
      matrix(int theRows = 0, int theColumns = 0);
      matrix(const matrix<T>&);
      ~matrix() {delete [] element;}
      int rows() const {return theRows;}
      int columns() const {return theColumns;}
      T& operator()(int i, int j) const;
      matrix<T>& operator=(const matrix<T>&);
      matrix<T> operator+() const; // unary +
      matrix<T> operator+(const matrix<T>&) const;
      matrix<T> operator-() const; // unary minus
      matrix<T> operator-(const matrix<T>&) const;
      matrix<T> operator*(const matrix<T>&) const;
      matrix<T>& operator+=(const T&);
   private:
       int theRows,    // number of rows in matrix
           theColumns; // number of columns in matrix
       T *element;     // element array
};  

template<class T>
matrix<T>::matrix(int theRows, int theColumns)
{// matrix constructor.
   // validate theRows and theColumns
   if (theRows < 0 || theColumns < 0)
      throw illegalParameterValue("Rows and columns must be >= 0");
   if ((theRows == 0 || theColumns == 0)
                && (theRows != 0 || theColumns != 0))
      throw illegalParameterValue
      ("Either both or neither rows and columns should be zero");

   // create the matrix
   this->theRows = theRows;
   this->theColumns = theColumns;
   element = new T [theRows * theColumns];
}

template<class T>
matrix<T>::matrix(const matrix<T>& m)
{// Copy constructor for matrices.
   // create matrix
   theRows = m.theRows;
   theColumns = m.theColumns;
   element = new T [theRows * theColumns];

   // copy each element of m
   copy(m.element,
        m.element + theRows * theColumns,
        element);
}

template<class T>
matrix<T>& matrix<T>::operator=(const matrix<T>& m)
{// Assignment. (*this) = m.
   if (this != &m)
   {// not copying to self
      delete [] element;
      theRows = m.theRows;
      theColumns = m.theColumns;
      element = new T [theRows * theColumns];
      // copy each element
      copy(m.element,
           m.element + theRows * theColumns,
           element);
   }
   return *this;
}

template<class T>
T& matrix<T>::operator()(int i, int j) const
{// Return a reference to element (i,j).
   if (i < 1 || i > theRows
       || j < 1 || j > theColumns)
   throw matrixIndexOutOfBounds();
   return element[(i - 1) * theColumns + j - 1];
}

template<class T>
matrix<T> matrix<T>::operator+(const matrix<T>& m) const
{// Return w = (*this) + m.
   if (theRows != m.theRows
       || theColumns != m.theColumns)
      throw matrixSizeMismatch();

   // create result matrix w
   matrix<T> w(theRows, theColumns);
   for (int i = 0; i < theRows * theColumns; i++)
      w.element[i] = element[i] + m.element[i];

   return w;
}

template<class T>
matrix<T> matrix<T>::
          operator-(const matrix<T>& m) const
{// Return (*this) - m.
   if (theRows != m.theRows 
       || theColumns != m.theColumns)
      throw matrixSizeMismatch();

   // create result matrix w
   matrix<T> w(theRows, theColumns);
   for (int i = 0; i < theRows * theColumns; i++)
      w.element[i] = element[i] - m.element[i];

   return w;
}

template<class T>
matrix<T> matrix<T>::operator-() const
{// Return w = -(*this).

   // create result matrix w
   matrix<T> w(theRows, theColumns);
   for (int i = 0; i < theRows * theColumns; i++)
      w.element[i] = -element[i];
   return w;

}

template<class T>
matrix<T> matrix<T>::operator*(const matrix<T>& m) const
{// matrix multiply.  Return w = (*this) * m.
   if (theColumns != m.theRows) 
      throw matrixSizeMismatch();

   matrix<T> w(theRows, m.theColumns);  // result matrix

   // define cursors for *this, m, and w
   // and initialize to location of (1,1) element
   int ct = 0, cm = 0, cw = 0;

   // compute w(i,j) for all i and j
   for (int i = 1; i <= theRows; i++)
   {// compute row i of result
      for (int j = 1; j <= m.theColumns; j++)
      { // compute first term of w(i,j)
          T sum =  element[ct] * m.element[cm];

          // add in remaining terms
          for (int k = 2; k <= theColumns; k++)
          {
             ct++;  // next term in row i of *this
             cm += m.theColumns;  // next in column j of m
             sum += element[ct] * m.element[cm];
          }
          w.element[cw++] = sum;  // save w(i,j)
 
          // reset to start of row and next column
          ct -= theColumns - 1;
          cm = j;
      }

      // reset to start of next row and first column
      ct += theColumns;
      cm = 0;
   }

   return w;
}

template<class T>
matrix<T>& matrix<T>::operator+=(const T& x)
{// Increment all elements of *this by x.
   for (int i = 0; i < theRows * theColumns; i++)
       element[i] += x;
   return *this;
}

template<class T>
ostream& operator<<(ostream& out, const matrix<T>& m)
{// Put matrix m into the stream out.
 // One row per line.
   int k = 0;  // index into element array
   for (int i = 0; i < m.theRows; i++)
   {// do row i
      for (int j = 0; j < m.theColumns; j++)
         out << m.element[k++] << "  ";

      // row i finished
      out << endl;
   }

   return out;
}

// for some reason compiler can't create this on its own
ostream& operator<<(ostream& out, const matrix<int>& m)
{// Put matrix m into the stream out.
 // One row per line.
   int k = 0;  // index into element array
   for (int i = 0; i < m.theRows; i++)
   {// do row i
      for (int j = 0; j < m.theColumns; j++)
         out << m.element[k++] << "  ";

      // row i finished
      out << endl;
   }

   return out;
}

#endif
