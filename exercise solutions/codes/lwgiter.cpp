
#include <iostream.h>
#include "lwdgph2.h"
#include "lwgiter.h"

void main(void)
{
   LinkedWDigraph<int> G(1);
   G.Input();
   cout << "The graph has " << G.Edges() << " edges." << endl;
   G.Output();

   // output adjacent vertices
   int n = G.Vertices();
   LinkedWeightedIterator<int> x;
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
