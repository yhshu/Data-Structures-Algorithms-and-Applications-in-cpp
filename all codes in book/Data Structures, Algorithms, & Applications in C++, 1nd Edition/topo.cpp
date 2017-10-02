// topological sort

#include <iostream.h>
#include "ad.h"

void main(void)
{
   AdjacencyDigraph G(5);
   int V[6];
   int n = 5;

   // input digraph
   cout << "enter number of edges of 5 vertex digraph" << endl;
   int e, u, v;
   cin >> e;
   for (int i = 1; i <= e; i++) {
      cout << "enter edge " << i << endl;
      cin >> u >> v;
      G.Add(u,v);}

   cout << "The network's adjacency matrix is" << endl;
   G.Output();

   cout << "Return status = " << G.Topological(V) << endl;
   cout << "The topological order is" << endl;
   for (i = 0; i <= n-1; i++)
      cout << V[i] << endl;
}
