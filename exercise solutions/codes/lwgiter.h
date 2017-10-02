
// iterator for linked weighted graphs

#ifndef LinkedWeightedIterator_
#define LinkedWeightedIterator_

#include "lwdgph2.h"
#include "gnode.h"
#include "citer.h"

template <class T>
class LinkedWeightedIterator {
   public:
      int Begin(LinkedWDigraph<T>& G, int i);
      int NextVertex();
   private:
      ChainIterator<GraphNode<T> > p;  // used to traverse adjacency list
};

template <class T>
int LinkedWeightedIterator<T>::
    Begin(LinkedWDigraph<T>& G, int i)
{// Return first vertex adjacent to vertex i.
   if (i < 1 || i > G.n) throw OutOfBounds();
   GraphNode<T> *x = p.Initialize(G.h[i]);
   return (x) ? x->vertex : 0;
}

template <class T>
int LinkedWeightedIterator<T>::NextVertex()
{// Return next adjacent vertex.
   GraphNode<T> *x = p.Next();
   return (x) ? x->vertex : 0;
}

#endif
