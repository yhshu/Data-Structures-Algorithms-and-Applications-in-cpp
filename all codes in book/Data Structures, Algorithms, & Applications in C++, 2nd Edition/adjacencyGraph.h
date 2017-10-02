// adjacency matrix representation of an undirected graph

#ifndef adjacencyGraph_
#define adjacencyGraph_

#include <iostream>
#include <sstream>
#include <iterator>
#include "adjacencyWGraph.h"
#include "unweightedEdge.h"
#include "maxHeap.h"

using namespace std;

class adjacencyGraph : public adjacencyWGraph<bool>
{
   public:
      adjacencyGraph(int numberOfVertices = 0)
         : adjacencyWGraph<bool> (numberOfVertices, false) {}

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
         a[v2][v1] = true;
      }

      bool weighted() const {return false;}

      int btMaxClique(int *maxClique)
      {// Solve max-clique problem using backtracking.
       // Set maxClique[] so that maxClique[i] = 1 iff i is in max clique.
       // Return size of max clique.
         // initialize for rClique
         currentClique = new int [n + 1];
         sizeOfCurrentClique = 0;
         sizeOfMaxCliqueSoFar = 0;
         maxCliqueSoFar = maxClique;
      
         // find max clique
         rClique(1);
         return sizeOfMaxCliqueSoFar;
      }

      // structs used by max-profit branch-and-bound max clique
      struct bbNode
      {
         // instance data members
         bbNode* parent;
         bool leftChild;    // true iff left child of parent
   
         // constructors
         bbNode() {}
   
         bbNode(bbNode* theParent, bool theLeftChild)
         {
            parent = theParent;
            leftChild = theLeftChild;
         }
      };
      
      struct heapNode
      {
         // data members
         bbNode* liveNode;
         int upperSize;     // upper bound on clique size in this subtree
         int cliqueSize;    // size of clique at this node
         int level;
   
         // constructors
         heapNode() {}
   
         heapNode(bbNode* theLiveNode, int theUpperSize,
                  int theCliqueSize, int theLevel)
         {
            liveNode = theLiveNode;
            upperSize = theUpperSize;
            cliqueSize = theCliqueSize;
            level = theLevel;
         }
   
         operator<(const heapNode right)
            {return upperSize < right.upperSize;}
   
         operator int() {return upperSize;}
      };

      int maxProfitBBMaxClique(int *maxClique)
      {// Max-profit branch-and-bound code to find a max clique.
       // maxClique[i] is set to 1 iff i is in max clique.
       // Return size of max clique.
         // initialize for level 1 start
         bbNode* eNode = NULL;
         int eNodeLevel = 1;
         int sizeOfCliqueAtENode = 0;
         int sizeOfMaxCliqueSoFar = 0;
      
         // search subset space tree
         while (eNodeLevel != n + 1)
         {// while not at leaf
            // see if vertex eNodeLevel is connected to all
            // vertices in the current clique
            bool connected = true;
            bbNode* currentNode = eNode;
            for (int j = eNodeLevel - 1; j > 0;
                 currentNode = currentNode->parent, j--)
               if (currentNode->leftChild && !a[eNodeLevel][j])
               {// j is in the clique but no edge between eNodeLevel and j
                  connected = false;
                  break;
                }
      
            if (connected)
            {// left child is feasible
               if (sizeOfCliqueAtENode + 1 > sizeOfMaxCliqueSoFar)
                  sizeOfMaxCliqueSoFar = sizeOfCliqueAtENode + 1;
               addLiveNode(sizeOfCliqueAtENode + n - eNodeLevel + 1,
                  sizeOfCliqueAtENode + 1, eNodeLevel + 1, eNode, true);
            }
   
            if (sizeOfCliqueAtENode + n - eNodeLevel >= sizeOfMaxCliqueSoFar)
               // right child has prospects
               addLiveNode(sizeOfCliqueAtENode + n - eNodeLevel,
                  sizeOfCliqueAtENode, eNodeLevel + 1, eNode, false);
      
            // get next E-node, heap cannot be empty
            heapNode nextENode = liveNodeMaxHeap.top();
            liveNodeMaxHeap.pop();
            eNode = nextENode.liveNode;
            sizeOfCliqueAtENode = nextENode.cliqueSize;
            eNodeLevel = nextENode.level;
         }
      
         // construct maxClique[] by following path from eNode to the root
         for (int j = n; j > 0; j--)
         {
            maxClique[j] = (eNode->leftChild) ? 1 : 0;
            eNode = eNode->parent;
         }
      
         return sizeOfMaxCliqueSoFar;
      }
      
   protected:
      // recursive backtracking code to compute largest clique
      void rClique(int currentLevel)
      {// search from a node at currentLevel
         if (currentLevel > n)
         {// at leaf, found a larger clique
          // update maxCliqueSoFar and sizeOfMaxCliqueSoFar
            for (int j = 1; j <= n; j++)
               maxCliqueSoFar[j] = currentClique[j];
            sizeOfMaxCliqueSoFar = sizeOfCurrentClique;
            return;
         }
      
         // not at leaf; see whether vertex currentLevel
         // is connected to others in current clique
         bool connected = true;
         for (int j = 1; j < currentLevel; j++)
            if (currentClique[j] == 1 && !a[currentLevel][j])
            {// vertex currentLevel not connected to j
               connected = false;
               break;
            }
      
         if (connected)
         {// try left subtree
            currentClique[currentLevel] = 1;  // add to clique
            sizeOfCurrentClique++;
            rClique(currentLevel + 1);
            sizeOfCurrentClique--;
         }
      
         if (sizeOfCurrentClique + n - currentLevel > sizeOfMaxCliqueSoFar)
         {// try right subtree
            currentClique[currentLevel] = 0;
            rClique(currentLevel + 1);
         }
      }

      // class data members used by backtracking max clique
      static int *currentClique;
      static int sizeOfCurrentClique;
      static int sizeOfMaxCliqueSoFar;
      static int *maxCliqueSoFar;

      // class data member used by max-profit branch-and-bound max clique
      static maxHeap<heapNode> liveNodeMaxHeap;
      
      void addLiveNode(int upperSize, int theSize, int theLevel,
                        bbNode* theParent, bool leftChild)
      {// Add a new live node to the max heap.
       // Also add the live node to the solution space tree.
       // theSize = size of clique at this live node.
       // theParent = parent of new node.
       // leftChild = true iff new node is left child of theParent.
         // create the new node of the solution space tree
         bbNode* b = new bbNode(theParent, leftChild);
   
         // insert corresponding node into max heap
         liveNodeMaxHeap.push(heapNode(b, upperSize, theSize, theLevel));
      }
};

int* adjacencyGraph::currentClique;
int adjacencyGraph::sizeOfCurrentClique;
int adjacencyGraph::sizeOfMaxCliqueSoFar;
int* adjacencyGraph::maxCliqueSoFar;
maxHeap<adjacencyGraph::heapNode> adjacencyGraph::liveNodeMaxHeap;

#endif
