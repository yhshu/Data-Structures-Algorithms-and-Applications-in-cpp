// test adjacency matrix directed graphs

#include <iostream.h>
#include "adigraph.h"

void main(void)
{
   AdjacencyDigraph G(4);
   cout << "Edges = " << G.Edges() << endl;
   G.Add(2,4).Add(1,3).Add(2,1).Add(1,4).Add(4,2);
   cout << "The graph is" << endl;
   G.Output();
   G.Delete(1,3);
   cout << "The graph after deleting <1,3> is" << endl;
   G.Output();
   cout << "Exist(3,1) = " << G.Exist(3,1) << endl;
   cout << "InDegree(3) = " << G.InDegree(3) << endl;
   cout << "OutDegree(1) = " << G.OutDegree(1) << endl;
   cout << "Edges = " << G.Edges() << endl;
}
