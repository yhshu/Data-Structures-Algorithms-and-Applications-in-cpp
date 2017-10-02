// iterative version of dynamic programming solution for
// the matrix multiplication chains problem


#include <iostream>
#include "make2dArray.h"

using namespace std;

// global variables
int *r;      // r[i] is number of rows in matrix i
int **kay;   // recurrence selector
int **c;

void matrixChain(int q)
{// Compute costs and kay for all Mij's iteratively.
 // r[] is array of dimensions; q is number of matrices;
 // c is cost matrix; kay is recurrence selector.

   // initialize c[i][i], c[i][i+1], and kay[i][i+1]
   for (int i = 1; i < q; i++)
   {
      c[i][i] = 0;
      c[i][i + 1] = r[i] * r[i + 1] * r[i + 2];
      kay[i][i + 1] = i;
   }
   c[q][q] = 0;
   
   // compute remaining c's and kay's
   for (int s = 2; s < q; s++)
      for (int i = 1; i <= q - s; i++)
      {// min term for k = i
         c[i][i+s] = c[i][i] + c[i + 1][i + s]
                     + r[i] * r[i + 1] * r[i + s + 1];
         kay[i][i + s] = i;

         // remaining min terms
         for (int k = i + 1; k < i + s; k++)
         {
            int t = c[i][k] + c[k + 1][i + s]
                    + r[i] * r[k + 1] * r[i + s + 1];
            if (t < c[i][i + s])
            {// smaller min term, update c and kay
               c[i][i + s] = t;
               kay[i][i + s] = k;
            }
         }      
      }
}

void traceback(int i, int j)
{// Output best way to compute Mij.
   if (i == j)  // only one matrix
      return;
   traceback(i, kay[i][j]);
   traceback(kay[i][j] + 1, j);
   cout << "Multiply M " << i << ", " << kay[i][j] <<
           " and M " << (kay[i][j] + 1) << ", " << j << endl;
}

void main(void)
{
   // initialize
   cout << "Enter number of matrices" << endl;
   int q;
   cin >> q;
   r = new int [q + 2];
   make2dArray(kay, q + 1, q + 1);
   make2dArray(c, q + 1, q + 1);

   // input matrix data
   for (int i = 1; i <= q; i++)
   {
      cout << "Enter number of rows in matrix " << i << endl;
      cin >> r[i];
   }
   cout << "Enter number of columns in matrix " << q << endl;
   cin >> r[q + 1];

   // compute cost of best way to multiply
   matrixChain(q);

   cout << "Minimum cost is " << c[1][q] << endl;

   // output optimal multiplication sequence
   traceback(1, q);
}
