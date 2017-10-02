
// file adigraph.h
//adjacency matrix representation of a directed graph
//initial version

#ifndef AdjacencyDigraph_
#define AdjacencyDigraph_

#include "awdgraph.h"

class AdjacencyDigraph :
               public AdjacencyWDigraph<int> {
   public:
      AdjacencyDigraph(int Vertices = 10)
   	  : AdjacencyWDigraph<int>(Vertices, 0) {}
      AdjacencyDigraph& Add(int i, int j)
          {AdjacencyWDigraph<int>::Add(i,j,1);
           return *this;}
      AdjacencyDigraph& Delete(int i, int j)
          {AdjacencyWDigraph<int>::Delete(i,j);
           return *this;}
};

#endif
