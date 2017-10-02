
// file loser.h
// formula-based loser tree

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

   // first record winners in t[1:n-1]
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

   // record overall winner in t[0]
   t[0] = t[1];

   // now make a level-order traversal of t
   // replacing winners by losers
   for (i = 1; i < n; i++) {
      // set t[i] to loser of match played at t[i]
      int lc = 2 * i;   // left child of i
      int rc = lc + 1;  // right child of i
      // eventually e[LeftPlayer] denotes left player
      // of match and t[i] and e[RightPlayer] denotes
      // other player
      int LeftPlayer, RightPlayer;
      // determine LeftPlayer
      if (lc <= n - 1) LeftPlayer = t[lc];
      else // left child is an external node
         if (lc <= offset)
            LeftPlayer = lc + LowExt - n + 1;
         else LeftPlayer = lc - offset;

      // determine RightPlayer
      if (rc <= n - 1) RightPlayer = t[rc];
      else // right child is an external node
         if (rc <= offset)
            RightPlayer = rc + LowExt - n + 1;
         else RightPlayer = rc - offset;

      // determine loser of match
      if (LeftPlayer == t[i])
         // RightPlayer is loser
         t[i] = RightPlayer;
      else // LeftPlayer is loser
         t[i] = LeftPlayer;
      }

}

template<class T>
void LoserTree<T>::Play(int p, int lc, int rc,
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
