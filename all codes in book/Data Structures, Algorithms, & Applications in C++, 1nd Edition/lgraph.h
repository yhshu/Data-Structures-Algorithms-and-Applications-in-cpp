
// file lgraph.h
// linked adjacency list representation of a graph
// initial version

#ifndef LinkedGraph_
#define LinkedGraph_

#include "ldigraph.h"
#include "xcept.h"

class LinkedGraph : public LinkedDigraph {
   public:
      LinkedGraph(int Vertices = 10)
        : LinkedDigraph (Vertices) {}
      LinkedGraph& Add(int i, int j);
      LinkedGraph& Delete(int i, int j);
      int Degree(int i) const {return InDegree(i);}
      int OutDegree(int i) const {return InDegree(i);}
   protected:
      LinkedGraph& AddNoCheck(int i, int j);
};

LinkedGraph& LinkedGraph::Add(int i, int j)
{// Add edge (i,j) to the graph.
   if (i < 1 || j < 1 || i > n || j > n || i ==j
       || Exist(i, j)) throw BadInput();
   return AddNoCheck(i, j);
}

LinkedGraph& LinkedGraph::AddNoCheck(int i, int j)
{// Add edge (i,j), no error checks.
   h[i].Insert(0,j);
   try {h[j].Insert(0,i);}
   // on exception, undo first insert
   // and rethrow same exception
   catch (...) {h[i].Delete(j);
                throw;}
   e++;
   return *this;
}

LinkedGraph& LinkedGraph::Delete(int i, int j)
{// Delete edge (i,j).
   LinkedDigraph::Delete(i,j);
   e++; // compensate
   LinkedDigraph::Delete(j,i);
   return *this;
}

#endif
