// test graph::bellmanFord

#include <iostream>
#include "graph.h"
#include "adjacencyWDigraph.h"
#include "adjacencyWGraph.h"
#include "linkedWDigraph.h"
#include "linkedWGraph.h"

using namespace std;

void main(void)
{
   const int numberOfTypes = 4;
   const noEdge = 100;
   // create a graph of each weighted type
   graph<int> *g[numberOfTypes];

   // input a test undirected graph
   cout << "Enter number of vertices and edges" << endl;
   int n, e;
   cin >> n >> e;
   g[0] = new adjacencyWGraph<int>(n, noEdge);
   g[1] = new linkedWGraph<int>(n);
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

   // input a test directed graph
   cout << "Enter number of vertices and edges" << endl;
   cin >> n >> e;
   g[2] = new adjacencyWDigraph<int>(n, noEdge);
   g[3] = new linkedWDigraph<int>(n);
   for (int i = 1; i <= e; i++)
   {
      cout << "Enter weighted edge " << i << endl;
      int u, v, w;
      cin >> u >> v >> w;
      g[2]->insertEdge(new weightedEdge<int>(u, v, w));
      g[3]->insertEdge(new weightedEdge<int>(u, v, w));
   }

   cout << "\nThe weighted digraph is" << endl;
   g[2]->output(cout);

   // test bellmanFord
   for (int s = 0; s < numberOfTypes; s++)
   {
      int *dist = new int [n + 1];
      int *p = new int [n + 1];
      g[s]->bellmanFord(1, dist, p);
      cout << "The dist and p values for the graph are" << endl;
      for (int i = 1; i <= g[s]->numberOfVertices(); i++)
         cout << dist[i] << " " << p[i] << endl;
   }
}
