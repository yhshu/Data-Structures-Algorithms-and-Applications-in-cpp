
#include <iostream.h>
#include "awdgph2.h"
#include "adjiter.h"

void main(void)
{
   AdjacencyWDigraph<int> G(1);
   G.Input();
   cout << "The graph has " << G.Edges() << " edges." << endl;
   G.Output();

   // output adjacent vertices
   int n = G.Vertices();
   AdjacencyIterator<int> x;
   for (int i = 1; i <= n; i++) {
      cout << "The vertices adjacent to vertex "
           << i << " are" << endl;
      int v = x.Begin(G,i);
      while (v) {
         cout << v << "  ";
         v = x.NextVertex();
         }
      cout << endl;
      }

   cin >> G;
   cout << "The graph has " << G.Edges() << " edges." << endl;
   cout << G << endl;

   // output adjacent vertices
   n = G.Vertices();
   for (i = 1; i <= n; i++) {
      cout << "The vertices adjacent to vertex "
           << i << " are" << endl;
      int v = x.Begin(G,i);
      while (v) {
         cout << v << "  ";
         v = x.NextVertex();
         }
      cout << endl;
      }

}
