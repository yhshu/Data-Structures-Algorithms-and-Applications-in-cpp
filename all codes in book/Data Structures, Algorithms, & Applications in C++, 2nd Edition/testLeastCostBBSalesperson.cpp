// test adjacencyWDigraph::leastCostBBSalesperson, branch & bound algorithm

#include <iostream>
#include <iterator>
#include "adjacencyWDigraph.h"
#include "adjacencyWGraph.h"
#include "weightedEdge.h"

using namespace std;

void main(void)
{
   const int numberOfTypes = 2;
   // create a graph of each adjacency weighted type
   adjacencyWDigraph<int> *g[numberOfTypes];

   // input a test graph
   cout << "Enter number of vertices and edges"<< endl;
   int n, e;
   cin >> n >> e;
   g[0] = new adjacencyWGraph<int>(n, 100);
   g[1] = new adjacencyWDigraph<int>(n, 100);
   for (int i = 1; i <= e; i++)
   {
      cout << "Enter weighted edge " << i << endl;
      int u, v, w;
      cin >> u >> v >> w;
      g[0]->insertEdge(new weightedEdge<int>(u, v, w));
      g[1]->insertEdge(new weightedEdge<int>(u, v, w));
   }

   cout << "The weighted undirected graph is" << endl;
   g[0]->output(cout);
   cout << "\nThe weighted digraph is" << endl;
   g[1]->output(cout);

   // test leastCostBBSalesperson
   int *p = new int [n + 1];
   cout << "\nThe length of the shortest tour is "
        << g[0]->btSalesperson(p) << endl;
   cout << "The shortest tour is ";
   copy(p + 1, p + n + 1, ostream_iterator<int>(cout, "  "));
   cout << endl;

   cout << "\nThe length of the shortest tour is "
        << g[1]->leastCostBBSalesperson(p) << endl;
   cout << "The shortest tour is ";
   copy(p + 1, p + n + 1, ostream_iterator<int>(cout, "  "));
   cout << endl;
}
