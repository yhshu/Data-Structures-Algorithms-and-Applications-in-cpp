// test graph::kruskal

#include <iostream>
#include "adjacencyWGraph.h"
#include "linkedWGraph.h"
#include "weightedEdge.h"

using namespace std;

void main(void)
{
   const int numberOfTypes = 2;
   // create a graph of each weighted undirected type
   graph<int>* g[numberOfTypes];
   int n = 7;
   g[0] = new adjacencyWGraph<int>(n);
   g[1] = new linkedWGraph<int>(n);

   // input a test graph
   cout << "Enter number of edges in 7 vertex graph" << endl;
   int e;
   cin >> e;
   for (int i = 1; i <= e; i++)
   {
      cout << "Enter weighted edge " << i << endl;
      int u, v, w;
      cin >> u >> v >> w;
      g[0]->insertEdge(new weightedEdge<int>(u, v, w));
      g[1]->insertEdge(new weightedEdge<int>(u, v, w));
   }

   cout << "The adjacency matrix is" << endl;
   g[0]->output(cout);
   cout << "\nThe linked lists are" << endl;
   g[1]->output(cout);

   // test kruskal
   weightedEdge<int> *edge = new weightedEdge<int> [n];
   cout << "Using cost-adjacency matrix" << endl;
   if (g[0]->kruskal(edge))
   {// found the spanning tree
      cout << "The min cost spanning tree edges are" << endl;
      for (int i = 0; i < n - 1; i++)
         cout << edge[i] << endl;
   }

   cout << "\nUsing linked-adjacency lists" << endl;
   if (g[1]->kruskal(edge))
   {// found the spanning tree
      cout << "The min cost spanning tree edges are" << endl;
      for (int i = 0; i < n - 1; i++)
         cout << edge[i] << endl;
   }
}
