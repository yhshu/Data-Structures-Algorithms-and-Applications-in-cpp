#include "xcept.h"

template<class T>
class Matrix {
public:
   Matrix(int r = 0, int c = 0);
   Matrix(const Matrix<T>& m); //copy constructor
   ~Matrix() {delete [] element;}
   T& operator()(int i, int j) const;
   Matrix<T>& operator=(const Matrix<T>& m);
   Matrix<T> operator+() const; //unary +
   Matrix<T> operator+(const Matrix<T>& m) const;
   Matrix<T> operator-() const; //unary minus
   Matrix<T> operator-(const Matrix<T>& m) const;
   Matrix<T> operator*(const Matrix<T>& m) const;
   Matrix<T>& operator+=(const T& x);
   void Output(ostream& out) const;
private:
    int rows, cols;
    T *element; //array
};  

template<class T>
Matrix<T>::Matrix(int r, int c)
{//create
if (rows < 0 || cols < 0) throw BadInitializers();
if ((!rows || !cols) && (rows || cols))
   throw BadInitializers();
cout << "Creating " << r << "  " << c << endl;
rows = r; cols = c;
element = new T [r * c];
}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& m)
{//copy constructor
rows = m.rows; cols = m.cols;
element = new T [rows * cols];
//copy each element
for (int i = 0; i < rows * cols; i++)
   element[i] = m.element[i];
}

template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m)
{//assignment
if (this != &m) {//do not copy to self
   delete [] element;
   rows = m.rows; cols = m.cols;
   element = new T [rows * cols];
   //copy each element
   for (int i = 0; i < rows * cols; i++)
      element[i] = m.element[i];
   }
return *this;
}

template<class T>
T& Matrix<T>::operator()(int i, int j) const
{//reference to element (i,j)
if (i < 1 || i > rows || j < 1
          || j > cols) throw OutOfBounds();
return element[(i - 1) * cols + j - 1];
}

template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& m) const
{
if (rows != m.rows || cols != m.cols)
   throw SizeMismatch();
Matrix<T> w(rows, cols);
for (int i = 0; i < rows * cols; i++)
    w.element[i] = element[i] + m.element[i];
return w;
}

template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& m) const
{
if (rows != m.rows || cols != m.cols)
   throw SizeMismatch();
Matrix<T> w(rows, cols);
for (int i = 0; i < rows * cols; i++)
    w.element[i] = element[i] - m.element[i];
return w;
}

template<class T>
Matrix<T> Matrix<T>::operator-() const
{//unary minus
Matrix<T> w(rows, cols);
for (int i = 0; i < rows * cols; i++)
    w.element[i] = -element[i];
return w;
}

template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& m) const
{
if (cols != m.rows) throw SizeMismatch();
Matrix<T> w(rows, m.cols);
//positions in this, m, and w
int tp = 0, mp = 0, wp = 0;
for (int i = 1; i <= rows; i++) {
   //compute row i of result
   for (int j = 1; j <= m.cols; j++) {
      //compute element (i,j)
      T sum =  element[tp] * m.element[mp];
      for (int k = 1; k <= cols; k++) {
         tp++; mp += m.cols;
         sum += element[tp] * m.element[mp];}
      //save element (i,j)
      w.element[wp++] = sum;
      //reset to start of row and next column
		tp -= cols - 1; mp = j - 1;}
   //reset to start of next row and first column
   tp++; mp = 0;}
return w;
}

template<class T>
Matrix<T>& Matrix<T>::operator+=(const T& x)
{
for (int i = 0; i < rows * cols; i++)
    element[i] += x;
return *this;
}

template<class T>
void Matrix<T>::Output(ostream& out) const
{// put the vector into the stream out
for (int i = 0; i < rows; i++) {
   for (int j = 0; j < cols; j++)
      out << element[i] << "  ";
   out << endl;}
}

//overload <<
template <class T>
ostream& operator<<(ostream& out, const Matrix<T>& x)
{x.Output(out); return out;}
