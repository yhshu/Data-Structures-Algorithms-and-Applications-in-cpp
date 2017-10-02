// test graph::dfs and graph::bfs

#include <iostream>
#include "graph.h"
#include "adjacencyWDigraph.h"
#include "adjacencyDigraph.h"
#include "adjacencyWGraph.h"
#include "adjacencyGraph.h"
#include "linkedWDigraph.h"
#include "linkedDigraph.h"
#include "linkedWGraph.h"
#include "linkedGraph.h"
#include "weightedEdge.h"
#include "unweightedEdge.h"

using namespace std;

void main(void)
{
   int numberOfTypes = 4;
   // create a graph of each type
   graph<bool>* g[4];
   graph<int>* h[4];
   g[0] = new adjacencyGraph(7);
   g[1] = new adjacencyDigraph(7);
   g[2] = new linkedGraph(7);
   g[3] = new linkedDigraph(7);
   h[0] = new adjacencyWGraph<int>(7);
   h[1] = new adjacencyWDigraph<int>(7);
   h[2] = new linkedWGraph<int>(7);
   h[3] = new linkedWDigraph<int>(7);
   int reach[8];
   int n = 7;   // number of vertices

   // input a test graph
   cout << "Enter number of edges in graph" << endl;
   int e, u, v, w;
   cin >> e;
   for (int i = 1; i <= e; i++)
   {
      cout << "Enter weighted edge " << i << endl;
      cin >> u >> v >> w;
      for (int j = 0; j < numberOfTypes; j++)
      {
         g[j]->insertEdge(new unweightedEdge(u, v));
         h[j]->insertEdge(new weightedEdge<int>(u, v, w));
      }
   }

   // output the test graphs
   for (int i = 0; i < numberOfTypes; i++)
   {
      cout << "Graph " << i << " is" << endl;
      cout << "Number of Vertices = " << g[i]->numberOfVertices() << endl;
      cout << "Number of Edges = " << g[i]->numberOfEdges() << endl;
      g[i]->output(cout);
      cout << endl << endl;
   }
   for (int i = 0; i < numberOfTypes; i++)
   {
      cout << "Graph " << i + numberOfTypes << " is" << endl;
      cout << "Number of Vertices = " << h[i]->numberOfVertices() << endl;
      cout << "Number of Edges = " << h[i]->numberOfEdges() << endl;
      h[i]->output(cout);
      cout << endl << endl;
   }

   // test bfs on all graph types
   cout << "Doing bfs" << endl;
   for (int i = 0; i < numberOfTypes; i++)
   {
      for (int j = 1; j <= n; j++)
         reach[j] = 0;
      g[i]->bfs(1, reach, 1);
      g[i]->bfs(4, reach, 2);
      cout << "Reached values for vertices are ";
      for (int j = 1; j <= n; j++)
         cout << reach[j] << " " ;
      cout << endl;
   }
   for (int i = 0; i < numberOfTypes; i++)
   {
      for (int j = 1; j <= n; j++)
         reach[j] = 0;
      h[i]->bfs(1, reach, 1);
      h[i]->bfs(4, reach, 2);
      cout << "Reached values for vertices are ";
      for (int j = 1; j <= n; j++)
         cout << reach[j] << " " ;
      cout << endl;
   }
   cout << endl;

   // test dfs on all graph types
   cout << "Doing dfs" << endl;
   for (int i = 0; i < numberOfTypes; i++)
   {
      for (int j = 1; j <= n; j++)
         reach[j] = 0;
      g[i]->dfs(1, reach, 1);
      g[i]->dfs(4, reach, 2);
      cout << "Reached values for vertices are ";
      for (int j = 1; j <= n; j++)
         cout << reach[j] << " " ;
      cout << endl;
   }
   for (int i = 0; i < numberOfTypes; i++)
   {
      for (int j = 1; j <= n; j++)
         reach[j] = 0;
      h[i]->dfs(1, reach, 1);
      h[i]->dfs(4, reach, 2);
      cout << "Reached values for vertices are ";
      for (int j = 1; j <= n; j++)
         cout << reach[j] << " " ;
      cout << endl;
   }
   cout << endl;
}
