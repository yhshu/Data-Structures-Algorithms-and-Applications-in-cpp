// linked adjacency list representation of a graph

#ifndef linkedGraph_
#define linkedGraph_


#include <iostream>
#include <sstream>
#include "linkedDigraph.h"
#include "unweightedEdge.h"


using namespace std;

class linkedGraph : public linkedDigraph
{
   public:
      linkedGraph(int numberOfVertices = 0)
         : linkedDigraph(numberOfVertices) {}
   
      bool directed() const {return false;}
      
      void insertEdge(edge<bool> *theEdge)
      {// Insert an edge.
         int oldE = e;
         linkedDigraph::insertEdge(theEdge);
         if (e > oldE)
         {// new edge
            linkedDigraph::insertEdgeNoCheck(new unweightedEdge
                           (theEdge->vertex2(), theEdge->vertex1()));
            e--;  // compenstate for extra increment
         }
      }
      
      void insertEdgeNoCheck(edge<bool> *theEdge)
      {// Insert an edge. No validation checks performed.
            linkedDigraph::insertEdgeNoCheck(theEdge);
            linkedDigraph::insertEdgeNoCheck(new unweightedEdge
                           (theEdge->vertex2(), theEdge->vertex1()));
            e--;
      }
   
      void eraseEdge(int i, int j)
      {
         int oldE = e;
         linkedDigraph::eraseEdge(i, j);
         if (oldE > e) // edge exists
         {
            linkedDigraph::eraseEdge(j, i);
            e++;
         }
      }
      
      int degree(int theVertex) const
      {
         checkVertex(theVertex);
         return aList[theVertex].size();
      }

      int outDegree(int theVertex) const {return degree(theVertex);}
      
      int inDegree(int theVertex) const {return degree(theVertex);}
};
#endif
