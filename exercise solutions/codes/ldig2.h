// linked adjacency list representation of a directed graph
// initial version
// extended to include input function and
// overloading of <<
// overloading of >> done in lbase2.h

#ifndef LinkedDigraph_
#define LinkedDigraph_

#include "lbase2.h"
#include "xcept.h"

class LinkedDigraph : public LinkedBase<int> {
   public:
      LinkedDigraph(int Vertices = 10)
        : LinkedBase<int> (Vertices) {}
      bool Exist(int i, int j) const;
      LinkedDigraph& Add(int i, int j);
      LinkedDigraph& Delete(int i, int j);
      int InDegree(int i) const;
      void Input() {Input(cin);}
      void Input(istream& in);
   protected:
      LinkedDigraph& AddNoCheck(int i, int j);
};

bool LinkedDigraph::Exist(int i, int j) const
{// Is edge (i,j) present?
   if (i < 1 || i > n) throw OutOfBounds();
   return (h[i].Search(j)) ? true : false;
}

LinkedDigraph& LinkedDigraph::Add(int i, int j)
{// Add edge (i,j) to the graph.
   if (i < 1 || j < 1 || i > n || j > n || i == j
       || Exist(i, j)) throw BadInput();
   return AddNoCheck(i, j);
}

LinkedDigraph& LinkedDigraph::AddNoCheck(int i, int j)
{// Add edge but do not check for errors.
   h[i].Insert(0,j); // add j to vertex i list
   e++;
   return *this;
}

LinkedDigraph& LinkedDigraph::Delete(int i, int j)
{// Delete edge (i,j).
   if (i < 1 || i > n) throw OutOfBounds();
   h[i].Delete(j);
   e--;
   return *this;
}

int LinkedDigraph::InDegree(int i) const
{// Return indegree of vertex i.
   if (i < 1 || i > n) throw OutOfBounds();
   // count in edges at vertex i
   int sum = 0;
   for (int j = 1; j <= n; j++)
      if (h[j].Search(i)) sum++;
   return sum;
}

void LinkedDigraph::Input(istream& in)
{// Input the adjacency lists.
   // first delete the old digraph
   delete [] h;

   // input new size and create h
   cout << "Enter the number of vertices in the digraph" << endl;
   cin >> n;
   if (n < 0) throw BadInput();
   cout << "Enter the number of edges in the digraph" << endl;
   int E;
   cin >> E;
   if (E < 0 || E > n*(n-1)) throw BadInput();
   h = new Chain<int> [n+1];

   // now input the edges and add them to the adjacency
   // lists
   e = 0;
   int u, v;  // edge end points
   for (int i = 1; i <= E; i++) {
      cout << "Enter edge " << i << endl;
      in >> u >> v;
      Add(u,v);
      }
}

// overload >>
istream& operator>>(istream& in, LinkedDigraph& x)
   {x.Input(in); return in;}

#endif
