
// iterator for adjaceny graphs

#ifndef AdjacencyIterator_
#define AdjacencyIterator_

#include "awdgph2.h"

template<class T>
class AdjacencyIterator {
   public:
      int Begin(AdjacencyWDigraph<T>& G, int i);
      int NextVertex();
   private:
      int row;  // row of array to use
      int col;  // last column examined
      AdjacencyWDigraph<T> *H;    // pointer to graph 
};

template<class T>
int AdjacencyIterator<T>::Begin(AdjacencyWDigraph<T>& G, int i)
{// Return first vertex adjacent to vertex i.
   if (i < 1 || i > G.n) throw OutOfBounds();

   // save vertex and pointer to G
   // for later use by NextVertex
   row = i;
   H = &G;

   // look for first adjacent vertex
   for (int j = 1; j <= G.n; j++)
      if (G.a[i][j] != G.NoEdge) {// j is first one
         col = j;
         return j;}

   col = G.n; // no adjacent vertex
   return 0;
}

template<class T>
int AdjacencyIterator<T>::NextVertex()
{// Return next vertex adjacent to vertex row.

   // find next adjacent vertex
   for (int j = col + 1; j <= H->n; j++)
      if (H->a[row][j] != H->NoEdge) {// j is next vertex
         col = j;
         return j;}

   col = H->n; // no next vertex
   return 0;
}

#endif
