#include <iostream.h>
#include "awdgph2.h"

void main(void)
{
   AdjacencyWDigraph<int> G(1);
   G.Input();
   cout << "The graph has " << G.Edges() << " edges." << endl;
   G.Output();
   cin >> G;
   cout << "The graph has " << G.Edges() << " edges." << endl;
   cout << G << endl;
}
