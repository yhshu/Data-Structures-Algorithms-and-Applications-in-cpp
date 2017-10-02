// test linked adjacency list graph class

#include <iostream.h>
#include "lgraph.h"

void main(void)
{
   LinkedGraph G(4);
   cout << "Edges = " << G.Edges() << endl;
   G.Add(2,4).Add(1,3).Add(2,1).Add(1,4).Add(3,2);
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
   cout << "Degree(3) = " << G.Degree(3) << endl;
   cout << "Degree(1) = " << G.Degree(1) << endl;
   cout << "Edges = " << G.Edges() << endl;
}
