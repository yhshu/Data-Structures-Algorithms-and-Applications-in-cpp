
// dynamic programming recursive knapsack

#include <iostream.h>
#include "make2db.h"

int p[6] = {0, 6, 3, 5, 4, 6};
int w[6] = {0, 2, 2, 6, 5, 4};
int x[6];
int **D;
int n = 5;
int c = 10;

int F(int i, int y)
{// Return f(i,y).
   if (i == n)
      // use Equation 15.1
      if (y < w[n]) {
        // x[n] is 0
        D[n][y] = 0;
        return 0;
        }
      else {// x[n] is 1
         D[n][y] = 1;
         return p[n];
         }

   // use Equation 15.2
   if (y < w[i]) {// x[i] is 0
      D[i][y] = 0;
      return F(i+1,y); 
      }
   
   int p1 = F(i+1,y);
   int p2 = F(i+1,y-w[i]) + p[i];
   if (p1 < p2) {// x[i] is 1
      D[i][y] = 1;
      return p2;
      }
   // x[1] is 0
   D[i][y] = 0;
   return p1;
}

void Traceback(int **D, int w[], int c, int n, int x[])
{// Compute x for optimal filling.
   for (int i = 1; i < n; i++)
      if (D[i][c]) {
         x[i] = 1;
         c -= w[i];}
      else x[i] = 0;
   x[n] = D[n][c];
}

void main(void)
{
   Make2DArray(D,n+1,c+1);
   cout << "Optimal value is ";
   cout << F(1,c) << endl;
   Traceback(D,w,c,n,x);
   cout << "The x values are ";
   for (int i = 1; i <= n; i++)
      cout << x[i] << " ";
   cout << endl;
}
