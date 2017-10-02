// adjacency matrix representation of a directed graph

#ifndef adjacencyDigraph_
#define adjacencyDigraph_

#include <iostream>
#include <sstream>
#include <iterator>
#include "adjacencyWDigraph.h"
#include "unweightedEdge.h"

using namespace std;

class adjacencyDigraph : public adjacencyWDigraph<bool>
{
   public:
      adjacencyDigraph(int numberOfVertices = 0)
         : adjacencyWDigraph<bool> (numberOfVertices, false) {}

      void insertEdge(edge<bool> *theEdge)
      {// Insert an edge.
         int v1 = theEdge->vertex1();
         int v2 = theEdge->vertex2();
         if (v1 < 1 || v2 < 1 || v1 > n || v2 > n || v1 == v2)
         {
            ostringstream s;
            s << "(" << v1 << "," << v2 
              << ") is not a permissible edge";
            throw illegalParameterValue(s.str());
         }
   
         if (!a[v1][v2])  // new edge
            e++;
         a[v1][v2] = true;
      }

      bool weighted() const {return false;}
};
#endif
