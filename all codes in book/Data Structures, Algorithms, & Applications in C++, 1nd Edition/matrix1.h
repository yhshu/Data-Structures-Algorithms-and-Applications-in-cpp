#include "xcept.h"
#include "vector.h"

template<class T>
class Matrix {
public:
   Matrix(int r = 0, int c = 0);
   Matrix(const Matrix<T>& m); // copy constructor
   ~Matrix() {delete [] row;}
   T& operator[](int x) const;
   Matrix<T>& operator=(const Matrix<T>& m);
   Matrix<T> operator+() const; // unary +
   Matrix<T> operator+(const Matrix<T>& m) const;
   Matrix<T> operator-() const; // unary minus
   Matrix<T> operator-(const Matrix<T>& m) const;
   Matrix<T> operator*(const Matrix<T>& m) const;
   Matrix<T>& operator+=(const T& x);
   void Output(ostream& out) const;
private:
    int rows, cols;
    Vector<T> **row; // array of pointers
};  

template<class T>
Matrix<T>::Matrix(int r, int c)
{// Create.
   if (rows < 0 || cols < 0) throw BadInitializers();
   if ((!rows || !cols) && (rows || cols))
      throw BadInitializers();
   rows = r; cols = c;
   row = new Vector<T>* (c) [r];
}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& m)
{// Copy constructor.
   rows = m.rows; cols = m.cols;
   row = new Vector<T> (cols) [rows];
   // copy each row
   for (int i = 0; i < rows; i++)
      row[i] = m.row[i];
   }

template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m)
{// Assignment.
   if (this != &m) {// not self assignment
      delete [] row;
      rows = m.rows; cols = m.cols;
      row = new Vector<T> (cols) [rows];
      // copy each row
      for (int i = 0; i < rows; i++)
         row[i] = m.row[i];
      }
   return *this;
}

template<class T>
T& Matrix<T>::operator[](int x) const
{// First index of matrix.
   if (x < 1 || x > rows) throw OutOfBounds();
   return *row[x - 1];
}

template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& m) const
{// Add two matrices.
   if (rows != m.rows || cols != m.cols)
      throw SizeMismatch();
   Matrix<T> w(rows, cols);
   for (int i = 0; i < rows; i++)
       w.row[i] = row[i] + m.row[i];
   return w;
}

template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& m) const
{// Subtract two matrices.
   if (rows != m.rows || cols != m.cols)
      throw SizeMismatch();
   Matrix<T> w(rows, cols);
   for (int i = 0; i < rows; i++)
       w.row[i] = row[i] - m.row[i];
   return w;
}

template<class T>
Matrix<T> Matrix<T>::operator-() const
{// Unary minus.
   Matrix<T> w(rows, cols);
   for (int i = 0; i < rows; i++)
       w.row[i] = -row[i];
   return w;
}

template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& m) const
{// Multiply two matrices.
   if (cols != m.rows) throw SizeMismatch();
   Matrix<T> w(rows, m.cols);
   for (int i = 1; i <= rows; i++)
      for (int j = 1; j <= m.cols; j++) {
         T sum = (*this)[i][1] * m[1][j];
         for (int k = 1; k <= cols; k++)
            sum += (*this)[i][k] * m[k][j];
         w[i][j] = sum;
      }
   return w;
}

template<class T>
Matrix<T>& Matrix<T>::operator+=(const T& x)
{// Increment.
   for (int i = 0; i < rows; i++)
       row[i] += x;
   return *this;
}

template<class T>
void Matrix<T>::Output(ostream& out) const
{// Put the matrix into the stream out.
   for (int i = 0; i < rows; i++)
      out << row[i] << endl;
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const Matrix<T>& x)
   {x.Output(out); return out;}
