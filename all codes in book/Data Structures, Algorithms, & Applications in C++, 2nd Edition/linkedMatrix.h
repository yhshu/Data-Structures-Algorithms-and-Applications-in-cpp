// linked representation of a sparse matrix

#ifndef linkedMatrix_
#define linkedMatrix_

#include <iostream>
#include "extendedChain.h"
#include "matrixElements.h"

using namespace std;

template<class T>
class linkedMatrix 
{
   friend ostream& operator<<
          (ostream&, linkedMatrix<T>&);
   friend istream& operator>>
          (istream&, linkedMatrix<T>&);
   public:
      linkedMatrix(){}
      ~linkedMatrix(){}
      void transpose(linkedMatrix<T> &b);
   private:
      int rows,       // number of rows in matrix
          cols;       // number of columns in matrix
      extendedChain<headerElement<T> > headerChain;
};

template<class T>
istream& operator>>(istream& in, linkedMatrix<T>& x)
{// Input matrix x from the stream in.
   x.headerChain.clear();
       // delete all nodes from x

   // get matrix characteristics
   int terms;   // number of terms to be input
   cout << "Enter number of rows, columns, and terms" 
        << endl;
   in >> x.rows >> x.cols >> terms;

   // create fictional row zero
   headerElement<T> header;  // header for current row
   header.row = 0;           // current row number

   // get terms of matrix x
   for (int i = 1; i <= terms; i++) 
   {
      // input next term
      cout << "Enter row, column, and value of term " 
           << i << endl;
      rowElement<T> *term = new rowElement<T>;
      int row;
      in >> row >> term->col >> term->value;

      // check if new term is part of current row
      if (row > header.row)
      {// start a new row
         // append header of current row to
         // header node chain only if row not zero
         if (header.row != 0)
            x.headerChain.push_back(header);

         // prepare header for new row
         header.row = row;
         header.rowChain.zero();
               // clear without deleting nodes
      }

      // add new term to row chain
      header.rowChain.push_back(*term);
   }

   // take care of last row of matrix
   if (header.row != 0)
      x.headerChain.push_back(header);
   header.rowChain.zero(); // save from chain destructor

   return in;
}

template<class T>
ostream& operator<<(ostream& out, linkedMatrix<T>& x)
{// Put matrix x into the output stream out.
   // output matrix dimensions
   out << "rows = " << x.rows << " columns = "
       << x.cols << endl << "  ";

   if (x.headerChain.empty())
   {
      out << "No non-zero terms" << endl;
      return out;
   }

   out << x.headerChain << endl;
   return out;
}

/****************************************************************/
// explict code to overload with T = int for test as compiler
// unable to generate

istream& operator>>(istream& in, linkedMatrix<int>& x)
{// Input matrix x from the stream in.
   x.headerChain.clear();
       // delete all nodes from x

   // get matrix characteristics
   int terms;   // number of terms to be input
   cout << "Enter number of rows, columns, and terms" 
        << endl;
   in >> x.rows >> x.cols >> terms;

   // create fictional row zero
   headerElement<int> header;  // header for current row
   header.row = 0;             // current row number

   // get terms of matrix x
   for (int i = 1; i <= terms; i++) 
   {
      // input next term
      cout << "Enter row, column, and value of term " 
           << i << endl;
      rowElement<int> *term = new rowElement<int>;
      int row;
      in >> row >> term->col >> term->value;

      // check if new term is part of current row
      if (row > header.row)
      {// start a new row
         // append header of current row to
         // header node chain only if row not zero
         if (header.row != 0)
            x.headerChain.push_back(header);

         // prepare header for new row
         header.row = row;
         header.rowChain.zero();
               // clear without deleting nodes
      }

      // add new term to row chain
      header.rowChain.push_back(*term);
   }

   // take care of last row of matrix
   if (header.row != 0)
      x.headerChain.push_back(header);
   header.rowChain.zero(); // save from chain destructor

   return in;
}

ostream& operator<<(ostream& out, linkedMatrix<int>& x)
{// Put matrix x into the output stream out.
   // output matrix dimensions
   out << "rows = " << x.rows << " columns = "
       << x.cols << endl << "  ";

   if (x.headerChain.empty())
   {
      out << "No non-zero terms" << endl;
      return out;
   }

   out << x.headerChain << endl;

   return out;
}
/****************************************************************/

template<class T>
void linkedMatrix<T>::transpose(linkedMatrix<T> &b)
{// Return transpose of *this as matrix b.
   b.headerChain.clear(); // delete all nodes from b

   // create bins to collect rows of b
   extendedChain<rowElement<T> > *bin;
   bin = new extendedChain<rowElement<T> > [cols + 1];

   // head node iterator
   extendedChain<headerElement<T> >::iterator
      ih = headerChain.begin(),
      ihEnd = headerChain.end();


   // copy terms of *this into bins
   while (ih != ihEnd)
   {// examine all rows
      int r = ih->row; // row number for row chain

      // row chain iterator
      extendedChain<rowElement<T> >::iterator
         ir = ih->rowChain.begin(),
         irEnd = ih->rowChain.end();


      rowElement<T> x;
      // terms from row r of *this go to column r of b
      x.col = r;

      while (ir != irEnd)
      {// copy a term from the row chain into a bin
         x.value = ir->value;
         // x will eventually be in row ir->col of transpose
         bin[ir->col].push_back(x);
         ir++;  // next term in row
      }

      ih++; // go to next row
   }

   // set dimensions of transpose
   b.rows = cols;
   b.cols = rows;

   // assemble header chain of transpose
   headerElement<T> h;
   // scan bins
   for (int i = 1; i <= cols; i++)
      if (!bin[i].empty())
      {// row i of transpose
         h.row = i;
         h.rowChain = bin[i];
         b.headerChain.push_back(h);
         bin[i].zero(); // save from destructor
      }

   h.rowChain.zero();   // save from destructor

   delete [] bin;
}

#endif
