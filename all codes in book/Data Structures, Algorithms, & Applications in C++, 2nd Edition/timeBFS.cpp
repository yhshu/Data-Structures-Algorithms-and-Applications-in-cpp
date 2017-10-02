
// time for graph::bfs
// run this program twice, once with the bfs methods
// in the implementing classes commented out and once
// with them present 

#include <iostream>
#include <time.h>
#include "unweightedEdge.h"
#include "adjacencyGraph.h"
#include "linkedGraph.h"
#include "graph.h"

using namespace std;

void main(void)
{
   double clocksPerMillis = double(CLOCKS_PER_SEC) / 1000;
                      // clock ticks per millisecond
   graph<bool> *g[2];
   int n = 100;
   g[0] = new adjacencyGraph(n);
   g[1] = new linkedGraph(n);
   int *reached = new int [n + 1];
  
   // set up complete graph
   for (int i = 1; i <= n; i++)
      for (int j = i + 1; j <= n; j++)
      {
         g[0]->insertEdge(new unweightedEdge(i, j));
         g[1]->insertEdge(new unweightedEdge(i, j));
      }

   long startTime = clock();
   // repeat many times
   int numTimes = 10000;
   for (int r = 1; r <= numTimes; r++)
   {
      for (int i = 1; i <= n; i++)
         reached[i] = 0;
      g[0]->bfs(1, reached, 1);
   }

   double elapsedTime = ((double) (clock() - startTime)) / numTimes;
   elapsedTime /= clocksPerMillis;
   cout << "BFS time for adjacency matrix is " 
        << elapsedTime << " milliseconds" << endl;

   startTime = clock();
   for (int r = 1; r <= numTimes; r++)
   {
      for (int i = 1; i <= n; i++)
         reached[i] = 0;
      g[1]->bfs(1, reached, 1);
   }
   elapsedTime = ((double) (clock() - startTime)) / numTimes;
   elapsedTime /= clocksPerMillis;
   cout << "BFS time for linked adjacency lists is " 
        << elapsedTime << " milliseconds" << endl;
}
