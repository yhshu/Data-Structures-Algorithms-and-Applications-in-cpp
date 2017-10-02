
// file ag.h
// adjacency matrix representation of a graph
// final version

#ifndef AdjacencyGraph_
#define AdjacencyGraph_

#include "aw.h"
#include "bbnode.h"
#include "clnode.h"
#include "maxheap.h"

class AdjacencyGraph : public AdjacencyWGraph<int>
{
   public:
      AdjacencyGraph(int Vertices = 10)
   	  : AdjacencyWGraph<int>(Vertices, 0) {}
      AdjacencyGraph& Add(int i, int j)
          {AdjacencyWGraph<int>::Add(i,j,1);
           return *this;}
      AdjacencyGraph& Delete(int i, int j)
          {AdjacencyWGraph<int>::Delete(i,j);
           return *this;}
      int MaxClique(int v[]);
      int BBMaxClique(int v[]);
   private:
      void maxClique(int i);
      void AddCliqueNode(MaxHeap<CliqueNode> &H,
           int cn, int un, int level, bbnode E[], bool ch);
      // static members used by backtracking
      // and branch-and-bound methods
      static int *x,     // path to current node
                 *bestx, // best solution so far
                 bestn,  // max number of vertices so far
                 cn;     // current number of vertices
};

// define static members
int *AdjacencyGraph::x,
    *AdjacencyGraph::bestx,
     AdjacencyGraph::bestn,
     AdjacencyGraph::cn;


void AdjacencyGraph::maxClique(int i)
{// Backtracking code to compute largest clique.
   if (i > n) {// at leaf
      // found a larger clique, update
      for (int j = 1; j <= n; j++)
         bestx[j] = x[j];
      bestn = cn;
      return;}

   // see if vertex i connected to others
   // in current clique
   int OK = 1;
   for (int j = 1; j < i; j++)
      if (x[j] && a[i][j] == NoEdge) {
         // i not connected to j
         OK = 0;
         break;}

   if (OK) {// try x[i] = 1
      x[i] = 1;  // add i to clique
      cn++;
      maxClique(i+1);
      x[i] = 0;
      cn--;}

   if (cn + n - i > bestn) {// try x[i] = 0
      x[i] = 0;
      maxClique(i+1);}
}

int AdjacencyGraph::MaxClique(int v[])
{// Return size of largest clique.
 // Return clique vertices in v[1:n].
   // initialize for maxClique
   x = new int [n+1];
   cn = 0;
   bestn = 0;
   bestx = v;

  // find max clique
   maxClique(1);

   delete [] x;
   return bestn;
}


void AdjacencyGraph::AddCliqueNode(MaxHeap<CliqueNode>
    &H, int cn, int un, int level, bbnode E[], bool ch)
{// Add node to max heap.  Used by BBMaxClique.
   bbnode *b = new bbnode;
   b->parent = E;
   b->LChild = ch;
   CliqueNode N;
   N.cn = cn;
   N.ptr = b;
   N.un = un;
   N.level = level;
   H.Insert(N);
}

int AdjacencyGraph::BBMaxClique(int bestx[])
{// Max profit branch-and-bound code to find
 // a max clique.
   // define a max heap for up to
   // 1000 live nodes
   MaxHeap<CliqueNode> H(1000);

   // initialize for level 1 start
   bbnode *E = 0;  // current E-node is root
   int i = 1,      // level of E-node
       cn = 0,     // size of clique at E
       bestn = 0;  // size of largest clique so far

   // search subset space tree
   while (i != n+1) {// while not at leaf
      // see if vertex i is connected to others
      // in current clique
      bool OK = true;
      bbnode *B = E;
      for (int j = i - 1; j > 0; B = B->parent, j--)
         if (B->LChild && a[i][j] == NoEdge) {
            OK = false;
            break;}

      if (OK) {// left child feasible
         if (cn + 1 > bestn) bestn = cn + 1;
         AddCliqueNode(H, cn+1, cn+n-i+1, i+1, E,
                                          true);}
      if (cn + n - i >= bestn)
         // right child has prospects
         AddCliqueNode(H, cn, cn+n-i, i+1, E, false);

      // get next E-node
      CliqueNode N;
      H.DeleteMax(N); // cannot be empty
      E = N.ptr;
      cn = N.cn;
      i = N.level;
      }

   // construct bestx[] by following path
   // from E to root
   for (int j = n; j > 0; j--) {
      bestx[j] = E->LChild;
      E = E->parent;
      }

   return bestn;
}


#endif
