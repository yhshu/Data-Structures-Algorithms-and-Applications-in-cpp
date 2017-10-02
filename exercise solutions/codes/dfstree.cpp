

// find a depth-first spanning tree

#include<iostream.h>
#include "lg2.h"
#include "edge.h"

void main(void)
{
   LinkedGraph G(0);
   Edge DT[100];

   // try three graphs
   for (int j = 1; j <= 3; j++) {
      G.Input();
      cout << "The input graph is" << endl;
      G.Output();

      if (G.DSpanningTree(j,DT)) {
         cout << "The depth-first spanning tree edges are" << endl;
         for (int i = 0; i <= G.Vertices()-2; i++)
             cout << DT[i] << ' ' ;
             cout << endl;}
      else cout << "The graph has no spanning tree" << endl;
      }
}
