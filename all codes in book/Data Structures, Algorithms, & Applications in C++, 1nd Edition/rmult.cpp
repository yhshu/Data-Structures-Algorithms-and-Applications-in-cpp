// dynamic programming recursive matrix multiplication chains

#include <iostream.h>
#include "make2db.h"

int r[7] = {0, 10, 5, 1, 10, 2, 10};
int **kay;


int C(int i, int j)
{// Return c(i,j) and compute kay(i,j) = kay[i][j].
   if (i == j) return 0;  // one matrix
   if (i == j - 1) {      // two matrices
      kay[i][i+1] = i;
      return r[i]*r[i+1]*r[i+2];}

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
   Make2DArray(kay,q+1,q+1);
   cout << "Optimal cost is " << C(1,q) << endl;
   Traceback(1,q,kay);
}
