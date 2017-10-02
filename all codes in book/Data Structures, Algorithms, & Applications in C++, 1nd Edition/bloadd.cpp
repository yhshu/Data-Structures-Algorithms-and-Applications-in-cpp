// iterative code for container loading by backtracking

#include<iostream.h>

template<class T>
T MaxLoading(T w[], T c, int n, int bestx[])
{// Return best loading and its value.
 // Iterative backtracking version.
   // initialize for root
   int i = 1;  // level of current node
   // x[1:i-1] is path to current node
   int *x = new int [n+1];
   T bestw = 0,  // weight of best loading so far
     cw = 0,     // weight of current loading
     r = 0;      // sum of remaining container weights
   for (int j = 1; j <= n; j++)
      r += w[j];

   // search the tree
   while (true) {
      // move down and left as far as possible
      while (i <= n && cw + w[i] <= c) {
         // move to left child
         r -= w[i];
         cw += w[i];
         x[i] = 1;
         i++;
         }

      if (i > n) {// leaf reached
         for (int j = 1; j <= n; j++)
            bestx[j] = x[j];
         bestw = cw;}
      else {// move to right child
            r -= w[i];
            x[i] = 0;
            i++;}

      // back up if necessary
      while (cw + r <= bestw) {
         // this subtree does not have a better
         // leaf, backup
         i--;
         while (i > 0 && !x[i]) {
            // backup from a right child
            r += w[i];
            i--;
            }

         if (i == 0) {delete [] x;
                      return bestw;}

         // move to right subtree
         x[i] = 0;
         cw -= w[i];
         i++;
         }
      }
}


void main(void)
{
   int w[6] = {0, 2, 2, 6, 5, 5};
   int x[6];
   int n = 5;
   int c = 16;
   cout << "Value of max loading is" << endl;
   cout << MaxLoading(w,c,n,x) << endl;
   cout << "x values are" << endl;
   for (int i=1; i<=n; i++)
      cout << x[i] << ' ';
   cout << endl;
}
