// test adjacency matrix weighted digraphs

#include <iostream.h>
#include "awdgraph.h"

void main(void)
{
   AdjacencyWDigraph<int> G(4,100);
   cout << "Edges = " << G.Edges() << endl;
   G.Add(2,4,1).Add(1,3,2).Add(2,1,3).Add(1,4,4).Add(4,2,5);
   cout << "The graph is" << endl;
   G.Output();
   G.Delete(2,1);
   cout << "The graph after deleting <2,1> is" << endl;
   G.Output();
   cout << "Exist(3,1) = " << G.Exist(3,1) << endl;
   cout << "InDegree(3) = " << G.InDegree(3) << endl;
   cout << "OutDegree(1) = " << G.OutDegree(1) << endl;
   cout << "Edges = " << G.Edges() << endl;
}
