// test bipartite graph cover

#include <iostream.h>
#include "lg.h"

void main(void)
{
   LinkedGraph G(17);
   int n = 17;
   int e = 25, u, v;
   // input graph
   cout << "Enter 25 edges of a 17 vertex graph" << endl;
   for (int i =1; i <= e; i++) {
      cin >> u >> v;
      G.Add(u,v);}

   cout << "The graph is" << endl;
   G.Output();

   int L[18], C[18], m;
   cout << "Enter vertex labels" << endl;
   for (i = 1; i <= n; i++)
      cin >> L[i];

   cout << "The vertex labels are" << endl;
   for (i = 1; i <= n; i++)
      cout << L[i] << " ";
   cout << endl;

   cout << "Cover Status = " << G.BipartiteCover(L, C, m) << endl; 
   cout << "The cover is" << endl;
   for (i = 0; i < m; i++)
      cout << C[i] << ' ' ;
   cout << endl;
}
