
// formula-based loser tree
// initialization as per Exercise 10.5(c)

#ifndef LoserTree_
#define LoserTree_

#include <iostream.h>
#include <stdlib.h>
#include "xcept.h"

template<class T>
class LoserTree {
   public:
      LoserTree(int TreeSize = 10);
      ~LoserTree() {delete [] t;}
      void Initialize(T a[], int size,
          int(*winner)(T a[], int b, int c));
      int Winner()  const {return (n) ? t[0] : 0;}
      void RePlay(int(*winner)
          (T a[], int b, int c));
      void Output() const;
   private:
      int MaxSize;
      int n;      // current size
      int LowExt; // lowest-level external nodes
      int offset; // 2^k - 1
      int *t;     // array for loser tree
      T *e;       // element array
      void Play(int p, int lc, int rc,
           int(*winner)(T a[], int b, int c));
};

template<class T>
LoserTree<T>::LoserTree(int TreeSize)
{// Constructor for winner tree.
   MaxSize = TreeSize;
   t = new int[MaxSize];
   n = 0;
}

template<class T>
void LoserTree<T>::Initialize(T a[], int size,
             int(*winner)(T a[], int b, int c))
{// Initialize loser tree t for array a.
   if (size > MaxSize || size < 2)
      throw BadInput();
   n = size;
   e = a;

   // compute  s = 2^log (n-1)
   int i, s;
   for (s = 1; 2*s <= n-1; s += s);

   LowExt = 2*(n-s);
   offset = 2*s-1;

   // play matches starting at
   // lowest-level external nodes
   for (i = 2; i <= LowExt; i += 2)
      Play((offset+i)/2, i-1, i, winner);

   // handle remaining external nodes
   if (n % 2) {// special case for odd n, play
               // internal and external node
      Play(n/2, t[(n-1)/2], LowExt+1, winner);
      i = LowExt+3;}
   else i = LowExt+2;

   // i is left-most remaining external node
   for (; i <= n; i += 2)
      Play((i-LowExt+n-1)/2, i-1, i, winner);

}

template<class T>
void LoserTree<T>::Play(int p, int lc, int rc,
	 int(*winner)(T a[], int b, int c))
{// Play matches beginning at t[p].
 // lc and rc are the children of t[p].
   int CurrentWinner = winner(e, lc, rc);
   if (CurrentWinner == lc)
      // loser is rc
      t[p] = rc;
   else // loser is lc
      t[p] = lc;

   // more matches possible if at right child
   while (p > 1 && p % 2) {// at a right child
      // parent of p has opponent information
      p /= 2;  // go to parent
      int NewWinner = winner(e, t[p], CurrentWinner);
      if (NewWinner != CurrentWinner) {
         // loser is CurrentWinner
         t[p] = CurrentWinner;
         CurrentWinner = NewWinner;}
      }

   // record winner of last match in t[p/2]
   t[p/2] = CurrentWinner;
}

template<class T>
void LoserTree<T>::RePlay
          (int(*winner)(T a[], int b, int c))
{// Replay matches for previous winner.
   // make sure loser tree has been initialized
   if (n < 2) throw OutOfBounds();

   int p;   // match node

   // find first match node
   int i = t[0];    // e[i] is previous winner
   if (i <= LowExt) // begin at lowest level
   	p = (offset + i)/2;
   else p = (i-LowExt+n-1)/2;

   int LastWinner = i;

   // play matches
   for (; p >= 1; p /= 2) {
      // play match at t[p]
      int NewWinner = winner(e, LastWinner, t[p]);
      // update loser if this has changed
      if (t[p] == NewWinner) {
         // e[t[p]] is no longer a loser
         t[p] = LastWinner;
         LastWinner = NewWinner;}
      }

   // put overall winner in t[0]
   t[0] = LastWinner;
}

template<class T>
void LoserTree<T>::Output() const
{
   cout << "size = "<< n << " LowExt = " << LowExt
        << " Offset = " << offset << endl;
   cout << "Loser tree pointers are" << endl;
   for (int i = 0; i < n; i++)
      cout << t[i] << ' ';
   cout << endl;
}

#endif
