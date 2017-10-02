// test adjacency matrix graph class

#include <iostream.h>
#include "ag.h"

void main(void)
{
   AdjacencyGraph G(7);
   int reach[8];
   int n = 7;
   cout << "enter number of edges in graph" << endl;
   int i, e, u, v;
   cin >> e;
   for (i =1; i <= e; i++) {
    cout << "enter edge " << i << endl;
    cin >> u >> v;
    G.Add(u,v);}
   for (i=1; i<=n; i++) reach[i] = 0;
   cout << "Doing bfs from vertex 1 labeling 1" << endl;
   G.BFS(1, reach, 1);
   cout << "Doing bfs from vertex 4 labeling 2" << endl;
   G.BFS(4, reach, 2);
   cout << "Reached values for vertices are" << endl;
   for (i=1; i<=n; i++)
      cout << reach[i] << ' ';
   cout << endl;
}
