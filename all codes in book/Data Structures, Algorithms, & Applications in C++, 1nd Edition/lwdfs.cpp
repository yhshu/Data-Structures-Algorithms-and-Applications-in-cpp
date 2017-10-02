// depth first search of linked weighted graphs

#include <iostream.h>
#include "lwg.h"

void main(void)
{
   LinkedWGraph<int> G(7);
   int reach[8];
   int n = 7;
   cout << "enter number of edges" << endl;
   int e, u, v, w;
   cin >> e;
   for (int i =1; i <= e; i++) {
      cout << "enter edge " << i << endl;
      cin >> u >> v >> w;
      G.Add(u,v,w);}
   for (int i = 1; i <= n; i++)
      reach[i] = 0;
   G.DFS(1, reach, 1);
   G.DFS(4, reach, 2);
   for (int i = 1; i <= n; i++)
      cout << reach[i] << ' ';
   cout << endl;
}
