
// functions for undirected graphs
// includes function to determine if a graph is bipartite

#ifndef Undirected_
#define Undirected_

#include "network.h"
#include "lstack.h"
#include "lqueue.h"

class NodeType {
   friend class Undirected;
   private:
      int left, right;
};

class Undirected : virtual public Network {
   public:
      virtual int Degree(int i) const = 0;
      bool Connected();
      int LabelComponents(int L[]);
      bool BipartiteCover(int L[], int C[], int& m);
      bool Bipartite(int L[]);
   private:
      void CreateBins(int b, int n);
      void DestroyBins() {delete [] node;
                          delete [] bin;}
      void InsertBins(int b, int v);
      void MoveBins(int bMax, int ToBin, int v);
      int *bin;
      NodeType *node;
};

bool Undirected::Connected()
{// Return true iff graph is connected.

   int n = Vertices();

   // set all vertices as not reached
   int *reach = new int [n+1];
   for (int i = 1; i <= n; i++)
      reach[i] = 0;
   
   // mark vertices reachable from vertex 1
   DFS(1, reach, 1);
   
   // check if all vertices marked
   for (i = 1; i <= n; i++)
      if (!reach[i]) return false;
   return true;
}

int Undirected::LabelComponents(int L[])
{// Label the components of the graph.
 // Return the number of components and set L[1:n]
 // to represent a labeling of vertices by component.

   int n = Vertices();

   // assign all vertices to no component
   for (int i = 1; i <= n; i++)
      L[i] = 0;

   int label = 0;  // ID of last component
   // identify components
   for (i = 1; i <= n; i++)
      if (!L[i]) {// unreached vertex
         // vertex i is in a new component
         label++;
         BFS(i, L, label);} // mark new component

   return label;
}

void Undirected::CreateBins(int b, int n)
{// Create b empty bins and n nodes.
   node = new NodeType [n+1];
   bin = new int [b+1];
   // set bins empty
   for (int i = 1; i <= b; i++)
      bin[i] = 0;
}

void Undirected::InsertBins(int b, int v)
{// Insert v into bin b unless b is zero.
   if (!b) return;   // do not insert in bin 0
   node[v].left = b; // add at left end
   if (bin[b]) node[bin[b]].left = v;
   node[v].right = bin[b];
   bin[b] = v;
}

void Undirected::MoveBins(int bMax, int ToBin, int v)
{// Move vertex v from its current bin to bin ToBin.
   // nodes to the left and right of v
   int l = node[v].left;
   int r = node[v].right;

   // delete from current bin
   if (r) node[r].left = node[v].left;
   if (l > bMax || bin[l] != v) // not left-most one
      node[l].right = r;
   else bin[l] = r;             // left-most in bin l

   // add to bin ToBin
   InsertBins(ToBin, v);
}

bool Undirected::BipartiteCover(int L[], int C[], int& m)
{// Find a cover of the bipartite graph.
 // L is the input vertex labeling, L[i] = 1 iff i is
 // in A.  C is an output array that identifies the
 // cover.  Return false if the graph has no cover.
 // If the graph has a cover, return true;
 // return cover size in m; and cover in C[0:m-1].

   int n = Vertices();

   // create structures
   int SizeOfA = 0;
   for (int i = 1; i <= n; i++) // find size of set A
      if (L[i] == 1) SizeOfA++;
   int SizeOfB = n - SizeOfA;
   CreateBins(SizeOfB, n);
   int *New = new int [n+1];
      // vertex i covers New[i] uncovered vertices of B
   bool *Change = new bool [n+1];
      // Change[i] is true iff New[i] has changed
   bool *Cov = new bool [n+1];
      // Cov[i] is true iff vertex i is covered
   InitializePos();
   LinkedStack<int> S;
   
   // initialize
   for (i = 1; i <= n; i++) {
      Cov[i] = Change[i] = false;
      if (L[i] == 1) {// i is in A
         New[i] = Degree(i); // i covers this many
         InsertBins(New[i], i);}}
   
   // construct cover
   int covered = 0,       // # of covered vertices
       MaxBin = SizeOfB;  // max bin that may be
                          // nonempty
   m = 0;                 // cursor for C
   while (MaxBin > 0) {   // search all bins
      // select a vertex
      if (bin[MaxBin]) {      // bin not empty
         int v = bin[MaxBin]; // first vertex
         C[m++] = v;          // add v to cover
         // label newly covered vertices
         int j = Begin(v), k;
         while (j) {
            if (!Cov[j]) {// j not covered yet
               Cov[j] = true;
               covered++;
               // update New
               k = Begin(j);
               while (k) {
                  New[k]--;     // j does not count
                  if (!Change[k]) {
                     S.Add(k);  // stack once only
                     Change[k] = true;}
                  k = NextVertex(j);}
               }
            j = NextVertex(v);}

         // update bins
         while (!S.IsEmpty()) {
            S.Delete(k);
            Change[k] = false;
            MoveBins(SizeOfB, New[k], k);}
         }
      else MaxBin--;
      }
   
   DeactivatePos();
   DestroyBins();
   delete [] New;
   delete [] Change;
   delete [] Cov;
   return (covered == SizeOfB);
}

bool Undirected::Bipartite(int L[])
{// Label the vertices such that every edge connects
 // a vertex with L[] = 1 to one with L[] = 2.
 // Return false if not bipartite and true if bipartite
   int n = Vertices();
   // set all labels to 0
   for (int v = 1; v <= n; v++)
      L[v] = 0;

   // do a breadth first search in each component
   LinkedQueue<int> Q;
   InitializePos();
   for (v = 1; v <= n; v++)
      if (!L[v]) {// new component
         L[v] = 1;
         Q.Add(v);
         while (!Q.IsEmpty()) {
            int w;
            Q.Delete(w);
            int u = Begin(w);
            while (u) {  // vertices adjacent to w
               if (L[u]) // old vertex
   	          {if (L[u] == L[w]) return false;} // same set
               else {// new vertex
                     Q.Add(u);
                     L[u] = 3 - L[w];} // assign u to other set
               u = NextVertex(w);
               }
            }
        }  

   DeactivatePos();

   return true;
}
  
#endif
