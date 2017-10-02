// check if a graph is bipartite

#include<iostream.h>
#include "lg4.h"

void main(void)
{
   LinkedGraph G(0);
   int L[100];

   // try two graphs
   for (int j = 1; j <= 2; j++) {
      G.Input();
      cout << "The input graph is" << endl;
      G.Output();

      if (G.Bipartite(L)) {
         cout << "The graph is bipartite" << endl;
         cout << "The vertex labels are" << endl;
         for (int i = 1; i <= G.Vertices(); i++)
             cout << L[i] << ' ' ;
             cout << endl;}
      else cout << "The graph is not bipartite" << endl;
      }
}
