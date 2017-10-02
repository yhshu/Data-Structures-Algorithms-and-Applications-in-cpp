
// file unetwork.h
// functions for undirected networks

#ifndef UNetwork_
#define UNetwork_

#include <iostream.h>
#include "edgenode.h"
#include "wnetwork.h"
#include "unfind.h"
#include "minheap.h"

template<class T>
class UNetwork : virtual public WNetwork<T>
{
  public:
     bool Kruskal(EdgeNode<T> t[]);
};

template<class T>
bool UNetwork<T>::Kruskal(EdgeNode<T> t[])
{// Find a min cost spanning tree using Kruskal's
 // method.  Return false if not connected.  If
 // connected, return min spanning tree in t[0:n-2].

   int n = Vertices();
   int e = Edges();
   // set up array of network edges
   InitializePos();  // graph iterator
   EdgeNode<T> *E = new EdgeNode<T> [e+1];
   int k = 0;        // cursor for E
   for (int i = 1; i <= n; i++) {
      // get all edges incident to i
      int j;
      T c;
      First(i, j, c);
      while (j) {    // j is adjacent from i
         if (i < j) {// add edge to E
   	    E[++k].weight = c;
            E[k].u = i;
            E[k].v = j;}
         Next(i, j, c);
         }
      }
   
   // put edges in min heap
   MinHeap<EdgeNode<T> > H(1);
   H.Initialize(E, e, e);
   
   UnionFind U(n); // union/find structure
   
   // extract edges in cost order and select/reject
   k = 0;  // use as cursor for t now
   while (e && k < n - 1) {
      // spanning tree not complete &
      // edges remain
      EdgeNode<T> x;
      H.DeleteMin(x); // min cost edge
      e--;
      int a = U.Find(x.u);
      int b = U.Find(x.v);
      if (a != b) {// select edge
         t[k++] = x;
         U.Union(a,b);}
      }
   
   DeactivatePos();
   H.Deactivate();
   return (k == n - 1);
}

#endif
