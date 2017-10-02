// crossing distribution using a linear list

#include <iostream.h>
#include "llist.h"

void main(void)
{
   const int n = 10;
   LinearList<int> L(n);
   int K, A[n+1], B[n+1], X[n+1];
   int k[11] = {0, 7, 6, 3, 1, 2, 0, 2, 0, 1, 0};
   int C[n+1] = {0, 8, 7, 4, 2, 5, 1, 9, 3, 10, 6};
   K = 22;
   
   int r = K/2; // remaining number of crossings
                // needed in top half

   // scan wires right to left
   int w = n;   // w is current wire
   while (r) {  // need more crossings in top half
      if (k[w] < r) {// use all from wire w
                     L.Insert(k[w], w);
   		     r -= k[w];}
      else {// use only r from wire w
            L.Insert(r, w);
            r = 0;}
      w--;}

   // determine wire permutation at center
   // first w wires have same ordering
   for (int i = 1; i <= w; i++)
      X[i] = i;

   // ordering of remaining wires is from L
   for (i = w+1; i <= n; i++)
      L.Delete(1, X[i]);
 
   // compute top half permutation
   for (i = 1; i <= n; i++)
      A[X[i]] = i;

  // compute bottom half permutation
   for (i = 1; i <= n; i++)
      B[i] = C[X[i]];
   
   cout << "A is ";
   for (i = 1; i <= n; i++)
      cout << A[i] << ' ';
   cout << endl;
   
   cout << "B is ";
   for (i = 1; i <= n; i++)
      cout << B[i] << ' ';
   cout << endl;
}
