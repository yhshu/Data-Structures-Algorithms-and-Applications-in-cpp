// adjacency matrix representation of a directed graph
// reflexive transitive closure added

#ifndef AdjacencyDigraph_
#define AdjacencyDigraph_

#include "awdgph1.h"
#include "make2db.h"
#include "del2d.h"

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
      void ReflexiveTransitiveClosure(int **RTC);
      void Input() {Input(cin);}
      void Input(istream& in);
};

void AdjacencyDigraph::Input(istream& in)
{// Input the adjacency matrix.
   // first delete the old graph
   Delete2DArray(a,n+1);

   // input number of vertices and edges
   cout << "Enter the number of vertices in the graph"
        << endl;
   cin >> n;
   if (n < 0) throw BadInput();
   cout << "Enter the number of edges in the graph" << endl;
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

void AdjacencyDigraph::
     ReflexiveTransitiveClosure(int **RTC)
{// Return, in RTC, the relexive transitive closure
 // matrix of the digraph.  Modified version of the
 // dynamic programming code of Program 15.9.
   // copy adjacency matrix into RTC
   for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
         RTC[i][j] = a[i][j];

   // set diagonal entries to 1
   for (i = 1; i <= n; i++)
      RTC[i][i] = 1;

   // 3 nested loops of Program 5.9 using
   // logical operators
   for (int k = 1; k <= n; k++)
      for (int i = 1; i <= n; i++)
         for (int j = 1; j <= n; j++)
            RTC[i][j] = RTC[i][j] || (RTC[i][k] && RTC[k][j]);
}


#endif
