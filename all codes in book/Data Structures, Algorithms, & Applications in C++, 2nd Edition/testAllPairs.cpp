// test AdjacencyWDigraph::allPairs 

#include <iostream>
#include "adjacencyWDigraph.h"
#include "adjacencyWGraph.h"

using namespace std;



template <class T>
void outputPath(T **c, int **kay, T noEdge, int i, int j)
{// Output shortest path from i to j.
   if (c[i][j] == noEdge)
      cout << "There is no path from " << i << " to " << j << endl;
   else
   {
      cout << "The path is " << i << " ";
      outputPath(kay, i, j);
      cout << endl;
   }
}

void outputPath(int **kay, int i, int j)
{// Actual code to output i to j path.
   if (i == j)
      return;
   if (kay[i][j] == 0)  // no intermediate vertices on path
      cout << j << " ";
   else
   {// kay[i][j] is an intermediate vertex on the path
      outputPath(kay, i, kay[i][j]);
      outputPath(kay, kay[i][j], j);
   }
}

void main(void)
{
   const int numberOfTypes = 2;
   // create a graph of each adjacency weighted type
   adjacencyWDigraph<int> *g[numberOfTypes];
   const int n = 5;
   const noEdge = 100;
   g[0] = new adjacencyWGraph<int>(n, noEdge);
   g[1] = new adjacencyWDigraph<int>(n, noEdge);

   // input a test graph
   cout << "Enter number of edges in 5 vertex graph" << endl;
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

   cout << "The weighted undirected graph is" << endl;
   g[0]->output(cout);
   cout << "\nThe weighted digraph is" << endl;
   g[1]->output(cout);

   // test allPairs
   int **c, **kay;
   make2dArray(c, n + 1, n + 1);
   make2dArray(kay, n + 1, n + 1);
   // first do for g[0]
   cout << "\nWorking on weighted undirected graph" << endl;
   g[0]->allPairs(c, kay);
   cout << "Cost matrix is" << endl;
   for (int i = 1; i <= n; i++)
   {
      for (int j = 1; j <= n; j++)
         cout << c[i][j] << " ";
      cout << endl;
   }
   
   cout << "\nKay matrix is" << endl;
   for (int i = 1; i <= n; i++)
   {
      for (int j = 1; j <= n; j++)
         cout << kay[i][j] << " ";
      cout << endl;
   }

   cout << endl;
   outputPath(c, kay, noEdge, 1, 5);
   cout << endl;

   // now do for g[1]
   cout << "\nWorking on weighted directed graph" << endl;
   g[1]->allPairs(c, kay);
   cout << "Cost matrix is" << endl;
   for (int i = 1; i <= n; i++)
   {
      for (int j = 1; j <= n; j++)
         cout << c[i][j] << " ";
      cout << endl;
   }
   
   cout << "\nKay matrix is" << endl;
   for (int i = 1; i <= n; i++)
   {
      for (int j = 1; j <= n; j++)
         cout << kay[i][j] << " ";
      cout << endl;
   }
   cout << endl;

   outputPath(c, kay, noEdge, 1, 5);
}
