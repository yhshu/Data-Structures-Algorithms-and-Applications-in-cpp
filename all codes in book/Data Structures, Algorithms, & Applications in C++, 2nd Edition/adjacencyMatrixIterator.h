
// adjacency matrix iterator

#ifndef adjacencyMatrixIterator_
#define adjacencyMatrixIterator_

#include "vertexIterator.h"

using namespace std;

template<class T>
class adjacencyMatrixIterator : public vertexIterator<T>
{
   public:
      adjacencyMatrixIterator(T* theRow, T theNoEdge, int numberOfVertices)
      {
         row = theRow;
         noEdge = theNoEdge;
         n = numberOfVertices;
         currentVertex = 1;
      }

      ~adjacencyMatrixIterator() {}

      pair<int, T>* next()
      {// Return (next vertex, edge weight) pair.
         // find next adjacent vertex
         for (int j = currentVertex; j <= n; j++)
            if (row[j] != noEdge)
            {
               currentVertex = j + 1;
               return new pair<int, T>(j, row[j]);
            }
         // no next adjacent vertex
         currentVertex = n + 1;
         return NULL;
      }

   protected:
      T* row;           // row of adjacency matrix
      T noEdge;         // theRow[i] == noEdge iff no edge to i
      int n;            // number of vertices
      int currentVertex;
};
#endif
