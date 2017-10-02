
// test adjacencyGraph::maxProfitBBMaxClique

#include <iostream>
#include <iterator>
#include "adjacencyGraph.h"
#include "unweightedEdge.h"

using namespace std;

void main(void)
{
   // input a test graph
   cout << "Enter number of vertices and edges" << endl;
   int n, e;
   cin >> n >> e;
   adjacencyGraph g(n);

   for (int i = 1; i <= e; i++)
   {
      cout << "Enter edge " << i << endl;
      int u, v;
      cin >> u >> v;
      g.insertEdge(new unweightedEdge(u, v));
   }
   cout << "The undirected graph is" << endl;
   g.output(cout);

   int *c = new int [n + 1];
   cout << "The max clique size is " << g.maxProfitBBMaxClique(c) << endl;
   cout << "The vertex selection vector is ";
   copy(c + 1, c + n + 1, ostream_iterator<int>(cout, "  "));
   cout << endl;
}
