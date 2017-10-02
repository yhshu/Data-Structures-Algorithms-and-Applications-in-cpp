// dynamic programming matrix multiplication chain
// non-recursive solution

#include <iostream.h>
#include "make2db.h"

void MatrixChain(int r[], int q, int **c, int **kay)
{// Compute costs and kay for all Mij's.

   // initialize c[i][i], c[i][i+1], and kay[i][i+1]
   for (int i = 1; i < q; i++) {
      c[i][i] = 0;
      c[i][i+1] = r[i]*r[i+1]*r[i+2];
      kay[i][i+1] = i;
      }
   c[q][q] = 0;
   
   // compute remaining c's and kay's
   for (int s = 2; s < q; s++)
      for (int i = 1; i <= q - s; i++) {
         // min term for k = i
         c[i][i+s] = c[i][i] + c[i+1][i+s]
                     + r[i]*r[i+1]*r[i+s+1];
         kay[i][i+s] = i;

         // remaining min terms
         for (int k = i+1; k < i + s; k++) {
            int t = c[i][k] + c[k+1][i+s]
                    + r[i]*r[k+1]*r[i+s+1];
            if (t < c[i][i+s]) {// smaller min term
               c[i][i+s] = t;
               kay[i][i+s] = k;}
            }
         }      
}

void Traceback(int i, int j, int **kay)
{
   if (i == j) return;
   Traceback(i, kay[i][j], kay);
   Traceback(kay[i][j]+1, j, kay);
   cout << "Multiply M " << i << ", " << kay[i][j];
   cout << " and M " << (kay[i][j]+1) << ", " << j
        << endl;
}

void main(void)
{
   int r[7] = {0, 10, 5, 1, 10, 2, 10};
   int **kay, **c;
   int q = 5;
   Make2DArray(c,q+1,q+1);
   Make2DArray(kay,q+1,q+1);
   
   MatrixChain(r,q,c,kay);
   
   cout << "Optimal cost is " << c[1][q] << endl;
   cout << "Cost matrix is" << endl;
   for (int i=1; i<=q; i++) {
      for (int j=1; j<i; j++)
         cout << 0 << ' ';
      for (j=i; j<=q; j++)
         cout << c[i][j] << ' ';
      cout << endl;}
   
   cout << "kay matrix is" << endl;
   for (i=1; i<=q; i++) {
      for (int j=1; j<=i; j++)
         cout << 0 << ' ';
      for (j=i+1; j<=q; j++)
         cout << kay[i][j] << ' ';
      cout << endl;}
   
   Traceback(1,q,kay);
}
