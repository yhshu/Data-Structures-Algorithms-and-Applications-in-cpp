// file awd.h
// adjacency matrix representation of a directed weighted graph
// full version
#ifndef AdjacencyWDigraph_
#define AdjacencyWDigraph_

#include <stdlib.h>
#include <iostream.h>
#include "fchain.h"
#include "network.h"
#include "citer.h"
#include "wnetwork.h"
#include "swap.h"
#include "make2db.h"
#include "del2d.h"

template <class T> class AdjacencyWGraph;

template<class T>
class AdjacencyWDigraph : virtual public Network,
                          virtual public WNetwork<T> {
   friend AdjacencyWGraph<T>;
   friend class AdjacencyGraph;
   public:
      AdjacencyWDigraph
               (int Vertices = 10, T noEdge = 0);
      ~AdjacencyWDigraph() {Delete2DArray(a,n+1);}
      bool Exist(int i, int j) const;
      int Edges() const {return e;}
      int Vertices() const {return n;}
      AdjacencyWDigraph<T>& Add
                        (int i, int j, const T& w);
      AdjacencyWDigraph<T>& Delete(int i, int j);
      int OutDegree(int i) const;
      int InDegree(int i) const;
      void ShortestPaths(int s, T d[], int p[]);
      void AllPairs(T **c, int **kay);
      void Output() const;
      void InitializePos() {pos = new int [n+1];}
      void DeactivatePos() {delete [] pos;}
      int Begin(int i);
      int NextVertex(int i);
      void First(int i, int& j, T& c);
      void Next(int i, int& j, T& c);
      T TSP(int v[]);
      T BBTSP(int v[]);
   private:
      void tSP(int i);
      T NoEdge;  // used for absent edge
      int n;     // number of vertices
      int e;     // number of edges
      T **a;     // adjacency matrix
      int *pos;
      // static members used by backtracking and
      // branch-and-bound methods
      static int *x,     // path to current node
                 *bestx; // best solution so far
      static T cc,       // cost at current node
               bestc;    // cost of best solution found so far
};

// define static members for T = int and float
// add definitions for additional types as needed
int  *AdjacencyWDigraph<int>::x,
     *AdjacencyWDigraph<int>::bestx,
      AdjacencyWDigraph<int>::bestc,
      AdjacencyWDigraph<int>::cc;

int  *AdjacencyWDigraph<float>::x,
     *AdjacencyWDigraph<float>::bestx;
float AdjacencyWDigraph<float>::bestc,
      AdjacencyWDigraph<float>::cc;

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
{
   for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++)
         cout << a[i][j] << " ";
      cout << endl;}
}

template<class T>
int AdjacencyWDigraph<T>::Begin(int i)
{// Return first vertex adjacent to vertex i.
if (i < 1 || i > n) throw OutOfBounds();

   // look for first adjacent vertex
   for (int j = 1; j <= n; j++)
      if (a[i][j] != NoEdge) {// j is first one
         pos[i] = j;
         return j;}

   pos[i] = n + 1; // no adjacent vertex
   return 0;
}

template<class T>
void AdjacencyWDigraph<T>::First(int i, int& j, T& c)
{// Return first vertex j and weight of (i,j).
   if (i < 1 || i > n) throw OutOfBounds();

   // look for first adjacent vertex
   for (j = 1; j <= n; j++)
      if (a[i][j] != NoEdge) {// j is first one
         pos[i] = j;
         c = a[i][j];
         return;}

   pos[i] = n + 1; // no adjacent vertex
   j = 0;
}

template<class T>
int AdjacencyWDigraph<T>::NextVertex(int i)
{// Return next vertex adjacent to vertex i.
   if (i < 1 || i > n) throw OutOfBounds();

   // find next adjacent vertex
   for (int j = pos[i] + 1; j <= n; j++)
      if (a[i][j] != NoEdge) {// j is next vertex
         pos[i] = j; return j;}

   pos[i] = n + 1; // no next vertex
   return 0;
}

template<class T>
void AdjacencyWDigraph<T>::Next(int i, int& j, T& c)
{// Return next vertex j and weight of (i,j).
   if (i < 1 || i > n) throw OutOfBounds();

   // find next adjacent vertex
   for (j = pos[i] + 1; j <= n; j++)
      if (a[i][j] != NoEdge) {// j is next vertex
         pos[i] = j;
         c = a[i][j];
         return;}

   pos[i] = n + 1; // no next vertex
   j = 0;
}

template<class T>
void AdjacencyWDigraph<T>::ShortestPaths(int s,
                          T d[], int p[])
{// Shortest paths from vertex s, return shortest
 // distances in d and predecessor info in p.
   if (s < 1 || s > n) throw OutOfBounds();
   Chain<int> L; // list of reachable vertices for
                 // which paths have yet to be found
   ChainIterator<int> I;
   // initialize d, p, and L
   for (int i = 1; i <= n; i++){
      d[i] = a[s][i];
      if (d[i] == NoEdge) p[i] = 0;
      else {p[i] = s; 
            L.Insert(0,i);}
      }

   // update d and p
   while (!L.IsEmpty()) {// more paths exist
      // find vertex *v in L with least d
      int *v = I.Initialize(L);
      int *w = I.Next();
      while (w) {
         if (d[*w] < d[*v]) v = w;
         w = I.Next();}

      // next shortest path is to vertex *v
      // delete from L and update d
      int i = *v;
      L.Delete(*v);
      for (int j = 1; j <= n; j++) {
         if (a[i][j] != NoEdge && (!p[j] ||
   	             d[j] > d[i] + a[i][j])) {
            // d[j] decreases
            d[j] = d[i] + a[i][j];
            // add j to L if not already in L
            if (!p[j]) L.Insert(0,j);
            p[j] = i;}
         }
      }
}
    
template<class T>
void AdjacencyWDigraph<T>::AllPairs(T **c, int **kay)
{// All pairs shortest paths.
 // Compute c[i][j] and kay[i][j] for all i and j.
   // initialize c[i][j] = c(i,j,0)
   for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++) {
         c[i][j] = a[i][j];
         kay[i][j] = 0;
         }
   for (i = 1; i <= n; i++)
      c[i][i] = 0;
   
   // compute c[i][j] = c(i,j,k)
   for (int k = 1; k <= n; k++)
      for (int i = 1; i <= n; i++)
         for (int j = 1; j <= n; j++) {
            T t1 = c[i][k];
            T t2 = c[k][j];
            T t3 = c[i][j];
            if (t1 != NoEdge && t2 != NoEdge &&
               (t3 == NoEdge || t1 + t2 < t3)) {
                 c[i][j] = t1 + t2;
                 kay[i][j] = k;}
            }
}

template<class T>
void AdjacencyWDigraph<T>::tSP(int i)
{// Backtracking code for traveling salesperson.
   if (i == n) {// at parent of a leaf
      // complete tour by adding last two edges
      if (a[x[n-1]][x[n]] != NoEdge &&
         a[x[n]][1] != NoEdge &&
         (cc + a[x[n-1]][x[n]] + a[x[n]][1] < bestc ||
         bestc == NoEdge)) {// better tour found
         for (int j = 1; j <= n; j++)
            bestx[j] = x[j];
         bestc = cc + a[x[n-1]][x[n]] + a[x[n]][1];}
      }
   else {// try out subtrees
      for (int j = i; j <= n; j++)
         // is move to subtree labeled x[j] possible?
         if (a[x[i-1]][x[j]] != NoEdge &&
               (cc + a[x[i-1]][x[i]] < bestc ||
                bestc == NoEdge)) {// yes
            // search this subtree
            Swap(x[i], x[j]);
            cc += a[x[i-1]][x[i]];
            tSP(i+1);
            cc -= a[x[i-1]][x[i]];
            Swap(x[i], x[j]);}
      }
}

template<class T>
T AdjacencyWDigraph<T>::TSP(int v[])
{// Traveling salesperson by backtracking.
 // Return cost of best tour, return tour in v[1:n].
   // initialize for tSP
   x = new int [n+1];
   // x is identity permutation
   for (int i = 1; i <= n; i++)
      x[i] = i;
   bestc = NoEdge;
   bestx = v;  // use array v to store best tour
   cc = 0;

   // search permutations of x[2:n]
   tSP(2);

   delete [] x;
   return bestc;
}

#include "minheap.h"
template<class T>
class MinHeapNode {
   friend AdjacencyWDigraph<T>;
   public:
      operator T () const {return lcost;}
   private:
      T lcost,  // lower bound on cost of tours in subtree
        cc,     // cost of partial tour
        rcost;  // min additional cost to complete tour
      int s,    // partial tour is x[0:s]
          *x;   // vertex array, x[s+1:n-1] gives remaining
                // vertices to be added to partial tour x[0:s]
};

template<class T>
T AdjacencyWDigraph<T>::BBTSP(int v[])
{// Min cost branch-and-bound
 // traveling-salesperson code.
   // define a max heap for up to
   // 1000 live nodes
   MinHeap<MinHeapNode<T> > H(1000);

   T *MinOut = new T [n+1];
   // compute MinOut[i] = cost of min-cost edge
   // leaving vertex i
   T MinSum = 0;  // sum of min-cost out edges
   for (int i = 1; i <= n; i++) {
      T Min = NoEdge;
      for (int j = 1; j <= n; j++)
         if (a[i][j] != NoEdge && 
                 (a[i][j] < Min || Min == NoEdge))
            Min = a[i][j];
      if (Min == NoEdge) return NoEdge; // no route
      MinOut[i] = Min;
      MinSum += Min;
      }

   // initial E-node is tree root
   MinHeapNode<T> E;
   E.x = new int [n];
   for (i = 0; i < n; i++)
      E.x[i] = i + 1;
   E.s = 0;           // partial tour is x[1:0]
   E.cc = 0;          // its cost is zero
   E.rcost = MinSum;  // will go up by this or more
   T bestc = NoEdge;  // no tour found so far

   // search permutation tree
   while (E.s < n - 1) {// not at leaf
      if (E.s == n - 2) {// parent of leaf
         // complete tour by adding 2 edges
         // see if new tour is better
         if (a[E.x[n-2]][E.x[n-1]] != NoEdge &&
             a[E.x[n-1]][1] != NoEdge && (E.cc +
             a[E.x[n-2]][E.x[n-1]] + a[E.x[n-1]][1]
             < bestc || bestc == NoEdge)) {
             // better tour found
             bestc = E.cc + a[E.x[n-2]][E.x[n-1]]
                          + a[E.x[n-1]][1];
             E.cc = bestc;
             E.lcost = bestc;
             E.s++;
             H.Insert(E);}
         else delete [] E.x;}  // done with E-node
      else {// generate children
         for (int i = E.s + 1; i < n; i++)
            if (a[E.x[E.s]][E.x[i]] != NoEdge) {
               // feasible child, bound path cost
               T cc = E.cc + a[E.x[E.s]][E.x[i]];
               T rcost = E.rcost - MinOut[E.x[E.s]];
               T b = cc + rcost;  // lower bound
               if (b < bestc || bestc == NoEdge) {
                   // subtree may have better leaf
                   // save root in max heap
                   MinHeapNode<T> N;
                   N.x = new int [n];
                   for (int j = 0; j < n; j++)
                      N.x[j] = E.x[j];
                   N.x[E.s+1] = E.x[i];
                   N.x[i] = E.x[E.s+1];
                   N.cc = cc;
                   N.s = E.s + 1;
                   N.lcost = b;
                   N.rcost = rcost;
                   H.Insert(N);}
               }  // end of feasible child
         delete [] E.x;}  // done with this node

      try {H.DeleteMin(E);}        // get next E-node
      catch (OutOfBounds) {break;} // no nodes left
      }

   if (bestc == NoEdge) return NoEdge; // no route
   // copy best route into v[1:n]
   for (i = 0; i < n; i++)
      v[i+1] = E.x[i];

   while (true) {// free all nodes in min heap
      delete [] E.x;
      try {H.DeleteMin(E);}
      catch (OutOfBounds) {break;}
      }

   return bestc;
}

#endif
