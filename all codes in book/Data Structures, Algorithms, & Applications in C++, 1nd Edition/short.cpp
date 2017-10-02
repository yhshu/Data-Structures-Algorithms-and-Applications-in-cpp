// single source shortest paths

#include <iostream.h>
#include "awd.h"

void main(void)
{
   AdjacencyWDigraph<int> G(5);
   int dist[6], p[6];
   int n = 5;
   cout << "enter number of edges of 5 vertex digraph" << endl;
   int e, u, v, w;
   cin >> e;
   // input edges
   for (int i =1; i <= e; i++) {
      cout << "enter edge " << i << endl;
      cin >> u >> v >> w;
      G.Add(u,v,w);}

   cout << "The input graph is" << endl;
   G.Output();

   G.ShortestPaths(1, dist, p);

   cout << "dist[i] and p[i] are" << endl;
   for (i=1; i<=n; i++)
      cout << dist[i] << ' ' << p[i] << endl;
}
