// formula-based winner tree
// RePlay modified to play essential matches only

#ifndef WinnerTree_
#define WinnerTree_

#include <iostream.h>
#include <stdlib.h>
#include "xcept.h"

template<class T>
class WinnerTree {
   public:
      WinnerTree(int TreeSize = 10);
      ~WinnerTree() {delete [] t;}
      void Initialize(T a[], int size,
          int(*winner)(T a[], int b, int c));
      int Winner()  const {return (n) ? t[1] : 0;}
      int Winner(int i) const
          {return (i < n) ? t[i] : 0;}
      void RePlay(int i, int(*winner)
          (T a[], int b, int c));
      void Output() const;
   private:
      int MaxSize;
      int n;      // current size
      int LowExt; // lowest-level external nodes
      int offset; // 2^k - 1
      int *t;     // array for winner tree
      T *e;       // element array
      void Play(int p, int lc, int rc,
           int(*winner)(T a[], int b, int c));
};

template<class T>
WinnerTree<T>::WinnerTree(int TreeSize)
{// Constructor for winner tree.
   MaxSize = TreeSize;
   t = new int[MaxSize];
   n = 0;
}

template<class T>
void WinnerTree<T>::Initialize(T a[], int size,
             int(*winner)(T a[], int b, int c))
{// Initialize winner t for array a.
   if (size > MaxSize || size < 2)
      throw BadInput();
   n = size;
   e = a;

   // compute  s = 2^log (n-1)
   int i, s;
   for (s = 1; 2*s <= n-1; s += s);

   LowExt = 2*(n-s);
   offset = 2*s-1;

   // play matches for lowest-level external nodes
   for (i = 2; i <= LowExt; i += 2)
      Play((offset+i)/2, i-1, i, winner);

   // handle remaining external nodes
   if (n % 2) {// special case for odd n, play
               // internal and external node
      Play(n/2, t[n-1], LowExt+1, winner);
      i = LowExt+3;}
   else i = LowExt+2;

   // i is left-most remaining external node
   for (; i <= n; i += 2)
      Play((i-LowExt+n-1)/2, i-1, i, winner);
}

template<class T>
void WinnerTree<T>::Play(int p, int lc, int rc,
	 int(*winner)(T a[], int b, int c))
{// Play matches beginning at t[p].
 // lc and rc are the children of t[p].
   t[p] = winner(e, lc, rc);

   // more matches possible if at right child
   while (p > 1 && p % 2) {// at a right child
      t[p/2] = winner(e, t[p-1], t[p]);
      p /= 2;  // go to parent
      }
}

template<class T>
void WinnerTree<T>::RePlay(int i,
          int(*winner)(T a[], int b, int c))
{// Replay matches for element i.
   if (i <= 0 || i > n) throw OutOfBounds();

   int p,   // match node
       lc,  // left child of p
       rc;  // right child of p

   // find first match node and its children
   if (i <= LowExt) {// begin at lowest level
   	p = (offset + i)/2;
   	lc = 2*p - offset; // left child of p
   	rc = lc+1;}
   else {p = (i-LowExt+n-1)/2;
         if (2*p == n-1) {lc = t[2*p];
                          rc = i;}
         else {lc = 2*p - n + 1 + LowExt;
               rc = lc+1;}
        }

   int NewWinner = winner(e, lc, rc);
   if (NewWinner != i && NewWinner == t[p])
      // no need to play additional matches
      return;
   t[p] = NewWinner;

   // play remaining matches
   p /= 2;  // move to parent
   for (; p >= 1; p /= 2) {
      NewWinner = winner(e, t[2*p], t[2*p+1]);
      if (NewWinner != i || NewWinner == t[p])
         // no need to play additional matches
         return;

      t[p] = NewWinner;
      }
}

template<class T>
void WinnerTree<T>::Output() const
{
   cout << "size = "<< n << " LowExt = " << LowExt
        << " Offset = " << offset << endl;
   cout << "Winner tree pointers are" << endl;
   for (int i = 1; i < n; i++)
      cout << t[i] << ' ';
   cout << endl;
}

#endif
