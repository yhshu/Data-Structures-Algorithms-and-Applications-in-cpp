// test breadth first search of linked adjacency list directed graphs

#include <iostream.h>
#include "ldg.h"

void main(void)
{
   LinkedDigraph G(7);
   int reach[8];
   int i, n = 7;
   cout << "enter number of edges" << endl;
   int e, u, v;
   cin >> e;
   for (i =1; i <= e; i++) {
      cout << "enter edge " << i << endl;
      cin >> u >> v;
      G.Add(u,v);}
   for (i=1; i<=n; i++) reach[i] = 0;
   G.BFS(1, reach, 1);
   G.BFS(4, reach, 2);
   for (i=1; i<=n; i++)
      cout << reach[i] << ' ';
   cout << endl;
}
