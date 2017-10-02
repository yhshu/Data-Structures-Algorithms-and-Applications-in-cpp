
// linked adjacency list representation of a graph
// final version
// includes input function

#ifndef LinkedGraph_
#define LinkedGraph_

#include "ldig3.h"  // LinkedDigraph
#include "und2.h"   // has DSpanningTree
#include "xcept.h"
#include "citer.h"

class LinkedGraph : public LinkedDigraph,
                    virtual public Undirected {
   public:
      LinkedGraph(int Vertices = 10)
        : LinkedDigraph (Vertices) {}
      LinkedGraph& Add(int i, int j);
      LinkedGraph& Delete(int i, int j);
      int Degree(int i) const {return InDegree(i);}
      int OutDegree(int i) const {return InDegree(i);}
      void Input()
         {Input(cin);}
      void Input(istream& in);
   protected:
      LinkedGraph& AddNoCheck(int i, int j);
};

LinkedGraph& LinkedGraph::Add(int i, int j)
{// Add edge (i,j) to the graph.
   if (i < 1 || j < 1 || i > n || j > n || i ==j
       || Exist(i, j)) throw BadInput();
   return AddNoCheck(i, j);
}

LinkedGraph& LinkedGraph::AddNoCheck(int i, int j)
{// Add edge (i,j), no error checks.
   h[i].Insert(0,j);
   try {h[j].Insert(0,i);}
   // on exception, undo first insert
   // and rethrow same exception
   catch (...) {h[i].Delete(j);
                throw;}
   e++;
   return *this;
}

LinkedGraph& LinkedGraph::Delete(int i, int j)
{// Delete edge (i,j).
   LinkedDigraph::Delete(i,j);
   e++; // compensate
   LinkedDigraph::Delete(j,i);
   return *this;
}

void LinkedGraph::Input(istream& in)
{// Input the adjacency lists.
   // first delete the old graph
   delete [] h;

   // input new size and create h
   cout << "Enter the number of vertices in the graph" << endl;
   cin >> n;
   if (n < 0) throw BadInput();
   cout << "Enter the number of edges in the graph" << endl;
   int E;
   cin >> E;
   if (E < 0 || E > n*(n-1)/2) throw BadInput();
   h = new Chain<int> [n+1];

   // now input the edges and add them to the adjacency
   // lists
   e = 0;
   int u, v;  // edge end points
   for (int i = 1; i <= E; i++) {
      cout << "Enter edge " << i << endl;
      in >> u >> v;
      if (u < 1 || v < 1 || u > n || v > n)
         throw BadInput();
      AddNoCheck(u,v);
      }

   // check for duplicate edges
   bool *seen = new bool [n+1];
   for (i = 1; i <= n; i++)
      seen[i] = false;
   ChainIterator<int> c;
   for (i = 1; i <= n; i++) {// check vertex i
      int *k = c.Initialize(h[i]);
      while (k) {// not at list end 
         if (seen[*k]) {// duplicate edge
            delete [] seen;
            throw BadInput();}
         else seen[*k] = true;
         k = c.Next();
         }
      // reset seen
      k = c.Initialize(h[i]);  
      while (k) {// not at list end 
         seen[*k] = false;
         k = c.Next();
         }
      }

   delete [] seen;
}

// overload >>
istream& operator>>(istream& in, LinkedGraph& x)
   {x.Input(in); return in;}

#endif
