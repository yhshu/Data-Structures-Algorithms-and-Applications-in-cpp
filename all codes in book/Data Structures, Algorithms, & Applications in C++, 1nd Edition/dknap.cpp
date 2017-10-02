// dynamic programming knapsack
// non-recursive version

#include <iostream.h>
#include <stdlib.h>
#include "dosmax.h"  // has max() and min()
#include "make2db.h"


template<class T>
void Knapsack(T p[], int w[], int c, int n, T** f)
{// Compute f[i][y] for all i and y.

   // initialize f[n][]
   int yMax = min(w[n]-1,c);
   for (int y = 0; y <= yMax; y++)
      f[n][y] = 0;
   for (y = w[n]; y <= c; y++)
      f[n][y] = p[n];
   
   // compute remaining f's
   for (int i = n - 1; i > 1; i--) {
      yMax = min(w[i]-1,c);
      for (int y = 0; y <= yMax; y++)
         f[i][y] = f[i+1][y];
      for (y = w[i]; y <= c; y++)
         f[i][y] = max(f[i+1][y],
                       f[i+1][y-w[i]] + p[i]);
      }
   f[1][c] = f[2][c];
   if (c >= w[1])
      f[1][c] = max(f[1][c], f[2][c-w[1]] + p[1]);
}

template<class T>
void Traceback(T **f, int w[], int c, int n, int x[])
{// Compute x for optimal filling.
   for (int i = 1; i < n; i++)
      if (f[i][c] == f[i+1][c]) x[i] = 0;
      else {x[i] = 1;
            c -= w[i];}
   x[n] = (f[n][c]) ? 1 : 0;
}

void main(void)
{
   int p[6] = {0, 6, 3, 5, 4, 6};
   int w[6] = {0, 2, 2, 6, 5, 4};
   int x[6];
   int **f;
   int n = 5;
   int c = 10;
   Make2DArray(f, n+1, c+1);
   Knapsack(p, w, c, n, f);
   cout << "Optimal value is ";
   cout << f[1][c] << endl;
   cout << "Rest of table is" << endl;
   for (int i = 2; i <= n; i++) {
      for (int j = 0; j <= c; j++)
         cout << f[i][j] << ' ';
      cout << endl;}
   Traceback(f,w,c,n,x);
   for (i = 1; i <= n; i++)
      cout << x[i] << ' ';
   cout << endl;
}
