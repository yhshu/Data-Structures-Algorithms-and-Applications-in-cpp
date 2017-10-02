// test adjacency matrix weighted graphs

#include <iostream.h>
#include "awgraph.h"

void main(void)
{
   AdjacencyWGraph<int> G(4,100);
   cout << "Edges = " << G.Edges() << endl;
   G.Add(2,4,1).Add(1,3,2).Add(2,1,3).Add(1,4,4).Add(3,2,5);
   cout << "The graph is" << endl;
   G.Output();
   G.Delete(1,2);
   cout << "The graph after deleting (1,2) is" << endl;
   G.Output();
   cout << "Exist(3,1) = " << G.Exist(3,1) << endl;
   cout << "Degree(3) = " << G.Degree(3) << endl;
   cout << "Degree(1) = " << G.Degree(1) << endl;
   cout << "Edges = " << G.Edges() << endl;
}
