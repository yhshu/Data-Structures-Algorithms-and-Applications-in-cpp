// adjacency matrix representation of a directed weighted graph
// initial version extended to include input and output functions
// and overloading of << and >>

#ifndef AdjacencyWDigraph_
#define AdjacencyWDigraph_

#include <iostream.h>
#include <stdlib.h>
#include "make2db.h"
#include "del2d.h"
#include "xcept.h"

template <class T> class AdjacencyWGraph;
template <class T> class AdjacencyIterator;

template <class T>
class AdjacencyWDigraph {
   friend AdjacencyWGraph<T>;
   friend AdjacencyIterator<T>;
   friend class AdjacencyGraph;
   friend class AdjacencyDigraph;
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
      void Input() {Input(cin);}
      void Input(istream& in);
      void Output() const
         {Output(cout);}
      void Output(ostream& out) const;
   private:
      T NoEdge;  // used for absent edge
      int n;     // number of vertices
      int e;     // number of edges
      T **a;     // 2D array
};

template <class T>
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

template <class T>
bool AdjacencyWDigraph<T>::Exist(int i, int j) const
{// Does edge (i, j) exist?
   if (i < 1 || j < 1 || i > n || j > n
       || a[i][j] == NoEdge) return false;
   return true;
}

template <class T>
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

template <class T>
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

template <class T>
int AdjacencyWDigraph<T>::OutDegree(int i) const
{// Return out degree of vertex i.
   if (i < 1 || i > n) throw BadInput();
   // count out edges from vertex i
   int sum = 0;
   for (int j = 1; j <= n; j++)
      if (a[i][j] != NoEdge) sum++;
   return sum;
}

template <class T>
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
void AdjacencyWDigraph<T>::Input(istream& in)
{// Input the cost adjacency matrix.
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
   cout << "Enter value to use for no edge" << endl;
   cin >> NoEdge;

   // create a new 2D array a[][] and initialize to NoEdge
   Make2DArray(a, n+1, n+1);
   // initalize to digraph with no edges
   for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
         a[i][j] = NoEdge;
   e = 0;

   // now input the edges and add them to a[][]
   int u, v;  // edge end points
   T w;       // edge weight
   for (i = 1; i <= E; i++) {
      cout << "Enter edge " << i << endl;
      in >> u >> v >> w;
      Add(u,v,w);
      }
}

// overload >>
template <class T>
istream& operator>>(istream& in, AdjacencyWDigraph<T>& x)
   {x.Input(in); return in;}


template <class T>
void AdjacencyWDigraph<T>::Output(ostream& out) const
{// Output the adjacency matrix.
   for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++)
         out << a[i][j] << " ";
      out << endl;}
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const AdjacencyWDigraph<T>& x)
   {x.Output(out); return out;}

#endif
