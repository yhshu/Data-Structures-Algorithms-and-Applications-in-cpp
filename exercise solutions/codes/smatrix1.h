
// array representation of a sparse matrix
// input operator check for valid input

#ifndef SparseMatrix_
#define SparseMatrix_

#include <stdlib.h>
#include <iostream.h>
#include "term.h"
#include "xcept.h"

template<class T>
class SparseMatrix
{
   friend ostream& operator<<
          (ostream&, const SparseMatrix<T>&);
   friend istream& operator>>
          (istream&, SparseMatrix<T>&);
   public:
      SparseMatrix(int maxTerms = 10);
      ~SparseMatrix() {delete [] a;}
      void Transpose(SparseMatrix<T> &b) const;
      void Add(const SparseMatrix<T> &b,
              SparseMatrix<T> &c) const;
   private:
      void Append(const Term<T>& t);
      int rows, cols;  // matrix dimensions
      int terms;  // current number of nonzero terms
      Term<T> *a;   // term array
      int MaxTerms; // size of array a;
};

template<class T>
SparseMatrix<T>::SparseMatrix(int maxTerms)
{// Sparse matrix constructor.
   if (maxTerms < 1) throw BadInitializers();
   MaxTerms = maxTerms;
   a = new Term<T> [MaxTerms];
   terms = rows = cols = 0;
}

// overload <<
template <class T>
ostream& operator<<(ostream& out,
                    const SparseMatrix<T>& x)
{// Put *this in output stream.

   // put matrix characteristics
   out << "rows = " << x.rows << " columns = "
       << x.cols  << endl;
   out << "nonzero terms = " << x.terms << endl;

   // put terms, one per line
   for (int i = 0; i < x.terms; i++)
      out << "a(" << x.a[i].row << ',' << x.a[i].col
          << ") = " << x.a[i].value << endl;

   return out;
}

// overload >>
template<class T>
istream& operator>>(istream& in, SparseMatrix<T>& x)
{// Input a sparse matrix.

   // input matrix characteristics
   cout << "Enter number of rows, columns, and terms"
        << endl;
   in >> x.rows >> x.cols >> x.terms;
   if (x.terms > x.MaxTerms) throw NoMem();

   // OldIndex = (row of last term) * x.cols +
   //         column of last term
   int OldIndex = 0;

   // input terms
   for (int i = 0; i < x.terms; i++) {
      cout << "Enter row, column, and value of term " 
           << (i + 1) << endl;
      in >> x.a[i].row >> x.a[i].col >> x.a[i].value;
      // verify input
      int NewIndex = x.a[i].row * x.cols + x.a[i].col;
      if ((NewIndex <= OldIndex) || (x.a[i].value == 0))
         throw BadInput();
      OldIndex = NewIndex;
      }

   return in;
}

template<class T>
void SparseMatrix<T>::
     Transpose(SparseMatrix<T> &b) const
{// Return transpose of *this in b.

   // make sure b has enough space
   if (terms > b.MaxTerms) throw NoMem();

   // set transpose characteristics
   b.cols = rows;
   b.rows = cols;
   b.terms = terms;

   // initialize to compute transpose
   int *ColSize, *RowNext;
   ColSize = new int[cols + 1];
   RowNext = new int[rows + 1];
   
   // find number of entries in each column of *this
   for (int i = 1; i <= cols; i++) // initialize
      ColSize[i] = 0;  
   for (i = 0; i < terms; i++)
      ColSize[a[i].col]++;  
   
   // find the starting point of each row of b
   RowNext[1] = 0;
   for (i = 2; i <= cols; i++)
      RowNext[i] = RowNext[i - 1] + ColSize[i - 1];  
   
   // perform the transpose copying from *this to b
   for (i = 0; i < terms; i++) {
      int j = RowNext[a[i].col]++; // position in b
      b.a[j].row = a[i].col;
      b.a[j].col = a[i].row;
      b.a[j].value = a[i].value;
      }
}

template<class T>
void SparseMatrix<T>::Append(const Term<T>& t)
{// Append a nonzero term t to *this.
   if (terms >= MaxTerms) throw NoMem();
   a[terms] = t;
   terms++;
}

template<class T>
void SparseMatrix<T>::Add(const SparseMatrix<T> &b,
                            SparseMatrix<T> &c) const
{// Compute c = (*this) + b.

   // verify compatibility
   if (rows != b.rows || cols != b.cols)
     throw SizeMismatch(); // incompatible matrices

   // set characteristics of result c
   c.rows = rows;
   c.cols = cols;
   c.terms = 0; // initial value

   // define cursors to move through *this and b
   int ct = 0, cb = 0;

   // move through *this and b adding like terms
   while (ct < terms && cb < b.terms) {

     // Row-major index plus cols of each term
     int indt = a[ct].row * cols + a[ct].col;
     int indb = b.a[cb].row * cols + b.a[cb].col;

     if (indt < indb) {// b term comes later
   	 c.Append(a[ct]);
         ct++;} // next term of *this
     else {if (indt == indb) {// both in same position

              // append to c only if sum not zero
              if (a[ct].value + b.a[cb].value) {
                 Term<T> t;
                 t.row = a[ct].row;
                 t.col = a[ct].col;
                 t.value = a[ct].value + b.a[cb].value;
                 c.Append(t);}

              ct++; cb++;}  // next terms of *this and b
           else {c.Append(b.a[cb]);
                 cb++;} // next term of b
          }
     }

   // copy over remaining terms
   for (; ct < terms; ct++)
      c.Append(a[ct]);
   for (; cb < b.terms; cb++)
      c.Append(b.a[cb]);
}

#endif
