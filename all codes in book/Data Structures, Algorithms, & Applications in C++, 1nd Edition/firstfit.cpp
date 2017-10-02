// First fit bin packing

#include <iostream.h>
#include "winner.h"

int winner(int a[], int b, int c)
{// For a max winner tree.
   if (a[b] >= a[c]) return b;
   return c;
}

void FirstFitPack(int s[], int n, int c)
{// Output first fit packing into bins of size c.
 // n is the number of objects and s[] their size.

   WinnerTree<int> *W = new WinnerTree<int> (n);
   int *avail = new int [n+1]; // bins
   
   // initialize n bins and winner tree
   for (int i = 1; i <= n; i++)
      avail[i] = c;  // initial available capacity
   W->Initialize(avail, n, winner);
   
   // put objects in bins
   for (i = 1; i <= n; i++) {// put s[i] in a bin
      // find first bin with enough capacity
      int p = 2;  // start search at left child of root
      while (p < n) {
         int winp = W->Winner(p);
         if (avail[winp] < s[i])  // first bin is in
            p++ ;                 // right subtree
         p *= 2;   // move to left child
         }

      int b;   // will be set to bin to use
      p /= 2;  // undo last left child move
      if (p < n) {// at a tree node
        b = W->Winner(p);
        // if b is right child, need to check
        // bin b-1.  No harm done by checking
        // bin b-1 even if b is left child.
        if (b > 1 && avail[b-1] >= s[i])
           b--;}
      else  // arises when n is odd
         b = W->Winner(p/2);

      cout << "Pack object " << i << " in bin "
           << b << endl;
      avail[b] -= s[i];  // update avail. capacity
      W->RePlay(b, winner);
      }
}

void main(void)
{
   int n, c; // number of objects and bin capacity
   cout << "Enter number of objects and bin capacity"
        << endl;
   cin >> n >> c;
   if (n < 2) {cout << "Too few objects" << endl;
               exit(1);}
   int *s = new int[n+1];
   
   for (int i = 1; i <= n; i++) {
     cout << "Enter space requirement of object "
          << i << endl;
     cin >> s[i];
     if (s[i] > c) {
       cout << "Object too large to fit in a bin"
            << endl;
       exit(1);}
     }
   FirstFitPack(s, n, c);
}
