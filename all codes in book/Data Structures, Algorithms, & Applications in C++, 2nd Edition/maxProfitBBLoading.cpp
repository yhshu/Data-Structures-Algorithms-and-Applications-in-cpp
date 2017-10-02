// Max profit branch-and-bound code for two ship loading
// code to find best loading and its value.

#include <iostream>
#include <iterator>
#include "maxHeap.h"

using namespace std;

struct bbNode
{
   // data members
   bbNode* parent;        // pointer to parent node
   bool leftChild;        // true iff left child of parent

   // constructor
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
   int upperWeight;    // upper weight of live node
   int level;          // level of live node

   // constructors
   heapNode() {};

   heapNode(bbNode* theLiveNode, int theUpperWeight, int theLevel)
   {
      liveNode = theLiveNode;
      upperWeight = theUpperWeight;
      level = theLevel;
   }

   operator<(const heapNode right)
      {return upperWeight < right.upperWeight;}

   // type conversion to enable arithmetics etc.
   operator int() {return upperWeight;}
};

// global variable
maxHeap<heapNode> liveNodeMaxHeap;

void addLiveNode(int, int, bbNode*, bool);

int maxLoading(int *weight, int numberOfContainers, int capacity,
               int *bestLoading)
{// Max-profit branch-and-bound search of solution space.
 // weight[1:numberOfContainers] = container weights
 // capacity = ship capacity
 // bestLoading[1:numberOfContainer] gives best loading.
 // Return weight of best loading.

   // initialize for level 1 E-node
   bbNode* eNode = NULL;
   int eNodeLevel = 1;
   int eNodeWeight = 0;

   // remainingWeight[j] will be sum of weight[j+1:n]
   int *remainingWeight = new int [numberOfContainers + 1];
   remainingWeight[numberOfContainers] = 0;
   for (int j = numberOfContainers - 1; j > 0; j--)
      remainingWeight[j] = remainingWeight[j + 1] + weight[j + 1];

   // search subset space tree
   while (eNodeLevel != numberOfContainers + 1)
   {// not at a leaf
      // check children of E-node
      if (eNodeWeight + weight[eNodeLevel] <= capacity)
         // feasible left child
         addLiveNode(eNodeWeight + weight[eNodeLevel] +
                     remainingWeight[eNodeLevel], eNodeLevel + 1,
                     eNode, true);
      // right child is always feasible
      addLiveNode(eNodeWeight + remainingWeight[eNodeLevel],
                  eNodeLevel + 1, eNode, false);

      // get next E-node, heap cannot be empty
      heapNode nextENode = liveNodeMaxHeap.top();
      liveNodeMaxHeap.pop();
      eNodeLevel = nextENode.level;
      eNode = nextENode.liveNode;
      eNodeWeight = nextENode.upperWeight
                    - remainingWeight[eNodeLevel - 1];
   }

   // construct bestLoading[] by following path from eNode to the root
   for (int j = numberOfContainers; j > 0; j--)
   {
      bestLoading[j] = (eNode->leftChild) ? 1 : 0;
      eNode = eNode->parent;
   }

   return eNodeWeight;
}

void addLiveNode(int upperWeight, int level,
                 bbNode* theParent, bool leftChild)
{// Add a new live node to the live node max heap.
 // Also add the live node to the solution space tree.
 // theParent is the parent of the new live node.
 // leftChild is true iff the new live node is
 // the left child of theParent.
   // create the new node of the solution space tree
   bbNode* b = new bbNode(theParent, leftChild);

   // put corresponding heap node into max heap
   liveNodeMaxHeap.push(heapNode(b, upperWeight, level));
}


/** test program */
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
