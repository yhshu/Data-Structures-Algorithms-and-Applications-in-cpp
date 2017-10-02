// single source shortest paths

#include <iostream.h>
#include "awd.h"

void Path(int p[], int s, int i)
{// Output shortest path from s to i.
   if (i != s && !p[i]) {// no path
      cout << "There is no path from vertex "
           << s << " to vertex " << i << endl;
      return;
      }

   // there is a shortest path to i
   // construct it backwards from i to s
   cout << "Shortest path from vertex "
        << s << " to vertex " << i
        << " is the reverse of " << i;
   while (i != s) {
      // move back one vertex
      i = p[i];
      cout << " " << i;
      }
   cout << endl;
}



void main(void)
{
   AdjacencyWDigraph<int> G(5);
   int dist[6], p[6];
   int n = 5;
   cout << "enter number of edges of 5 vertex digraph" << endl;
   int e, u, v, w;
   cin >> e;
   // input edges
   for (int i = 1; i <= e; i++) {
      cout << "enter edge " << i << endl;
      cin >> u >> v >> w;
      G.Add(u,v,w);}

   cout << "The input graph is" << endl;
   G.Output();

   G.ShortestPaths(1, dist, p);

   cout << "dist[i] and p[i] are" << endl;
   for (i = 1; i <= n; i++)
      cout << dist[i] << ' ' << p[i] << endl;

   // output shortest paths
   for (i = 1; i <= n; i++)
      Path(p,1,i);

}
