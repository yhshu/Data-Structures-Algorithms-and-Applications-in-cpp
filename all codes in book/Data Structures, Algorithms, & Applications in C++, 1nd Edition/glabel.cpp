// label components of an undirected graph

#include <iostream.h>
#include "ag.h"

void main(void)
{
   AdjacencyGraph G(7);
   cout << "enter number of edges" << endl;
   int i, e, u, v;
   cin >> e;
   for (i =1; i <= e; i++) {
      cout << "enter edge " << i << endl;
      cin >> u >> v;
      G.Add(u,v);}
   int L[8];
   cout << "Components = " << G.LabelComponents(L) << endl;
   for (i =1; i <= e; i++) cout << L[i] << ' ';
   cout << endl;
}
