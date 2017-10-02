// recursive dynamic programming matrix multiplication chains
// avoid recomputations

#include <iostream.h>
#include "make2db.h"

int r[7] = {0, 10, 5, 1, 10, 2, 10};
int **kay, **c;

int C(int i, int j)
{// Return c(i,j) and compute kay(i,j) = kay[i][j].
 // Avoid recomputations.

   // check if already computed
   if (c[i][j] > 0) return c[i][j];

   // c[i][j] not computed before, compute now
   if (i == j) return 0;  // one matrix
   if (i == j - 1) {// two matrices
                    kay[i][i+1] = i;
                    c[i][j] = r[i]*r[i+1]*r[i+2];
                    return c[i][j];}

   // more than two matrices
   // set u to min term for k = i
   int u = C(i,i) + C(i+1,j) + r[i]*r[i+1]*r[j+1];
   kay[i][j] = i;

   // compute remaining min terms and update u
   for (int k = i+1; k < j; k++) {
      int t = C(i,k) + C(k+1,j) + r[i]*r[k+1]*r[j+1];
      if (t < u) {// smaller min term
                  u = t;
                  kay[i][j] = k;}
      }

   c[i][j] = u;
   return u;
}

void Traceback(int i, int j, int **kay)
{// Output best way to compute Mij.
   if (i == j) return;
   Traceback(i, kay[i][j], kay);
   Traceback(kay[i][j]+1, j, kay);
   cout << "Multiply M " << i << ", " << kay[i][j];
   cout << " and M " << (kay[i][j]+1) << ", " << j << endl;
}

void main(void)
{
   int q = 5;
   Make2DArray(c,q+1,q+1);
   Make2DArray(kay,q+1,q+1);
   
   for (int i = 1; i <= q; i++)
      for (int j = i; j <= q; j++)
         c[i][j] = 0;
   
   cout << "Optimal cost is " << C(1,q) << endl;
   
   cout << "cost matrix is" << endl;
   for (i=1; i<=q; i++) {
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
