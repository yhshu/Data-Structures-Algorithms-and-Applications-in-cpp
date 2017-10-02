// time breadth first search

#include <iostream.h>
#include <time.h>
#include "lg.h"

clock_t start, finish;

void main(void)
{
   LinkedGraph G(50);
   int reach[51];
   int i, j, n = 50;
   for (i = 1; i <= n; i++)
      for (j = 1; j <= n; j++)
         if (i < j) G.Add(i,j);
   start = clock();
   for (int s = 1; s <= 50; s++) {
      for (j=1; j<=n; j++) reach[j] = 0;
      G.BFS(1, reach, 1);}
   finish = clock();
   cout << (finish - start)/CLK_TCK << endl;
   for (i=1; i<=n; i++)
      cout << reach[i] << ' ';
   cout << endl;
}
