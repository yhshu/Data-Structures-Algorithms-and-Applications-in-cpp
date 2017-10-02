
// Next fit bin packing

#include <iostream.h>
#include "winner4.h"

int winner(int a[], int b, int c)
{// For a max winner tree.
   if (a[b] >= a[c]) return b;
   return c;
}

void NextFitPack(int s[], int n, int c)
{// Output next fit packing into bins of size c.
 // n is the number of objects and s[] their size.

   WinnerTree<int> *W = new WinnerTree<int> (n);
   int *avail = new int [n+1]; // bins
   
   // initialize n bins and winner tree
   for (int i = 1; i <= n; i++)
      avail[i] = c;  // initial available capacity
   W->Initialize(avail, n, winner);
   int last = 0; // bin used for last object packed
   
   // put objects in bins
   for (i = 1; i <= n; i++) {// put s[i] in a bin
      // see if there is a nonempty bin to the
      // right of bin last that has enough capcity

      // set j to next bin with enough capacity
      int j = last + 1;
      if (avail[j] < s[i])
         // there must be another bin j+1
         if (avail[j+1] >= s[i]) j++;
         else {// move up the tree
            // set p to parent of bin j
            int p = W->Parent(j);
            bool done = false;
            if (p == n-1) {// special case
               int q;
               if (j%2) q = j + 1;
               else q = j + 2;
               // q must be <= n
               if (avail[q] >= s[i]) {
                  j = q;
                  done = true;}
               }
            
            if (!done) {
               // move to nearest ancestor
               // of p with enough capacity
               p /= 2;
               while (avail[W->Winner(p)] < s[i])
                  p /= 2;

               // now move to leftmost child of p
               // that has enough capacity
               p *= 2;  // start search at left child
               while (p < n) {
                  int winp = W->Winner(p);
                  if (avail[winp] < s[i])  // first bin is in
                     p++ ;                 // right subtree
                  p *= 2;   // move to left child
                  }
         
               p /= 2;  // undo last left child move
               if (p < n) {// at a tree node
                 j = W->Winner(p);
                 // if j is right child, need to check
                 // bin j-1.  No harm done by checking
                 // bin j-1 even if j is left child.
                 if (j > 1 && avail[j-1] >= s[i])
                    j--;
                 }
               else  // arises when n is odd
                  j = W->Winner(p/2);
               }
           }  

   // see if bin j is nonempty
   if (avail[j] == c) {// empty bin, execute step 2
      // find first bin with enough capacity
      int p = 2;  // start search at left child of root
      while (p < n) {
         int winp = W->Winner(p);
         if (avail[winp] < s[i])  // first bin is in
            p++ ;                 // right subtree
         p *= 2;   // move to left child
         }

      p /= 2;  // undo last left child move
      if (p < n) {// at a tree node
        j = W->Winner(p);
        // if j is right child, need to check
        // bin j-1.  No harm done by checking
        // bin j-1 even if j is left child.
        if (j > 1 && avail[j-1] >= s[i])
           j--;
        }
      else  // arises when n is odd
         j = W->Winner(p/2);
      }

      cout << "Pack object " << i << " in bin "
           << j << endl;
      avail[j] -= s[i];  // update avail. capacity
      W->RePlay(j, winner);
      last = j;
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
   NextFitPack(s, n, c);
}
