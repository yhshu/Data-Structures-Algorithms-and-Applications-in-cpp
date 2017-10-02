// test of linked adjacency list weighted graph class

#include <iostream.h>
#include "lwgraph.h"

void main(void)
{
   LinkedWGraph<int> G(4);
   cout << "Edges = " << G.Edges() << endl;
   G.Add(2,4,1).Add(1,3,2).Add(2,1,4).Add(1,4,4).Add(3,2,5);
   G.Output();
   G.Delete(1,2);
   cout << "Edge (1,2) deleted" << endl;
   G.Output();
   cout << "Exist(3,1) = " << G.Exist(3,1) << endl;
   cout << "Degree(3) = " << G.Degree(3) << endl;
   cout << "Degree(1) = " << G.Degree(1) << endl;
   cout << "Edges = " << G.Edges() << endl;
}
