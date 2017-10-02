// test adjacencyWDigraph::shortestPaths */
#include <iostream>
#include "adjacencyWDigraph.h"
#include "adjacencyWGraph.h"

using namespace std;


void main(void)
{
   const int numberOfTypes = 2;
   // create a graph of each adjacency weighted type
   adjacencyWDigraph<int> *g[numberOfTypes];

   // input a test graph
   cout << "Enter number of vertices and edges" << endl;
   int n, e;
   cin >> n >> e;
   g[0] = new adjacencyWGraph<int>(n);
   g[1] = new adjacencyWDigraph<int>(n);
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

   // test shortestPaths
   int *dist = new int [n + 1];
   int *p = new int [n + 1];
   g[0]->shortestPaths(1, dist, p);
   cout << "The dist and p values for the undirected graph are" << endl;
   for (int i = 1; i <= n; i++)
      cout << dist[i] << " " << p[i] << endl;

   g[1]->shortestPaths(1, dist, p);
   cout << "\nThe dist and p values for the directed graph are" << endl;
   for (int i = 1; i <= n; i++)
      cout << dist[i] << " " << p[i] << endl;
}
