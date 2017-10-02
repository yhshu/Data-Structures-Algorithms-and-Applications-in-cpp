// file awdgraph.h
// adjacency matrix representation of a directed weighted graph
// initial version
#ifndef AdjacencyWDigraph_
#define AdjacencyWDigraph_

#include<iostream.h>
#include<stdlib.h>
#include "make2db.h"
#include "del2d.h"
#include "xcept.h"

template <class T> class AdjacencyWGraph;

template<class T>
class AdjacencyWDigraph {
   friend AdjacencyWGraph<T>;
   public:
      AdjacencyWDigraph
               (int Vertices = 10, T noEdge = 0);
      ~AdjacencyWDigraph() {Delete2DArray(a,n+1);}
      bool Exist(int i, int j) const;
      int Edges()  const {return e;}
      int Vertices() const {return n;}
      AdjacencyWDigraph<T>& Add
                        (int i, int j, const T& w);
      AdjacencyWDigraph<T>& Delete(int i, int j);
      int OutDegree(int i) const;
      int InDegree(int i) const;
      void Output() const;
   private:
      T NoEdge;  // used for absent edge
      int n;     // number of vertices
      int e;     // number of edges
      T **a;     // 2D array
};

template<class T>
AdjacencyWDigraph<T>
   ::AdjacencyWDigraph(int Vertices, T noEdge)
{// Constructor.
   n = Vertices;
   e = 0;
   NoEdge = noEdge;
   Make2DArray(a, n+1, n+1);
   // initalize to graph with no edges
   for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
         a[i][j] = NoEdge;
}

template<class T>
bool AdjacencyWDigraph<T>::Exist(int i, int j) const
{// Does edge (i, j) exist?
   if (i < 1 || j < 1 || i > n || j > n
       || a[i][j] == NoEdge) return false;
   return true;
}

template<class T>
AdjacencyWDigraph<T>& AdjacencyWDigraph<T>
                  ::Add(int i, int j, const T& w)
{// Add edge (i,j) to digraph if not present.
   if (i < 1 || j < 1 || i > n ||
       j > n || i == j || a[i][j] != NoEdge)
       throw BadInput();
   a[i][j] = w;
   e++;
   return *this;
}

template<class T>
AdjacencyWDigraph<T>& AdjacencyWDigraph<T>
                  ::Delete(int i, int j)
{// Delete edge (i,j).
   if (i < 1 || j < 1 || i > n ||
       j > n || a[i][j] == NoEdge)
       throw BadInput();
   a[i][j] = NoEdge;
   e--;
   return *this;
}

template<class T>
int AdjacencyWDigraph<T>::OutDegree(int i) const
{// Return out degree of vertex i.
   if (i < 1 || i > n) throw BadInput();
   // count out edges from vertex i
   int sum = 0;
   for (int j = 1; j <= n; j++)
      if (a[i][j] != NoEdge) sum++;
   return sum;
}

template<class T>
int AdjacencyWDigraph<T>::InDegree(int i) const
{// Return indegree of vertex i.
   if (i < 1 || i > n) throw BadInput();
   // count in edges at vertex i
   int sum = 0;
   for (int j = 1; j <= n; j++)
      if (a[j][i] != NoEdge) sum++;
   return sum;
}

template <class T>
void AdjacencyWDigraph<T>::Output() const
{// Output the adjacency matrix.
   for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++)
         cout << a[i][j] << " ";
      cout << endl;}
}

#endif
