// maximum non-crossing subset
// dynamic programming

#include <iostream.h>
#include <stdlib.h>
#include "dosmax.h"  // has max() and min()
#include "make2db.h"

void MNS(int C[], int n, int **size)
{// Compute size[i][j] for all i and j.

   // initialize size[1][*]
   for (int j = 0; j < C[1]; j++)
      size[1][j] = 0;
   for (j = C[1]; j <= n; j++)
      size[1][j] = 1;

   // compute size[i][*], 1 < i < n
   for (int i = 2; i < n; i++) {
      for (int j = 0; j < C[i]; j++)
         size[i][j] = size[i-1][j];
      for (j = C[i]; j <= n; j++)
         size[i][j] = max(size[i-1][j],
                          size[i-1][C[i]-1]+1);
      }

   size[n][n] = max(size[n-1][n],
                    size[n-1][C[n]-1]+1);
}
      
void Traceback(int C[], int **size, int n, int Net[],
                        int& m)
{// Return MNS in Net[0:m-1].
   int j = n;  // max bottom pin number allowed
   m = 0;      // cursor for Net
   for (int i = n; i > 1; i--)
      // is net i in MNS?
      if (size[i][j] != size[i-1][j]){// yes
         Net[m++] = i;
         j = C[i] - 1;}

   // is net 1 in MNS?
   if (j >= C[1])
      Net[m++] = 1;  // yes
}

void main(void)
{
   const int n = 10;
   int C[n+1] = {0, 8, 7, 4, 2, 5, 1, 9, 3, 10, 6};
   int **size;
   Make2DArray(size,n+1,n+1);
   
   MNS(C,n,size);
   
   cout << "matrix size is" << endl;
   for (int i = 1; i < n; i++) {
      for (int j = 1; j <= n; j++)
         cout << size[i][j] << ' ';
      cout << endl;
      }
   
   int Net[n+1], m;
   
   Traceback(C,size,n,Net,m);
   
   cout << "Maximum non-crossing subset is" << endl;
   for (i = 0; i < m; i++)
      cout << Net[i] << ' ';
   cout << endl;
}
