// find a path in an undirected graph

#include <iostream.h>
#include "ag.h"

void main(void)
{
   AdjacencyGraph G(7);
   int path[7];
   cout << "enter number of edges" << endl;
   int i, e, u, v;
   cin >> e;
   for (i =1; i <= e; i++) {
      cout << "enter edge " << i << endl;
      cin >> u >> v;
      G.Add(u,v);}
   int length;
   bool x = G.FindPath(1,3,length,path);
   cout << "FindPath = " << x << endl;
   cout << "length = " << length << endl;
   for (i=0; i<=length; i++)
      cout << path[i] << ' ';
   cout << endl;
   x = G.FindPath(4,6,length,path);
   cout << "FindPath = " << x << endl;
   cout << "length = " << length << endl;
   for (i=0; i<=length; i++)
      cout << path[i] << ' ';
   cout << endl;
   x = G.FindPath(1,6,length,path);
   cout << "FindPath = " << x << endl;
   cout << "length = " << length << endl;
   for (i=0; i<=length; i++)
      cout << path[i] << ' ';
   cout << endl;
}
