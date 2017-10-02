
#include <iostream.h>
#include "ldig2.h"

void main(void)
{
   LinkedDigraph G(1);
   G.Input();
   cout << "The graph has " << G.Edges() << " edges." << endl;
   G.Output();
   cin >> G;
   cout << "The graph has " << G.Edges() << " edges." << endl;
   cout << G << endl;
}
