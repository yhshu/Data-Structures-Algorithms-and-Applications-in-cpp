

#include <iostream.h>
#include "adgph2.h"

void main(void)
{
   AdjacencyDigraph G(1);
   G.Input();
   cout << "The digraph has " << G.Edges() << " edges." << endl;
   G.Output();
   cin >> G;
   cout << "The digraph has " << G.Edges() << " edges." << endl;
   cout << G << endl;
}
