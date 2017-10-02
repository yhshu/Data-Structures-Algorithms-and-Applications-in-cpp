
// file unetwork.h
// functions for undirected networks
// Prim's algorithm added

#ifndef UNetwork_
#define UNetwork_

#include <iostream.h>
#include "edgenode.h"
#include "vnode.h"
#include "wnetwork.h"
#include "unfind.h"
#include "minheap.h"
#include "modheap.h"

template<class T>
class UNetwork : virtual public WNetwork<T>
{
  public:
     bool Kruskal(EdgeNode<T> t[]);
     bool Prim(EdgeNode<T> t[]);
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

template<class T>
bool UNetwork<T>::Prim(EdgeNode<T> t[])
{// Find a min cost spanning tree using Prim's
 // method.  Return false if not connected.  If
 // connected, return min spanning tree in t[0:n-2].

   int n = Vertices();
   bool *selected = new bool [n+1];
   VertexNode1<T> *VN1 = new VertexNode1<T> [n+1];

   // start with vertex 1 in tree
   // initilize distance and modified min heap
   // of next candidates
   VN1[1].distance = 0;
   for (int i = 2; i <= n; i++) {
      VN1[i].distance = -1;
      selected[i] = false;
      }
   InitializePos();  // graph iterator

   // update distance for vertices adjacent to 1
   // and insert these vertices into a modified
   // min heap
   int v;
   T w;  // edge weight
   VertexNode2<T> VN2;  // used for modified min heap
   ModifiedMinHeap<T> *H;
   H = new ModifiedMinHeap<T> (n);
   First(1,v,w);
   while (v) {
      VN1[v].distance = w;
      VN1[v].nbr = 1;
      VN2.ID = v;
      VN2.distance = w;
      H->Insert(VN2);
      Next(1,v,w);
      }

   // select n-1 edges for spanning tree
   for (i = 0; i < n - 1; i++) {
      // get nearest unselected vertex
      try {H->DeleteMin(VN2);}
      catch (OutOfBounds)
         {// no next vertex
          return false;
         }

      // select VN2.ID
      EdgeNode<T> x;
      int u = VN2.ID;
      x.u = u;
      x.v = VN1[u].nbr;
      x.weight = VN1[u].distance;
      t[i] = x;
      selected[u] = true;

      // update distances
      First(u,v,w);
      while (v) {
         // VN1[v].distance may have changed
         if (!selected[v]) {
            if (VN1[v].distance == -1) {
               // v not in min heap
               VN1[v].distance = w;
               VN1[v].nbr = u;
               VN2.distance = w;
               VN2.ID = v;
               H->Insert(VN2);
               }
            else if (VN1[v].distance > w) {
                    // v is in the min heap
                    VN1[v].distance = w;
                    VN1[v].nbr = u;
                    VN2.distance = w;
                    VN2.ID = v;
                    H->Decrease(VN2);
                    }
            }
         Next(u,v,w);
         }               
      }   

   DeactivatePos();
   delete [] VN1;
   delete [] selected;
   delete H;
   return true;
}

#endif
