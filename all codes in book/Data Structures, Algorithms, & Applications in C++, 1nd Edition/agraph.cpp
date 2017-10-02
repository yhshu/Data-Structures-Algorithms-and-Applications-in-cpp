// test adjacency matrix undirected graphs

#include <iostream.h>
#include "agraph.h"

void main(void)
{
   AdjacencyGraph G(4);
   cout << "Edges = " << G.Edges() << endl;
   G.Add(2,4).Add(1,3).Add(2,1).Add(1,4).Add(3,2);
   cout << "The graph is" << endl;
   G.Output();
   G.Delete(3,1);
   cout << "The graph after deleting (3,1) is" << endl;
   G.Output();
   cout << "Exist(3,1) = " << G.Exist(3,1) << endl;
   cout << "G.Degree(2) = " << G.Degree(2) << endl;
   cout << "G.Edges() = " << G.Edges() << endl;
}
