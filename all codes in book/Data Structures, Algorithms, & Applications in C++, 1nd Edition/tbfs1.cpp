// time breadth first search

#include <iostream.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "ag.h"

void main(void)
{
   AdjacencyGraph G(50);
   int reach[51];
   int i, j, n = 50;
   for (i = 1; i <= n; i++)
      for (j = 1; j <= n; j++)
         if (i < j) G.Add(i,j);
   clock_t start, finish;
   start = clock();
   for (i = 1; i <= 2000; i++) {
      for (j=1; j<=n; j++) reach[j] = 0;
      G.BFS(1, reach, 1);}
   finish = clock();
   cout << (finish - start)/CLK_TCK << endl;
   for (i=1; i<=n; i++)
      cout << reach[i] << ' ';
   cout << endl;
}
