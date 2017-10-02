
// adjacency matrix representation of a weighted directed graph

#ifndef adjacencyWDigraph_
#define adjacencyWDigraph_

#include <iostream>
#include <sstream>
#include <iterator>
#include "graph.h"
#include "weightedEdge.h"
#include "vertexIterator.h"
#include "make2dArrayNoCatch.h"
#include "delete2dArray.h"
#include "myExceptions.h"
#include "arrayQueue.h"
#include "graphChain.h"
#include "minHeap.h"

using namespace std;

template <class T>
class adjacencyWDigraph : public graph<T>
{
   protected:
      int n;           // number of vertices
      int e;           // number of edges
      T **a;           // adjacency array
      T noEdge;        // denotes absent edge

   public:
      adjacencyWDigraph(int numberOfVertices = 0, T theNoEdge = 0)
      {// Constructor.
         // validate number of vertices
         if (numberOfVertices < 0)
            throw illegalParameterValue("number of vertices must be >= 0");
         n = numberOfVertices;
         e = 0;
         noEdge = theNoEdge;
         make2dArray(a, n + 1, n + 1);
         for (int i = 1; i <= n; i++)
            // initialize adjacency matrix
            fill(a[i], a[i] + n + 1, noEdge);
      }
      
      ~adjacencyWDigraph() {delete2dArray(a, n + 1);}

      int numberOfVertices() const {return n;}
   
      int numberOfEdges() const {return e;}
   
      bool directed() const {return true;}
   
      bool weighted() const {return true;}
   
      bool existsEdge(int i, int j) const
      {// Return true iff (i,j) is an edge of the graph. 
         if (i < 1 || j < 1 || i > n || j > n || a[i][j] == noEdge)
            return false;
         else
            return true;
      }
      
      void insertEdge(edge<T> *theEdge)
      {// Insert edge theEdge into the digraph; if the edge is already
       // there, update its weight to theEdge.weight().
         int v1 = theEdge->vertex1();
         int v2 = theEdge->vertex2();
         if (v1 < 1 || v2 < 1 || v1 > n || v2 > n || v1 == v2)
         {
            ostringstream s;
            s << "(" << v1 << "," << v2 
              << ") is not a permissible edge";
            throw illegalParameterValue(s.str());
         }
   
         if (a[v1][v2] == noEdge)  // new edge
            e++;
         a[v1][v2] = theEdge->weight();
      }
      
      void eraseEdge(int i, int j)
      {// Delete the edge (i,j).
         if (i >= 1 && j >= 1 && i <= n && j <= n && a[i][j] != noEdge)
         {
            a[i][j] = noEdge;
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
   
         // count out edges from vertex theVertex
         int sum = 0;
         for (int j = 1; j <= n; j++)
            if (a[theVertex][j] != noEdge)
               sum++;
   
         return sum;
      }
      
      int inDegree(int theVertex) const
      {// Return in-degree of vertex theVertex.
         checkVertex(theVertex);
   
         // count in edges at vertex theVertex
         int sum = 0;
         for (int j = 1; j <= n; j++)
            if (a[j][theVertex] != noEdge)
               sum++;
   
         return sum;
      }

      class myIterator : public vertexIterator<T>
      {
         public:
            myIterator(T* theRow, T theNoEdge, int numberOfVertices)
            {
               row = theRow;
               noEdge = theNoEdge;
               n = numberOfVertices;
               currentVertex = 1;
            }
      
            ~myIterator() {}
      
            int next()
            {// Return next vertex if any. Return 0 if no next vertex.
               // find next adjacent vertex
               for (int j = currentVertex; j <= n; j++)
                  if (row[j] != noEdge)
                  {
                     currentVertex = j + 1;
                     return j;
                  }
               // no next adjacent vertex
               currentVertex = n + 1;
               return 0;
            }
      
            int next(T& theWeight)
            {// Return next vertex if any. Return 0 if no next vertex.
             // Set theWeight = edge weight.
               // find next adjacent vertex
               for (int j = currentVertex; j <= n; j++)
                  if (row[j] != noEdge)
                  {
                     currentVertex = j + 1;
                     theWeight = row[j];
                     return j;
                  }
               // no next adjacent vertex
               currentVertex = n + 1;
               return 0;
            }

         protected:
            T* row;           // row of adjacency matrix
            T noEdge;         // theRow[i] == noEdge iff no edge to i
            int n;            // number of vertices
            int currentVertex;
      };

      myIterator* iterator(int theVertex)
      {// Return iterator for vertex theVertex.
         checkVertex(theVertex);
         return new myIterator(a[theVertex], noEdge, n);
      }
      

      void output(ostream& out) const
      {// Output the adjacency matrix.
         for (int i = 1; i <= n; i++)
         {
            copy(a[i] + 1, a[i] + n + 1, ostream_iterator<T>(out, "  "));
            out << endl;
         }
      }

      void bfs(int v, int reach[], int label)
      {// Breadth-first search. reach[i] is set to label for
       // all vertices reachable from vertex v.
         arrayQueue<int> q(10);
         reach[v] = label;
         q.push(v);
         while (!q.empty())
         {
            // remove a labeled vertex from the queue
            int w = q.front();
            q.pop();
   
            // mark all unreached vertices adjacent from w
            for (int u = 1; u <= n; u++)
               // visit an adjacent vertex of w
               if (a[w][u] != noEdge && reach[u] == 0)
               {// u is an unreached vertex
                  q.push(u);
                  reach[u] = label; // mark reached
               }
         }
      }

      void shortestPaths(int sourceVertex,
                         T* distanceFromSource, int* predecessor)
      {// Find shortest paths from sourceVertex.
       // Return shortest distances in distanceFromSource.
       // Return predecessor information in predecessor.
         if (sourceVertex < 1 || sourceVertex > n)
            throw illegalParameterValue("Invalid source vertex");
   
         if (!weighted())
            throw undefinedMethod
            ("adjacencyWDigraph::shortestPaths() not defined for unweighted graphs");

         graphChain<int> newReachableVertices;
   
         // initialize
         for (int i = 1; i <= n; i++)
         {
            distanceFromSource[i] = a[sourceVertex][i];
            if (distanceFromSource[i] == noEdge)
               predecessor[i] = -1;
            else
            {
               predecessor[i] = sourceVertex; 
               newReachableVertices.insert(0, i);
            }
         }
         distanceFromSource[sourceVertex] = 0;
         predecessor[sourceVertex] = 0;  // source vertex has no predecessor
      
         // update distanceFromSource and predecessor
         while (!newReachableVertices.empty())
         {// more paths exist
            // find unreached vertex v with least distanceFromSource
            chain<int>::iterator iNewReachableVertices
                                 = newReachableVertices.begin();
            chain<int>::iterator theEnd = newReachableVertices.end();
            int v = *iNewReachableVertices;
            iNewReachableVertices++;
            while (iNewReachableVertices != theEnd)
            {
               int w = *iNewReachableVertices;
               iNewReachableVertices++;
               if (distanceFromSource[w] < distanceFromSource[v])
                  v = w;
            }
      
            // next shortest path is to vertex v, delete v from
            // newReachableVertices and update distanceFromSource
            newReachableVertices.eraseElement(v);
            for (int j = 1; j <= n; j++)
            {
               if (a[v][j] != noEdge && (predecessor[j] == -1 ||
         	   distanceFromSource[j] > distanceFromSource[v] + a[v][j]))
               {
                  // distanceFromSource[j] decreases
                  distanceFromSource[j] = distanceFromSource[v] + a[v][j];
                  // add j to newReachableVertices
                  if (predecessor[j] == -1)
                     // not reached before
                     newReachableVertices.insert(0, j);
                  predecessor[j] = v;
               }
            }
         }
      }

      template <class T>
      void allPairs(T **c, int **kay)
      {// Dynamic programming all pairs shortest paths algorithm.
       // Compute c[i][j] and kay[i][j] for all i and j.
         if (!weighted())
            throw undefinedMethod
            ("adjacencyWDigraph::allPairs() not defined for unweighted graphs");
   
         // initialize c[i][j] = c(i,j,0)
         for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
               c[i][j] = a[i][j];
               kay[i][j] = 0;
            }
         for (int i = 1; i <= n; i++)
            c[i][i] = 0;
         
         // compute c[i][j] = c(i,j,k)
         for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
               for (int j = 1; j <= n; j++)
                  if (c[i][k] != noEdge && c[k][j] != noEdge &&
                     (c[i][j] == noEdge || c[i][j] > c[i][k] + c[k][j]))
                  {// smaller value for c[i][j] found
                       c[i][j] = c[i][k] + c[k][j];
                       kay[i][j] = k;
                  }
      }

      T btSalesperson(int *bestTour)
      {// Traveling salesperson by backtracking.
       // bestTour[1:n] is set to best tour.
       // Return cost of best tour.
         if (!weighted())
            throw undefinedMethod
            ("adjacencyWDigraph::btSalesperson() not defined for unweighted graphs");
         // set partialTour to identity permutation
         partialTour = new int [n + 1];
         for (int i = 1; i <= n; i++)
            partialTour[i] = i;
   
         costOfBestTourSoFar = noEdge;
         bestTourSoFar = bestTour;
         costOfPartialTour = 0;
      
         // search permutations of partialTour[2:n]
         rTSP(2);
      
         return costOfBestTourSoFar;
      }

      // struct used by least-cost branch-and-bound traveling salesperson
      struct heapNode
      {
         // data members
         T lowerCost;            // lower bound on cost of tours in subtree
         T costOfPartialTour;    // cost of partial tour
         T minAdditionalCost;    // min additional cost to complete tour
         int sizeOfPartialTour;  // partial tour is
         int *partialTour;       // partialTour[sizeOfPartialTour+1:n-1]
                                 // gives remaining vertices to be added
                                 // to partialTour[0:sizeOfPartialTour]
         // constructors
         heapNode() {}

         heapNode(T lC, T cOPT, T mAC, int sOPT, int* pT)
         {
            lowerCost = lC;
            costOfPartialTour = cOPT;
            minAdditionalCost = mAC;
            sizeOfPartialTour = sOPT;
            partialTour = pT;
         }
   
         operator int() {return lowerCost;}

         operator>(const heapNode right)
            {return lowerCost > right.lowerCost;}
      };
      
      T leastCostBBSalesperson(int *bestTour)
      {// least-cost branch-and-bound code to find a shortest tour
       // bestTour[i] set to i'th vertex on shortest tour
       // Return cost of shortest tour.
         if (!weighted())
            throw undefinedMethod
            ("adjacencyWDigraph::leastCostBBSalesperson() not defined for unweighted graphs");

         minHeap<heapNode> liveNodeMinHeap;
      
         // costOfMinOutEdge[i] = cost of least-cost edge leaving vertex i
         T *costOfMinOutEdge = new T [n + 1];
         T sumOfMinCostOutEdges = 0;
         for (int i = 1; i <= n; i++)
         {// compute costOfMinOutEdge[i] and sumOfMinCostOutEdges
            T minCost = noEdge;
            for (int j = 1; j <= n; j++)
               if (a[i][j] != noEdge && (minCost == noEdge ||
                   minCost > a[i][j]))
                  minCost = a[i][j];
   
            if (minCost == noEdge) return noEdge; // no route
            costOfMinOutEdge[i] = minCost;
            sumOfMinCostOutEdges += minCost;
         }
      
         // initial E-node is tree root
         heapNode eNode(0, 0, sumOfMinCostOutEdges, 0, new int [n]);
         for (int i = 0; i < n; i++)
            eNode.partialTour[i] = i + 1;
         T costOfBestTourSoFar = noEdge;            // no tour found so far
         int *partialTour = eNode.partialTour;      // shorthand for
                                                    // eNode.partialTour
         // search permutation tree
         while (eNode.sizeOfPartialTour < n - 1)
         {// not at leaf
            partialTour = eNode.partialTour;
            if (eNode.sizeOfPartialTour == n - 2)
            {// parent of leaf
               // complete tour by adding two edges
               // see whether new tour is better
               if (a[partialTour[n - 2]][partialTour[n - 1]] != noEdge
                   && a[partialTour[n - 1]][1] != noEdge
                   && (costOfBestTourSoFar == noEdge ||
                      eNode.costOfPartialTour
                      + a[partialTour[n - 2]][partialTour[n - 1]]
                      + a[partialTour[n - 1]][1]
                      < costOfBestTourSoFar))
               {// better tour found
                  costOfBestTourSoFar = eNode.costOfPartialTour
                          + a[partialTour[n - 2]][partialTour[n - 1]]
                          + a[partialTour[n - 1]][1];
                   eNode.costOfPartialTour = costOfBestTourSoFar;
                   eNode.lowerCost = costOfBestTourSoFar;
                   eNode.sizeOfPartialTour++;
                   liveNodeMinHeap.push(eNode);
               }
            } 
            else
            {// generate children
               for (int i = eNode.sizeOfPartialTour + 1; i < n; i++)
                  if (a[partialTour[eNode.sizeOfPartialTour]]
                      [partialTour[i]] != noEdge)
                  {
                     // feasible child, bound path cost
                     T costOfPartialTour = eNode.costOfPartialTour
                         + a[partialTour[eNode.sizeOfPartialTour]]
                            [partialTour[i]];
                     T minAdditionalCost = eNode.minAdditionalCost
                               -  costOfMinOutEdge[partialTour
                                  [eNode.sizeOfPartialTour]];
                     T leastCostPossible = costOfPartialTour
                                           + minAdditionalCost;
                     if (costOfBestTourSoFar == noEdge ||
                       leastCostPossible < costOfBestTourSoFar)
                     {// subtree may have better leaf, put root in min heap
                         heapNode hNode(leastCostPossible,
                                        costOfPartialTour,
                                        minAdditionalCost,
                                        eNode.sizeOfPartialTour + 1,
                                        new int [n]);
                         for (int j = 0; j < n; j++)
                            hNode.partialTour[j] = partialTour[j];
                         hNode.partialTour[eNode.sizeOfPartialTour + 1] =
                                  partialTour[i];
                         hNode.partialTour[i] =
                                  partialTour[eNode.sizeOfPartialTour + 1];
                         liveNodeMinHeap.push(hNode);
                     }
                  }
               }
      
            // get next E-node
            delete [] eNode.partialTour;
            if (liveNodeMinHeap.empty()) break;
            eNode = liveNodeMinHeap.top();
            liveNodeMinHeap.pop();
         }
      
         if (costOfBestTourSoFar == noEdge)
            return NULL; // no route
   
         // copy best route into bestTour[1:n]
         for (int i = 0; i < n; i++)
            bestTour[i + 1] = partialTour[i];
      
         return costOfBestTourSoFar;
      }
      
   protected:
      void rTSP(int currentLevel)
      {// Recursive backtracking code for traveling salesperson.
       // Search the permutation tree for best tour. Start  at a node
       // at currentLevel.
         if (currentLevel == n)
         {// at parent of a leaf
            // complete tour by adding last two edges
            if (a[partialTour[n - 1]][partialTour[n]] != noEdge &&
                a[partialTour[n]][1] != noEdge &&
                (costOfBestTourSoFar == noEdge ||
                 costOfPartialTour + a[partialTour[n - 1]][partialTour[n]]
                 + a[partialTour[n]][1] < costOfBestTourSoFar))
            {// better tour found
               copy(partialTour + 1, partialTour + n + 1, bestTourSoFar + 1);
               costOfBestTourSoFar = costOfPartialTour
                                + a[partialTour[n - 1]][partialTour[n]]
                                + a[partialTour[n]][1];
            }
         }
         else
         {// try out subtrees
            for (int j = currentLevel; j <= n; j++)
               // is move to subtree labeled partialTour[j] possible?
               if (a[partialTour[currentLevel - 1]][partialTour[j]] != noEdge
                   && (costOfBestTourSoFar == noEdge ||
                    costOfPartialTour +
                      a[partialTour[currentLevel - 1]][partialTour[j]]
                      < costOfBestTourSoFar))
               {// search this subtree
                  swap(partialTour[currentLevel], partialTour[j]);
                  costOfPartialTour += a[partialTour[currentLevel - 1]]
                                        [partialTour[currentLevel]];
                  rTSP(currentLevel + 1);
                  costOfPartialTour -= a[partialTour[currentLevel - 1]]
                                        [partialTour[currentLevel]];
                  swap(partialTour[currentLevel], partialTour[j]);
               }
         }
      }

      // class data members used by btSalesperson
      static int *partialTour;
      static int *bestTourSoFar;
      static T costOfBestTourSoFar;
      static T costOfPartialTour;
   
};

int* adjacencyWDigraph<int>::partialTour;
int* adjacencyWDigraph<int>::bestTourSoFar;
int adjacencyWDigraph<int>::costOfBestTourSoFar;
int adjacencyWDigraph<int>::costOfPartialTour;
int* adjacencyWDigraph<float>::partialTour;
int* adjacencyWDigraph<float>::bestTourSoFar;
float adjacencyWDigraph<float>::costOfBestTourSoFar;
float adjacencyWDigraph<float>::costOfPartialTour;
int* adjacencyWDigraph<double>::partialTour;
int* adjacencyWDigraph<double>::bestTourSoFar;
double adjacencyWDigraph<double>::costOfBestTourSoFar;
double adjacencyWDigraph<double>::costOfPartialTour;
      
// overload <<
template <class T>
ostream& operator<<(ostream& out, const adjacencyWDigraph<T>& x)
   {x.output(out); return out;}
#endif
