// FIFO branch-and-bound loading code to find best loading and its value

#include <iostream>
#include <iterator>
#include "arrayQueue.h"

using namespace std;

struct qNode
{
   // data members
   qNode *parent;         // pointer to parent node
   bool leftChild;        // true iff left child of parent
   int weight;            // weight of partial solution
                          // defined by path to this node

   // constructor
   qNode(qNode *theParent, bool theLeftChild, int theWeight)
   {
      parent = theParent;
      leftChild = theLeftChild;
      weight = theWeight;
   }
};

// global variables
int numberOfContainers;
int maxWeightSoFar;
arrayQueue<qNode*> liveNodeQueue;
qNode *bestENodeSoFar;
int *bestLoading;

void addLiveNode(int, int, qNode*, bool);

int maxLoading(int *weight, int theNumberOfContainers, int capacity,
               int *theBestLoading)
{// FIFO branch-and-bound search of solution space.
 // weight[1:theNumberOfContainers] = container weights
 // capacity = ship capacity
 // theBestLoading[1:theNumberOfContainers] is set to best loading.
 // Return weight of best loading.
   // initialize globals
   numberOfContainers = theNumberOfContainers;
   maxWeightSoFar = 0;
   liveNodeQueue.push(NULL);      // end-of-level marker
   qNode *eNode = NULL;
   bestENodeSoFar = NULL;
   bestLoading = theBestLoading;

   // initialize for level 1 E-node
   int eNodeLevel = 1;
   int eNodeWeight = 0;
   int remainingWeight = 0;
   for (int j = 2; j <= numberOfContainers; j++)
      remainingWeight += weight[j];

   // search subset space tree
   while (true)
   {
      // check left child of E-node
      int leftChildWeight = eNodeWeight + weight[eNodeLevel];
      if (leftChildWeight <= capacity)
      {// feasible left child
         if (leftChildWeight > maxWeightSoFar)
            maxWeightSoFar = leftChildWeight;
         addLiveNode(leftChildWeight, eNodeLevel, eNode, true); 
      }

      // check right child
      if (eNodeWeight + remainingWeight > maxWeightSoFar)
         addLiveNode(eNodeWeight, eNodeLevel, eNode, false);

      eNode = liveNodeQueue.front();
      liveNodeQueue.pop();
      if (eNode == NULL)
      {// end of level
         if (liveNodeQueue.empty()) break;    // no more live nodes
         liveNodeQueue.push(NULL);             // end-of-level pointer
         eNode = liveNodeQueue.front();
         liveNodeQueue.pop();
         eNodeLevel++;
         remainingWeight -= weight[eNodeLevel];
      }

      eNodeWeight = eNode->weight;
   }

   // construct bestLoading[] by following path from
   // bestENodeSoFar to root, bestLoading[numberOfContainers]
   // is set by addLiveNode
   for (int j = numberOfContainers - 1; j > 0; j--)
   {
      bestLoading[j] = (bestENodeSoFar->leftChild) ? 1 : 0;
      bestENodeSoFar = bestENodeSoFar->parent;
   }

   return maxWeightSoFar;
}

void addLiveNode(int theWeight, int theLevel,
                 qNode* theParent, bool leftChild)
{// Add a live node at level theLevel and having weight theWeight
 // to liveNodeQueue if not a leaf. If feasible leaf, set
 // bestLoading[numberOfContainers] = 1 iff leftChild is true.
 // theParent = parent of new node.
 // leftChild is true iff new node is left child of theParent.
   if (theLevel == numberOfContainers)
   {// feasible leaf
      if (theWeight == maxWeightSoFar)
      {// best leaf so far
        bestENodeSoFar = theParent;
        bestLoading[numberOfContainers] = (leftChild) ? 1 : 0;
      }
      return;
  }

   // not a leaf, add to queue
   qNode *b = new qNode(theParent, leftChild, theWeight);
   liveNodeQueue.push(b);
}

void main(void)
{
   int w[] = {0, 2, 2, 6, 5, 5};
   int c = 16;
   int n = 5;
   int *x = new int [n + 1];
   cout << "Value of max loading is " << maxLoading(w, n, c, x) << endl;
   cout << "Loading vector is ";
   copy(x + 1, x + n + 1, ostream_iterator<int>(cout, "  "));
   cout << endl;
}
