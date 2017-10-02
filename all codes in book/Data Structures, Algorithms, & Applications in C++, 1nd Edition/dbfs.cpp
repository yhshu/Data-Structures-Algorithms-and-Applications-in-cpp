// test depth first search of adjacency matrix digraphs

#include <iostream.h>
#include "ad.h"
void main(void)
{
   AdjacencyDigraph G(7);
   int reach[8];
   int n = 7;
   cout << "enter number of edges in digraph" << endl;
   int e, u, v;
   cin >> e;
   for (int i =1; i <= e; i++) {
      cout << "enter edge " << i << endl;
      cin >> u >> v;
      G.Add(u,v);}
   for (int i=1; i<=n; i++)
      reach[i] = 0;
   cout << "Doing bfs from vertex 1 labeling 1" << endl;
   G.BFS(1, reach, 1);
   cout << "Doing bfs from vertex 4 labeling 2" << endl;
   G.BFS(4, reach, 2);
   cout << "Doing bfs from vertex 2 labeling 3" << endl;
   G.BFS(7, reach, 3);
   cout << "Reached values for vertices are" << endl;
   for (int i=1; i<=n; i++)
      cout << reach[i] << ' ';
   cout << endl;
}
