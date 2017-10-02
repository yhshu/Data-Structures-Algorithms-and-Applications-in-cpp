// test linked adjacency list directed graph class

#include <iostream.h>
#include "ldigraph.h"

void main(void)
{
   LinkedDigraph G(4);
   cout << "Edges = " << G.Edges() << endl;
   G.Add(2,4).Add(1,3).Add(2,1).Add(1,4).Add(4,2);
   cout << "The graph is" << endl;
   G.Output();
   G.Delete(2,4);
   cout << "The graph after deleting <2,4> is" << endl;
   G.Output();
   try {G.Delete(3,4);
        cout << "Edge <3,4> has been deleted" << endl;}
   catch (...)
        {cout << "Deletion of <3,4> failed" << endl;}
   cout << "Exist(3,1) = " << G.Exist(3,1) << endl;
   cout << "InDegree(3) = " << G.InDegree(3) << endl;
   cout << "OutDegree(1) = " << G.OutDegree(1) << endl;
   cout << "Edges = " << G.Edges() << endl;
}
