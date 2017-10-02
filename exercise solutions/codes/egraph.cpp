
// exercise 12.15


#include <iostream.h>
#include "xcept.h"
#include "make2db.h"


int OutDegree(int **a, int n, int i)
{// a[0:n-1][0:n-1] is the adjacency matrix of
 // an n vertex digraph.  Return the out-degree of
 // vertex i.
 // Throw OutOfBounds exception if i invalid.
   if (i < 1 || i > n) throw OutOfBounds();

   // out-degree is sum of row i-1
   int v = i - 1,   // row index into a
       degree = 0;  // out-degree of vertex i
   for (int j = 0; j < n; j++)
      degree += a[v][j];

   return degree;
}

int InDegree(int **a, int n, int i)
{// a[0:n-1][0:n-1] is the adjacency matrix of
 // an n vertex digraph.  Return the in-degree of
 // vertex i.
 // Throw OutOfBounds exception if i invalid.
   if (i < 1 || i > n) throw OutOfBounds();

   // in-degree is sum of column i-1
   int v = i - 1,   // column index into a
       degree = 0;  // in-degree of vertex i
   for (int j = 0; j < n; j++)
      degree += a[j][v];

   return degree;
}

int NumberOfEdges(int **a, int n)
{// a[0:n-1][0:n-1] is the adjacency matrix of
 // an n vertex digraph.  Return the number of
 // edges in the digraph.

   // answer is sum of adjacency matrix entries
   int sum = 0;
   for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
         sum += a[i][j];

   return sum;
}




void main(void)
{// Test with n = 5.
   int **a;
   int n = 5;
   Make2DArray(a,n,n);

   // initialize all entries
   for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
         a[i-1][j-1] = 0;
   // change some to 1
   a[0][3] = 1;
   a[3][4] = 1;
   a[4][2] = 1;
   a[2][1] = 1;
   a[1][3] = 1;
   a[2][4] = 1;

   // output all out-degrees
   for (i = 1; i <= n; i++)
         cout << "out-degree of vertex " << i << " is "
              << OutDegree(a,n,i) << endl;

   // output all in-degrees
   for (i = 1; i <= n; i++)
         cout << "in-degree of vertex " << i << " is "
              << InDegree(a,n,i) << endl;

   cout << "Number of edges is " << NumberOfEdges(a,n) << endl;

}
