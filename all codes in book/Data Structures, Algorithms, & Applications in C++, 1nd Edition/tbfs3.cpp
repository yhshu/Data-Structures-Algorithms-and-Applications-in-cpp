
// time breadth first search using a graph that is a chain

#include <iostream.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "lg.h"

void main(void)
{
   LinkedGraph G(100);
   int reach[101];
   int n = 100;
   for (int i = 1; i < n-1; i++)
      G.Add(i,i+1);
   clock_t start, finish;
   start = clock();
   for (int i = 1; i <= 4000; i++) {
      for (int j=1; j<=n; j++) reach[j] = 0;
      G.BFS(1, reach, 1);}
   finish = clock();
   cout << (finish - start)/CLK_TCK << endl;
   for (int i=1; i<=n; i++)
      cout << reach[i] << ' ';
   cout << endl;
}
