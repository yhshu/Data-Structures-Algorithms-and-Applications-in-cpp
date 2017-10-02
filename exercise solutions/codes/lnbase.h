// file lnbase.h
// final linked base for linked graph representations

#ifndef LinkedBase_
#define LinkedBase_

#include <iostream.h>
#include <stdlib.h>
#include "network.h"
#include "jchain.h"  // was fchain before
#include "citer.h"
#include "xcept.h"

template <class T> class LinkedWDigraph;
template <class T> class LinkedWGraph;

template<class T>
class LinkedBase : virtual public Network {
   friend class LinkedDigraph;
   friend class LinkedGraph;
   friend LinkedWDigraph<int>;
   friend LinkedWGraph<int>;
   public:
      LinkedBase(int Vertices = 10)
         {n = Vertices;
          e = 0;
          h = new Chain<T> [n+1];}
      ~LinkedBase() {delete [] h;}
      int Edges() const {return e;}
      int Vertices() const {return n;}
      int OutDegree(int i) const
         {if (i < 1 || i > n) throw OutOfBounds();
          return h[i].Length();}
      void Output() const;
      void InitializePos()
         {pos = new ChainIterator<T> [n+1];}
      void DeactivatePos() {delete [] pos;}
   private:
      int n;       // number of vertices
      int e;       // number of edges
      Chain<T> *h; // adjacency list array
      ChainIterator<T> *pos;
};

template<class T>
void LinkedBase<T>::Output() const
{// Output the adjacency lists.
   for (int i = 1; i <= n; i++) {
      cout << "Vertex " << i << " = ";
      h[i].Output(cout);
      cout << endl;}
}

#endif
