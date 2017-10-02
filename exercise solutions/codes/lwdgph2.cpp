


#include <iostream.h>
#include "lwdgph2.h"

void main(void)
{
   LinkedWDigraph<int> G(1);
   G.Input();
   cout << "The graph has " << G.Edges() << " edges." << endl;
   G.Output();
   cin >> G;
   cout << "The graph has " << G.Edges() << " edges." << endl;
   cout << G << endl;
}
