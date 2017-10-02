// used by bbloadd.cpp

#ifndef bbnode_
#define bbnode_

template <class T> class HeapNode;
template <class T> class MaxHeap;

class bbnode {
   friend void AddLiveNode(MaxHeap<HeapNode<int> > &, bbnode *,
                             int, bool, int);
   friend int MaxLoading(int *, int, int, int *);
   friend class AdjacencyGraph;
   private:
      bbnode *parent; // pointer to parent node
      bool LChild;    // true iff left child of parent
};

template<class T>
class HeapNode {
   friend void AddLiveNode(MaxHeap<HeapNode<T> > &, bbnode *,
                   T, bool, int);
   friend T MaxLoading(T *, T, int, int *);
   public:
      operator T () const {return uweight;}
   private:
      bbnode *ptr;  // pointer to live node
      T uweight;    // upper weight of live node
      int level;    // level of live node
};

#endif
