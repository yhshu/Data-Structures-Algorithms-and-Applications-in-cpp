// file lbase.h
// base class for linked graph representations

#ifndef LinkedBase_
#define LinkedBase_

#include "keychain.h"
#include <iostream.h>

template<class type>
class LinkedBase {
   public:
      LinkedBase(int Vertices = 10);
      ~LinkedBase() {delete [] h;}
      int Edges() {return e;}
      void Print();
   protected:
      int n; // number of vertices
      int e; // number of edges
      KeyedChain<type> *h; // 1D array
};

template<class type>
LinkedBase<type>::LinkedBase(int Vertices)
{
   n = Vertices; e = 0;
   h = new KeyedChain<type> [n+1];
   if (!h)
    {cerr << "Out Of Memory" << endl;
     exit(1);}
}

template<class type>
void LinkedBase<type>::Print()
{
   for (int i = 1; i <= n; i++) {
      cout << "Vertex " << i << " = ";
      h[i].Print();}
}

#endif
