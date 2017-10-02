
// used by UNetwork::Prim
#ifndef VertexNode1_
#define VertexNode1_

template <class T> class UNetwork;
template <class T> class ModifiedMinHeap;

template <class T>
class VertexNode1 {
   friend UNetwork<T>;
   public:
      operator T () const {return distance;}
   private:
      T distance;    // distance to nearest tree vertex
      int nbr;       // closest tree vertex
};


template <class T>
class VertexNode2 {
   friend UNetwork<T>;
   friend ModifiedMinHeap<T>;
   public:
      operator T () const {return distance;}
   private:
      T distance;    // distance to nearest tree vertex
      int ID;        // vertex ID
};

#endif
