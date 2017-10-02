// test branch-and-bound travelisng salesperson

#include <iostream.h>
#include "awd.h"

void main(void)
{
   AdjacencyWDigraph<int> G(7);
   int i, n = 7, p[8];
   cout << "enter number of edges of 7 vertex graph" << endl;
   int e, u, v, c;
   cin >> e;
   for (i =1; i <= e; i++) {
      cout << "enter edge " << i << endl;
      cin >> u >> v >> c;
      G.Add(u,v,c);}
   cout << "Cost = " << G.BBTSP(p) << endl;
   cout << "Optimal tour is" << endl;
   for (i = 1; i <= n; i++) cout << p[i] << ' ';
   cout << endl;
}
