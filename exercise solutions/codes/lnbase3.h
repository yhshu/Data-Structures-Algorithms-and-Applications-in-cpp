

// final linked base for linked graph representations
// output functions added

#ifndef LinkedBase_
#define LinkedBase_

#include <iostream.h>
#include <stdlib.h>
#include "network2.h" // has transitive closure
#include "jchain.h"   // was fchain.h
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
      void InitializePos()
         {pos = new ChainIterator<T> [n+1];}
      void DeactivatePos() {delete [] pos;}
      void Output() const
         {Output(cout);}
      void Output(ostream& out) const;
   private:
      int n;       // number of vertices
      int e;       // number of edges
      Chain<T> *h; // adjacency list array
      ChainIterator<T> *pos;
};

template<class T>
void LinkedBase<T>::Output(ostream& out) const
{// Output the adjacency lists.
   for (int i = 1; i <= n; i++) {
      out << "Vertex " << i << " = ";
      h[i].Output(out);
      out << endl;}
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const LinkedBase<T>& x)
   {x.Output(out); return out;}
#endif
