

// functions for undirected graphs
// includes max independent set heuristic

#ifndef Undirected_
#define Undirected_

#include "network.h"
#include "lstack.h"
#include "echain.h"
#include "citer.h"
#include "swap.h"

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
      int MaxIndependentSet(int V[]);
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
  
int Undirected::MaxIndependentSet(int V[])
{// Find an independent set using the greedy method.
 // Return the independent set size and put the independent
 // set vertices in V[0:size-1]

   InitializePos();
   int n = Vertices();
   int *C = new int [n+1];  // candidate array
                            // i is candidate iff C[i] = 2
   // count[i] is number of candidate vertices i
   // is not adjacent to
   int *count = new int [n+1];

   // initialize candidate array
   for (int i = 1; i <= n; i++)
      C[i] = 2;

   // find vertex with min degree
   int MinDegree = Degree(1);
   int MinV = 1;
   for (i = 2; i <= n; i++) {
     int m = Degree(i);
     if (m < MinDegree) {
        MinDegree = m;
        MinV = i;}
     }

   // MinV is first vertex in independent set
   C[MinV] = 1;

   // define three chains for candidate and eliminated vertices
   Chain<int> *Cand = new Chain<int>,
              *New = new Chain<int>,
              *Elim = new Chain<int>;

   // vertices adjacent to MinV are no longer candidates
   int v = Begin(MinV);
   while (v) {
      C[v] = 0;
      v = NextVertex(MinV);
      }

   // create candidate chain
   for (i = 1; i <= n; i++)
      if (C[i] == 2) Cand->Insert(0,i);

   // find next vertex to add to independent set 
   // this is a candidate vertex which is adjacent to
   // to the fewest other candidate vertices
   MinDegree = n + 1;
   // define a chain iterator to go down chain of candidates
   ChainIterator<int> c;
   int *u = c.Initialize(*Cand);
   while (u) {
      // vertex *u is a candidate
      // find number of other candidates adjacent to it
      v = Begin(*u);
      count[*u] = 0;
      while (v) {
         // if v is a candidate, increment count[*u]
         if (C[v] == 2) count[*u]++;
         v = NextVertex(*u);
         }

      // is this better vertex to add next?
      if (count[*u] < MinDegree) {// yes it is
         MinDegree = count[*u];
         MinV = *u;}
      u = c.Next();
      }

   // add additional vertices to clique
   while (MinDegree < n + 1) {
      // MinV will be added to independent set and
      // adjacent candidate vertices will be eliminated

      // label eliminated candidates
      v = Begin(MinV);
      while (v) {
         // v is to be eliminated, but first
         // make sure it was a candidate
         if (C[v] == 2) {
            C[v] = 0;
            Elim->Insert(0,v);
            }
         v = NextVertex(MinV);
         }

      // add MinV to independent set
      C[MinV] = 1;

      // now set up new candidates
      u = c.Initialize(*Cand);
      while (u) {
         if (C[*u] == 2)
           // *u remains a candidate
           New->Insert(0,*u);
         u = c.Next();
         }
      Cand->Erase();
      Swap(Cand,New);

      // update count to account for eliminated
      // candidates and selection of MinV
      u = c.Initialize(*Elim);
      while (u) {
         // *u has been eliminated
         // reduce count of adjacent candidates
         v = Begin(*u);
         while (v) {
            // easier to reduce everyone's count
            count[v]--;
            v = NextVertex(*u);
            }
         u = c.Next();
         }
      Elim->Erase();

      // update MinV
      MinDegree = n + 1;
      u = c.Initialize(*Cand);
      while (u) {
         if (count[*u] < MinDegree) {
            MinDegree = count[*u];
            MinV = *u;
            }
         u = c.Next();
         }
      }
      
   // put clique vertices into V
   int s = -1;
   for (i = 1; i <= n; i++)
      if (C[i] == 1) V[++s] = i;
       
   delete [] C;
   delete [] count;
   DeactivatePos();
   return s + 1;
}

#endif
