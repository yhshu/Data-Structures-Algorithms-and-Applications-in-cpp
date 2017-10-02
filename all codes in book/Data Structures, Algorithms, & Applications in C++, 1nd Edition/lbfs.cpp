// test breadth first search on linke adjacency list graphs

#include <iostream.h>
#include "lg.h"

void main(void)
{
   LinkedGraph G(7);
   int reach[8];
   int n = 7;
   cout << "enter number of edges" << endl;
   int e, u, v;
   cin >> e;
   for (int i = 1; i <= e; i++) {
    cout << "enter edge " << i << endl;
    cin >> u >> v;
    G.Add(u,v);}
   for (int i = 1; i <= n; i++)
      reach[i] = 0;
   G.BFS(1, reach, 1);
   G.BFS(4, reach, 2);
   for (int i = 1; i <= n; i++)
      cout << reach[i] << ' ';
   cout << endl;
}
