// test branch-and-bound max clique

#include <iostream.h>
#include "ag.h"

void main(void)
{
   AdjacencyGraph G(8);
   int n = 7, p[8];
   cout << "enter number of edges" << endl;
   int e, u, v;
   cin >> e;
   for (int i =1; i <= e; i++) {
      cout << "enter edge " << i << endl;
      cin >> u >> v;
      G.Add(u,v);}
   cout << "Size of max clique is "
        << G.BBMaxClique(p) << endl;
   cout << "Vertex selection vector is" << endl;
   for (i = 1; i <= n; i++)
      cout << p[i] << ' ';
   cout << endl;
}
