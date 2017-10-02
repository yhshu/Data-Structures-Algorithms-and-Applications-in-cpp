// file lwgraph.h
// linked adjacency list representation of weighted graphs
// initial version
#ifndef LinkedWGraph_
#define LinkedWGraph_

#include "lwdgraph.h"

template<class T>
class LinkedWGraph : public LinkedWDigraph<T> {
   public:
      LinkedWGraph(int Vertices = 10)
        : LinkedWDigraph<T> (Vertices) {}
      LinkedWGraph<T>& Add(int i, int j, const T& w);
      LinkedWGraph<T>& Delete(int i, int j);
      int Degree(int i) const {return InDegree(i);}
      int OutDegree(int i) const {return InDegree(i);}
   protected:
      LinkedWGraph<T>& AddNoCheck(int i, int j, const T& w);
};

template<class T>
LinkedWGraph<T>& LinkedWGraph<T>
           ::Add(int i, int j, const T& w)
{// Add edge (i,j).
   if (i < 1 || j < 1 || i > n || j > n || i == j
       || Exist(i, j)) throw BadInput();
   return AddNoCheck(i, j, w);
}

template<class T>
LinkedWGraph<T>& LinkedWGraph<T>
          ::AddNoCheck(int i, int j, const T& w)
{// Add edge (i,j).
   GraphNode<T> x;
   x.vertex = j; x.weight = w;
   h[i].Insert(0,x); // put on i's list
   x.vertex = i;
   try {h[j].Insert(0,x);}
   catch (...) // insert failed
      {// undo previous insert
       x.vertex = j; h[i].Delete(x);
       throw;} // throw same exception
   e++;
   return *this;
}

template<class T>
LinkedWGraph<T>& LinkedWGraph<T>
                 ::Delete(int i, int j)
{// Delete edge (i,j).
   LinkedWDigraph<T>::Delete(i,j);
   LinkedWDigraph<T>::Delete(j,i);
   e++; // compensate
   return *this;
}

#endif
