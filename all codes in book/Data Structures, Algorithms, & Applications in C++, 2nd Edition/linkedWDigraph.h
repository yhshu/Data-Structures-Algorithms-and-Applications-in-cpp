// linked adjacency list representation of a weighted digraph

#ifndef linkedWDigraph_
#define linkedWDigraph_


#include <iostream>
#include <sstream>
#include "graph.h"
#include "graphChain.h"
#include "weightedEdge.h"
#include "vertexIterator.h"
#include "myExceptions.h"

using namespace std;

//**************************************************************************
// struct used for element type in graph chain
template <class T>
struct wEdge
{// vertex and weight pair
   int vertex;
   T weight;
   wEdge(int theVertex = 0, T theWeight = 0)
      {vertex = theVertex; weight = theWeight;}
   operator int() const {return vertex;}
};

// overload <<
template <class T>
ostream& operator<<(ostream& out, const wEdge<T>& x)
   {out << x.vertex << " " << x.weight << " "; return out;}
//**************************************************************************

// T is data type of edge weight
template <class T>
class linkedWDigraph : public graph<T>
{
   protected:
      int n;                         // number of vertices
      int e;                         // number of edges
      graphChain<wEdge<T> > *aList;  // adjacency lists
      
   public:
      linkedWDigraph(int numberOfVertices = 0)
      {// Constructor.
         if (numberOfVertices < 0)
            throw illegalParameterValue
                  ("number of vertices must be >= 0");
         n = numberOfVertices;
         e = 0;
         aList = new graphChain<wEdge<T> > [n + 1];
      }

      ~linkedWDigraph() {delete [] aList;}
      
      int numberOfVertices() const {return n;}
   
      int numberOfEdges() const {return e;}
   
      bool directed() const {return true;}
   
      bool weighted() const {return true;}
   
      bool existsEdge(int i, int j) const
      {// Return true iff (i,j) is an edge.
         if (i < 1 || j < 1 || i > n || j > n
             || aList[i].indexOf(wEdge<T>(j)) == -1)
            return false;
         else
            return true;
      }
      
      void insertEdge(edge<T> *theEdge)
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
   
         if (aList[v1].indexOf(wEdge<T>(v2)) == -1) 
         {// new edge
            aList[v1].insert(0, wEdge<T>(v2, theEdge->weight()));
            e++;
         }
      }
      
      void insertEdgeNoCheck(edge<T> *theEdge)
      {// Insert an edge. No validation checks performed.
         aList[theEdge->vertex1()].insert(0,
               wEdge<T>(theEdge->vertex2(), theEdge->weight()));
         e++;
      }
   
   
      void eraseEdge(int i, int j)
      {
         if (i >= 1 && j >= 1 && i <= n && j <= n)
         {
            wEdge<T> *v = aList[i].eraseElement(j);
            if (v != NULL)  // edge (i,j) did exist
               e--;
         }
      }
      
      void checkVertex(int theVertex) const
      {// Verify that i is a valid vertex.
         if (theVertex < 1 || theVertex > n)
         {
            ostringstream s;
            s << "no vertex " << theVertex;
            throw illegalParameterValue(s.str());
         }
      }
      
      int degree(int theVertex) const
         {throw undefinedMethod("degree() undefined");}
   
      int outDegree(int theVertex) const
      {// Return out-degree of vertex theVertex.
         checkVertex(theVertex);
         return aList[theVertex].size();
      }
      
      int inDegree(int theVertex) const
      {
         checkVertex(theVertex);
   
         // count in-edges at vertex theVertex
         int sum = 0;
         for (int j = 1; j <= n; j++)
            if (aList[j].indexOf(wEdge<T>(theVertex)) != -1)
               sum++;
   
         return sum;
      }

      class myIterator : public vertexIterator<int>
      {
         public:
            myIterator(chainNode<wEdge<T> > *theNode)
               {currentNode = theNode;}
      
            ~myIterator() {}
      
            int next()
            {// Return next vertex if any. Return 0 if no next vertex.
               // find next adjacent vertex
               if (currentNode == NULL)
                  return 0;
               int nextVertex = currentNode->element.vertex;
               currentNode = currentNode->next;
               return nextVertex;
            }
      
            int next(T& theWeight)
            {// Return next vertex if any. Return 0 if no next vertex.
             // Set theWeight = edge weight.
               // find next adjacent vertex
               if (currentNode == NULL)
                  return 0;
               int nextVertex = currentNode->element.vertex;
               theWeight = currentNode->element.weight;
               currentNode = currentNode->next;
               return nextVertex;
            }
      
         protected:
            chainNode<wEdge<T> > *currentNode;
      };

      myIterator* iterator(int theVertex)
      {// Return iterator for vertex theVertex.
         checkVertex(theVertex);
         return new myIterator(aList[theVertex].firstNode);
      }
      

      void output(ostream& out) const
      {// Output the adjacency matrix.
         for (int i = 1; i <= n; i++)
            out << aList[i] << endl;
      }
};
      
// overload <<
template <class T>
ostream& operator<<(ostream& out, const linkedWDigraph<T>& x)
   {x.output(out); return out;}
#endif
