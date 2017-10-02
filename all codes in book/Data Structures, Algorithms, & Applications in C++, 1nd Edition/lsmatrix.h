// header file lsmatrix.h
// linked representation of a sparse matrix

#ifndef LinkedMatrix_
#define LinkedMatrix_

#include <stdlib.h>
#include <iostream.h>
#include "echain.h"
#include "citer.h"
#include "matnodes.h"
#include "xcept.h"

template<class T>
class LinkedMatrix {
   friend ostream& operator<<
          (ostream&, const LinkedMatrix<T>&);
   friend istream& operator>>
          (istream&, LinkedMatrix<T>&);
   public:
      LinkedMatrix(){}
      ~LinkedMatrix(){}
      void Transpose(LinkedMatrix<T> &b) const;
   private:
      int rows, cols;        // matrix dimensions
      Chain<HeadNode<T> > a; // head node chain
};

template<class T>
istream& operator>>(istream& in, LinkedMatrix<T>& x)
{// Input matrix x from the stream in.
   x.a.Erase(); // delete all nodes from x

   // get matrix characteristics
   int terms;   // number of terms to be input
   cout << "Enter number of rows, columns, and terms" 
        << endl;
   in >> x.rows >> x.cols >> terms;

   // create fictional row zero
   HeadNode<T> H;  // head node for current row
   H.row = 0;      // current row number

   // get terms of matrix x
   for (int i = 1; i <= terms; i++) {
      // get next term
      cout << "Enter row, column, and value of term " 
           << i << endl;
      int row, col;
      T value;
      in >> row >> col >> value;

      // check if new term is part of current row
      if (row > H.row) {// start a new row
         // append head node H of current row to
         // head node chain x.a only if row not zero
         if (H.row) x.a.Append(H);

         // prepare H for new row
         H.row = row;
         H.a.Zero();}  // save from chain destructor

      // add new term to row chain
      CNode<T> *c = new CNode<T>;
      c->col = col;
      c->value = value;
      H.a.Append(*c);
      }

   // take care of last row of matrix
   if (H.row) x.a.Append(H);
   H.a.Zero(); // save from chain destructor

   return in;
}

template<class T>
ostream& operator<<(ostream& out,
                    const LinkedMatrix<T>& x)
{// Put matrix x into the output stream out.
   ChainIterator<HeadNode<T> > p;// head node iterator

   // output matrix dimensions
   out << "rows = " << x.rows << " columns = "
       << x.cols << endl;

   // set h to point to first head node
   HeadNode<T> *h = p.Initialize(x.a);
   if (!h) {out << "No non-zero terms" << endl;
   	    return out;}

   // output one row at a time
   while (h) {
      out << "row " << h->row << endl;
      out << h->a << endl;  // output row chain
      h = p.Next();         // next head node
      }

   return out;
}

template<class T>
void LinkedMatrix<T>::
     Transpose(LinkedMatrix<T> &b) const
{// Return transpose of *this as matrix b.
   b.a.Erase(); // delete all nodes from b

   // create bins to collect rows of b
   Chain<CNode<T> > *bin;
   bin = new Chain<CNode<T> > [cols + 1];

   // head node iterator
   ChainIterator<HeadNode<T> > p;

   // set h to point to first head node of *this
   HeadNode<T> *h = p.Initialize(a);

   // copy terms of *this into bins
   while (h) { // examine all rows
      int r = h->row; // row number for row chain

      // row chain iterator
      ChainIterator<CNode<T> > q;

      // set z to point to first node in row chain
      CNode<T> *z = q.Initialize(h->a);

      CNode<T> x;  // temporary node
      // terms from row r of *this go to column r of b
      x.col = r;

      // examine all terms in row r of *this
      while (z) {// go down row r
         x.value = z->value;
         // append term to bin for row z->col of b
         bin[z->col].Append(x);
         z = q.Next();  // next term in row
         }

      h = p.Next(); // go to next row
      }

   // set dimensions of b
   b.rows = cols;
   b.cols = rows;

   // assemble head node chain of b
   HeadNode<T> H;
   // scan bins
   for (int i = 1; i <= cols; i++)
      if (!bin[i].IsEmpty()) {// row i of transpose
         H.row = i;
         H.a = bin[i];
         b.a.Append(H);
         bin[i].Zero();} // save from destructor

   H.a.Zero(); // save from destructor

   delete [] bin;
}

#endif
