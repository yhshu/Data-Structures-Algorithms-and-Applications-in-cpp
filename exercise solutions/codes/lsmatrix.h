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
      T Retrieve(int i, int j) const;
      LinkedMatrix<T>& Store(const T& x, int i, int j);
      void Add(const LinkedMatrix<T> &b,
              LinkedMatrix<T> &c) const;
      void Subtract(const LinkedMatrix<T> &b,
              LinkedMatrix<T> &c) const;
   private:
      HeadNode<T>* Copy(HeadNode<T> *h) const;
          // copy a row
      HeadNode<T>* MinusCopy(HeadNode<T> *h) const;
          // copy negative of a row
      HeadNode<T>* AddRows
             (HeadNode<T> *ah, HeadNode<T>* bh) const;
          // add a row of one matrix to a row of another
      HeadNode<T>* SubRows
             (HeadNode<T> *ah, HeadNode<T>* bh) const;
          // subtract a row of one matrix
          // from a row of another
      int rows, cols;        // matrix dimensions
      Chain<HeadNode<T> > a; // head node chain
};

template<class T>
istream& operator>>(istream& in, LinkedMatrix<T>& x)
{// Input matrix x from the stream in.
   x.a.Erase(); // delete all nodes from x

   // get matrix characteristics
   int terms;  // number of terms to be input
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
   if (!h) {out << "No nonzero terms" << endl;
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

template <class T>
T LinkedMatrix<T>::Retrieve(int i, int j) const
{// Return the (i,j) element of the matrix.
   // first make sure i and j are valid
   if (i < 1 || j < 1 || i > rows || j > cols)
       throw OutOfBounds();

   // find chain for row i, using an iterator
   // p for the head node chain
   ChainIterator<HeadNode<T> > p;

   // define h to point to current head node
   HeadNode<T> *h = p.Initialize(a);

   // advance h to head node for row i
   while (h && h->row < i)
      h = p.Next();
  
   if (!h || h->row > i) // no row chain for row i
      return 0;

   // search the row chain for column j element,
   // using a row chain iterator q
   ChainIterator<CNode<T> > q;
 
   // define r to point to current row chain node
   CNode<T> *r = q.Initialize(h->a);
 
   // advance r to node with column value j
   while (r && r->col < j)
      r = q.Next();
    
   if (!r || r->col > j) // no node for (i,j) element
      return 0;
   else return r->value;
}
 

template <class T>
LinkedMatrix<T>& LinkedMatrix<T>::
                 Store(const T& x, int i, int j)
{// Store x as (i,j) element of the matrix.
   // first make sure i and j are valid
   if (i < 1 || j < 1 || i > rows || j > cols)
       throw OutOfBounds();

   // find chain for row i, using an iterator
   // p for the head node chain
   ChainIterator<HeadNode<T> > p;

   // define h to point to current head node
   // and hCount to be distance from start 
   HeadNode<T> *h = p.Initialize(a);
   int hCount = 0;

   // advance h to head node for row i
   while (h && h->row < i) {
      h = p.Next();
      hCount++;
      }
  
   if (!h || h->row > i) {// no row chain for row i
      // do not store a zero element
      if (x == 0) return *this;

      // create new row chain
      HeadNode<T> H;  // head node for the row chain
      H.row = i;

      // create row chain node for new element
      CNode<T> *c = new CNode<T>;
      c->col = j;
      c->value = x;
      // append row chain node to head node
      H.a.Append(*c);

      // insert row chain into head node chain
      a.Insert(hCount, H);
      H.a.Zero();  // save from chain destructor
      return *this;}

   // chain for row i exists
   // search the row chain for column j element,
   // using a row chain iterator q
   ChainIterator<CNode<T> > q;
 
   // define r to point to current row chain node
   // and rCount to be distance from start 
   CNode<T> *r = q.Initialize(h->a);
   int rCount = 0;
 
   // advance r to node with column value j
   while (r && r->col < j) {
      r = q.Next();
      rCount++;}
    
   if (!r || r->col > j) {// no node for (i,j) element
      // do not store a zero element
      if (x == 0) return *this;
      // create row chain node for new element
      CNode<T> *c = new CNode<T>;
      c->col = j;
      c->value = x;
      // insert row chain node into row chain
      h->a.Insert(rCount, *c);
      return *this;}

   // there is already an (i,j) element, change it
   CNode<T> z;
   h->a.Delete(rCount+1, z);
   if (x == 0) {// check if row chain empty
                if (h->a.IsEmpty()) {
                    // delete row chain
                    HeadNode<T> H;
                    a.Delete(hCount+1, H);}
                return *this;}
   // insert new value for (i,j)
   z.value = x;
   h->a.Insert(rCount, z);
   return *this;
}

template <class T>
HeadNode<T>* LinkedMatrix<T>::Copy(HeadNode<T> *h) const
{// Return a copy of row defined by h.

   // copy the head node
   HeadNode<T> *hCopy = new HeadNode<T>;
   hCopy->row = h->row;

   // use a chain iterator to traverse row nodes
   ChainIterator<CNode<T> > q;
   CNode<T> *r = q.Initialize(h->a);
   while (r) {
      // copy and append the term
      hCopy->a.Append(*r);
      // advance to next term in row
      r = q.Next();
      }
   return hCopy;
}
      

template <class T>
HeadNode<T>* LinkedMatrix<T>::AddRows
    (HeadNode<T> *ah, HeadNode<T>* bh) const
{// Add the matrix rows ah and bh and return
 // a pointer to the result.

   // create head node for result
   HeadNode<T> *sum = new HeadNode<T>;
   sum->row = ah->row;

   // define chain iterators for the two chains
   // and initialize
   ChainIterator<CNode<T> > aIter, bIter;
   CNode<T> *aTerm = aIter.Initialize(ah->a),
            *bTerm = bIter.Initialize(bh->a);
   
   // go down the chains copying terms
   while (aTerm && bTerm)
      if (aTerm->col > bTerm->col) {
         // copy bTerm
         sum->a.Append(*bTerm);
         bTerm = bIter.Next();}
      else if (aTerm->col < bTerm->col) {
              // copy aTerm
              sum->a.Append(*aTerm);
              aTerm = aIter.Next();}
           else {// add values and append
                 T x = aTerm->value + bTerm->value;
                 if (x) {// x != 0
                         CNode<T> p;
                         p.col = aTerm->col;
                         p.value = x;
                         sum->a.Append(p);}
                 aTerm = aIter.Next();
                 bTerm = bIter.Next();}
              
   // copy remaining terms
   while (aTerm) {
      sum->a.Append(*aTerm);
      aTerm = aIter.Next();
      }
   while (bTerm) {
      sum->a.Append(*bTerm);
      bTerm = bIter.Next();
      }

   if (sum->a.IsEmpty()) {delete sum;
                          return 0;}
   else return sum;
}
 

template <class T>
void LinkedMatrix<T>::Add(const LinkedMatrix<T> &b,
              LinkedMatrix<T> &c) const
{// Compute c = (*this) + b.

   // verify compatibility
   if (rows != b.rows || cols != b.cols)
     throw SizeMismatch(); // incompatible matrices

   // set characteristics of result c
   c.rows = rows;
   c.cols = cols;
   c.a.Erase();  // delete nodes in c

   // define iterators for head node chains
   // of *this and b and initialize
   ChainIterator<HeadNode<T> > tHeadIter, bHeadIter;
   HeadNode<T> *th = tHeadIter.Initialize(a);
   HeadNode<T> *bh = bHeadIter.Initialize(b.a);

   // go down the head node chains
   // until we fall off one of them
   while (th && bh)
      // compare row numbers
      if (th->row < bh->row) {
         // copy row of *this and append to c.a
         c.a.Append(*Copy(th));
         // advance to next row of *this
         th = tHeadIter.Next();}
      else if (th->row > bh->row) {
              // copy row of b and append to c.a
              c.a.Append(*Copy(bh));
              // advance to next row of b
              bh = bHeadIter.Next();}
            else {// rows are the same, add and
                  // append to c.a
                  HeadNode<T> *x = AddRows(th, bh);
                  if (x)  {// append to head node chain
                           c.a.Append(*x);
                           // save row nodes from destructor
                           // and delete head node as it has
                           // been copied by Append
                           x->a.Zero();
                           delete x;
                           }
                  th = tHeadIter.Next();
                  bh = bHeadIter.Next();
                  }

   // take care of remaining rows
   // at most one of *this and b has unprocessed rows
   while (th) {// copy a row of *this
      c.a.Append(*Copy(th));
      // advance to next row of *this
      th = tHeadIter.Next();
      }
         
   while (bh) {// copy a row of b
      c.a.Append(*Copy(bh));
      // advance to next row of *this
      bh = bHeadIter.Next();
      }
}

      
template <class T>
HeadNode<T>* LinkedMatrix<T>::MinusCopy(HeadNode<T> *h) const
{// Return a copy of the negative of row defined by h.

   // copy the head node
   HeadNode<T> *hCopy = new HeadNode<T>;
   hCopy->row = h->row;

   // use a chain iterator to traverse row nodes
   ChainIterator<CNode<T> > q;
   CNode<T> *r = q.Initialize(h->a);
   while (r) {// copy a node and append
      CNode<T> c;
      c.col = r->col;
      c.value = -r->value;
      // append to row chain copy
      hCopy->a.Append(c);
      // advance to next node
      r = q.Next();
      }
   return hCopy;
}
      

template <class T>
HeadNode<T>* LinkedMatrix<T>::SubRows
    (HeadNode<T> *ah, HeadNode<T>* bh) const
{// Subtract the matrix rows ah and bh and return
 // a pointer to the result.

   // create head node for result
   HeadNode<T> *sum = new HeadNode<T>;
   sum->row = ah->row;

   // define chain iterators for the two chains
   // and initialize
   ChainIterator<CNode<T> > aIter, bIter;
   CNode<T> *aTerm = aIter.Initialize(ah->a),
            *bTerm = bIter.Initialize(bh->a);
   
   // go down the chains copying terms
   while (aTerm && bTerm)
      if (aTerm->col > bTerm->col) {
         // copy negative of bTerm
         CNode<T> y;
         y.col = bTerm->col;
         y.value = -bTerm->value;
         sum->a.Append(y);
         bTerm = bIter.Next();}
      else if (aTerm->col < bTerm->col) {
              // copy aTerm
              sum->a.Append(*aTerm);
              aTerm = aIter.Next();}
           else {// subtract values and append
                 T x = aTerm->value - bTerm->value;
                 if (x) {// x != 0
                         CNode<T> p;
                         p.col = aTerm->col;
                         p.value = x;
                         sum->a.Append(p);}
                 aTerm = aIter.Next();
                 bTerm = bIter.Next();}
              
   // copy remaining terms
   while (aTerm) {
      sum->a.Append(*aTerm);
      aTerm = aIter.Next();
      }
   while (bTerm) {
      CNode<T> y;
      y.col = bTerm->col;
      y.value = -bTerm->value;
      sum->a.Append(y);
      bTerm = bIter.Next();
      }

   if (sum->a.IsEmpty()) {delete sum;
                          return 0;}
   else return sum;
}
 

template <class T>
void LinkedMatrix<T>::Subtract(const LinkedMatrix<T> &b,
              LinkedMatrix<T> &c) const
{// Compute c = (*this) - b.

   // verify compatibility
   if (rows != b.rows || cols != b.cols)
     throw SizeMismatch(); // incompatible matrices

   // set characteristics of result c
   c.rows = rows;
   c.cols = cols;
   c.a.Erase();  // delete nodes in c

   // define iterators for head node chains
   // of *this and b and initialize
   ChainIterator<HeadNode<T> > tHeadIter, bHeadIter;
   HeadNode<T> *th = tHeadIter.Initialize(a);
   HeadNode<T> *bh = bHeadIter.Initialize(b.a);

   // go down the head node chains
   // until we fall off one of them
   while (th && bh)
      // compare row numbers
      if (th->row < bh->row) {
         // copy row of *this and append to c.a
         c.a.Append(*Copy(th));
         // advance to next row of *this
         th = tHeadIter.Next();}
      else if (th->row > bh->row) {
              // copy negative of row of b
              // and append to c.a
              c.a.Append(*MinusCopy(bh));
              // advance to next row of b
              bh = bHeadIter.Next();}
            else {// rows are the same, subtract and
                  // append to c.a
                  HeadNode<T> *x = SubRows(th, bh);
                  if (x)  {// append to head node chain
                           c.a.Append(*x);
                           // save row nodes from destructor
                           // and delete head node as it has
                           // been copied by Append
                           x->a.Zero();
                           delete x;
                           }
                  th = tHeadIter.Next();
                  bh = bHeadIter.Next();
                  }

   // take care of remaining rows
   // at most one of *this and b has unprocessed rows
   while (th) {// copy a row of *this
      c.a.Append(*Copy(th));
      // advance to next row of *this
      th = tHeadIter.Next();
      }
         
   while (bh) {// copy minus of a row of b
      c.a.Append(*MinusCopy(bh));
      // advance to next row of *this
      bh = bHeadIter.Next();
      }
}

#endif
