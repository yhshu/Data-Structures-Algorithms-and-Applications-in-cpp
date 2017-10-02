// test graph::bipartiteCover

#include <iostream>
#include <iterator>
#include "linkedGraph.h"
#include "graph.h"

using namespace std;

void main(void)
{
   int n = 17;
   int e = 25;
   linkedGraph g(n);

   // input a test graph
   cout << "Enter a 25 edge 17 vertex bipartite graph" << endl;
   for (int i = 1; i <= e; i++)
   {
      cout << "enter edge " << i << endl;
      int u, v;
      cin >> u >> v;
      g.insertEdge(new unweightedEdge(u, v));
   }
   cout << "The undirected graph is" << endl;
   g.output(cout);

   int *l = new int [n + 1];
   cout << "\nEnter vertex labels" << endl;
   for (int i = 1; i <= n; i++)
      cin >> l[i];

   cout << "\nThe vertex labels are ";
   copy(l + 1, l + n + 1, ostream_iterator<int>(cout, "  "));
   cout << endl;

   int *c = new int [n];
   int size = g.bipartiteCover(l, c);
   if (size == -1) // no cover
      cout << "Did not find a cover" << endl;
   else
   {
      cout << "The cover is ";
      copy(c, c + size, ostream_iterator<int>(cout, "  "));
      cout << endl;
   }
}
