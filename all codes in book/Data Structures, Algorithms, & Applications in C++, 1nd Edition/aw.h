// file aw.h
// adjacency matrix representation of a weighted graph
// final version
#ifndef AdjacencyWGraph_
#define AdjacencyWGraph_

#include "awd.h"
#include "undirect.h"
#include "unetwork.h"

template<class T>
class AdjacencyWGraph : public AdjacencyWDigraph<T>,
                        virtual public Undirected,
			virtual public UNetwork<T> {
   public:
      AdjacencyWGraph(int Vertices = 10, T noEdge = 0)
   	  : AdjacencyWDigraph<T>(Vertices, noEdge) {}
      AdjacencyWGraph<T>& Add(int i, int j, const T& w)
          {AdjacencyWDigraph<T>::Add(i,j,w);
           a[j][i] = w;
           return *this;}
      AdjacencyWGraph<T>& Delete(int i, int j)
          {AdjacencyWDigraph<T>::Delete(i,j);
           a[j][i] = NoEdge;
           return *this;}
      int Degree(int i) const {return OutDegree(i);}
};

#endif
