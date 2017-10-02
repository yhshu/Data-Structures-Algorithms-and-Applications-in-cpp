// test breadth first search for linked adjacency list
// weighted directed graphs

#include <iostream.h>
#include "lwdg.h"

void main(void)
{
   LinkedWDigraph<int> G(7);
   int reach[8];
   int n = 7;
   cout << "enter number of edges in weighted digraph" << endl;
   int i, e, u, v, w;
   cin >> e;
   for (i = 1; i <= e; i++) {
      cout << "enter edge " << i << endl;
      cin >> u >> v >> w;
      G.Add(u,v,w);}
   for (i =1 ; i <= n; i++)
      reach[i] = 0;
   cout << "Doing bfs from vertex 1 labeling 1" << endl;
   G.BFS(1, reach, 1);
   cout << "Doing bfs from vertex 4 labeling 2" << endl;
   G.BFS(4, reach, 2);
   cout << "Doing bfs from vertex 7 labeling 3" << endl;
   G.BFS(7, reach, 3);
   cout << "Reached values for vertices are" << endl;
   for (i = 1; i <= n; i++)
      cout << reach[i] << ' ';
   cout << endl;
}
