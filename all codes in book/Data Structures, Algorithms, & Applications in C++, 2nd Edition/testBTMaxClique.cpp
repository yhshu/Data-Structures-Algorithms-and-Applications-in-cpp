// test adjacencyGraph::btMaxClique

#include <iostream>
#include <iterator>
#include "adjacencyGraph.h"

using namespace std;

void main(void)
{
   const int n = 7;
   adjacencyGraph g(n);

   // input a test graph
   cout << "Enter number of edges in 7 vertex graph"<< endl;
   int e;
   cin >> e;
   for (int i = 1; i <= e; i++)
   {
      cout << "Enter unweighted edge " << i << endl;
      int u, v;
      cin >> u >> v;
      g.insertEdge(new unweightedEdge(u, v));
   }

   cout << "The undirected graph is" << endl;
   g.output(cout);

   // test btMaxClique
   int *v = new int [n + 1];
   cout << "\nMax Clique size is " << g.btMaxClique(v) << endl;
   cout << "\nSolution vector is ";
   copy(v + 1, v + n + 1, ostream_iterator<int>(cout, "  "));
   cout << endl;
}
