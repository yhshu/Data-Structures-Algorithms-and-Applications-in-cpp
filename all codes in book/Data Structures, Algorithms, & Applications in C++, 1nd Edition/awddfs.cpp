// test depth first search on adjacency matrix weighted digraphs

#include <iostream.h>
#include "awd.h"

void main(void)
{
   AdjacencyWDigraph<int> G(7);
   int reach[8];
   int n = 7;
   cout << "enter number of edges" << endl;
   int e, u, v, w;
   cin >> e;
   for (int i =1; i <= e; i++) {
    cout << "enter edge " << i << endl;
    cin >> u >> v >> w;
    G.Add(u,v,w);}
   for (i=1; i<=n; i++) reach[i] = 0;
   G.DFS(1, reach, 1);
   G.DFS(4, reach, 2);
   G.DFS(7, reach, 3);
   for (i=1; i<=n; i++)
      cout << reach[i] << ' ';
   cout << endl;
}
