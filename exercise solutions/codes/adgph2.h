
// adjacency matrix representation of a directed graph
// input function added
// << overloaded

#ifndef AdjacencyDigraph_
#define AdjacencyDigraph_

#include "awdgph1.h"
#include "make2db.h"
#include "del2d.h"
#include "xcept.h"

class AdjacencyDigraph :
               public AdjacencyWDigraph<int> {
   public:
      AdjacencyDigraph(int Vertices = 10)
   	  : AdjacencyWDigraph<int>(Vertices, 0) {}
      AdjacencyDigraph& Add(int i, int j)
          {AdjacencyWDigraph<int>::Add(i,j,1);
           return *this;}
      AdjacencyDigraph& Delete(int i, int j)
          {AdjacencyWDigraph<int>::Delete(i,j);
           return *this;}
      void Input() {Input(cin);}
      void Input(istream& in);
};

void AdjacencyDigraph::Input(istream& in)
{// Input the adjacency matrix.
   // first delete the old digraph
   Delete2DArray(a,n+1);

   // input number of vertices and edges
   cout << "Enter the number of vertices in the digraph"
        << endl;
   cin >> n;
   if (n < 0) throw BadInput();
   cout << "Enter the number of edges in the digraph" << endl;
   int E;
   cin >> E;
   if (E < 0 || E > n*(n-1)) throw BadInput();

   // create a new 2D array a[][] and initialize to zero
   Make2DArray(a, n+1, n+1);
   // initalize to digraph with no edges
   for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
         a[i][j] = 0;
   e = 0;
   NoEdge = 0;

   // now input the edges and add them to a[][]
   int u, v;  // edge end points
   for (i = 1; i <= E; i++) {
      cout << "Enter edge " << i << endl;
      in >> u >> v;
      Add(u,v);
      }
}

// overload >>
istream& operator>>(istream& in, AdjacencyDigraph& x)
   {x.Input(in); return in;}


#endif
