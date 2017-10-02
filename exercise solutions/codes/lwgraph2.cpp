

#include <iostream.h>
#include "lwgraph2.h"

void main(void)
{
   LinkedWGraph<int> G(1);
   G.Input();
   cout << "The graph has " << G.Edges() << " edges." << endl;
   G.Output();
   cin >> G;
   cout << "The graph has " << G.Edges() << " edges." << endl;
   cout << G << endl;
}
