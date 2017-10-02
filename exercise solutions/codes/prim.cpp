
// test Prim's min cost spanning tree algorithm

#include <iostream.h>
#include "lwg.h"

void main(void)
{
   LinkedWGraph<int> G(7);
   EdgeNode<int> t[7];
   int n = 7;
   int e, u, v, w;
   cout << "enter number of edges of 7 vertex graph" << endl;
   cin >> e;
   // get edges
   for (int i = 1; i <= e; i++) {
      cout << "enter edge " << i << endl;
      cin >> u >> v >> w;
      G.Add(u,v,w);}

   cout << "The input graph is" << endl;
   G.Output();

   if (G.Prim(t)) {
      cout << "The min spanning tree edges are" << endl;
      for (int i=0; i<n-1; i++)
         cout << t[i] << endl;}
   else  cout << "The graph is not connected" << endl;
}
