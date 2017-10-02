// test graph connectedness

#include <iostream.h>
#include "ag.h"

void main(void)
{
   AdjacencyGraph G(7);
   cout << "enter number of edges" << endl;
   int e, u, v;
   cin >> e;
   for (int i =1; i <= e; i++) {
      cout << "enter edge " << i << endl  ;
      cin >> u >> v;
      G.Add(u,v);}
   cout << "Connected = " << G.Connected() << endl;
}
