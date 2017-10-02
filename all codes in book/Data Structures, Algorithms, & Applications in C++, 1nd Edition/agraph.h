// file agraph.h
// adjacency matrix representation of a graph
// initial version

#ifndef AdjacencyGraph_
#define AdjacencyGraph_

#include "awgraph.h"

class AdjacencyGraph : public AdjacencyWGraph<int>
{
   public:
      AdjacencyGraph(int Vertices = 10)
   	  : AdjacencyWGraph<int>(Vertices, 0) {}
      AdjacencyGraph& Add(int i, int j)
          {AdjacencyWGraph<int>::Add(i,j,1);
           return *this;}
      AdjacencyGraph& Delete(int i, int j)
          {AdjacencyWGraph<int>::Delete(i,j);
           return *this;}
};

#endif
