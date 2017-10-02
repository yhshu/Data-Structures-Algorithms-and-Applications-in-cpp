// max-profit branch-and-bound knapsack

#include <iostream>
#include <iterator>
#include "maxHeap.h"
#include "mergeSort.h"

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
   double upperProfit;
   double profit;
   double weight;
   int upperWeight;    // upper weight of live node
   int level;          // level of live node

   // constructors
   heapNode() {};

   heapNode(bbNode* theLiveNode, double theUpperProfit, double theProfit,
            double theWeight, int theLevel)
   {
      liveNode = theLiveNode;
      upperProfit = theUpperProfit;
      profit = theProfit;
      weight = theWeight;
      level = theLevel;
   }

   operator<(const heapNode right)
      {return upperProfit < right.upperProfit;}

   // type conversion to enable arithmetics etc.
   operator double() {return upperProfit;}
};


struct element
{
   // data members
   int id;   // object identifier
   double profitDensity;

   // constructors
   element() {}

   element(int theID, double theProfitDensity)
   {
      id = theID;
      profitDensity = theProfitDensity;
   }

   operator double() {return profitDensity;}
};

// global variables
double capacity;
int numberOfObjects;
double *weight;
double *profit;
double weightOfCurrentPacking;
double profitFromCurrentPacking;
int *bestPackingSoFar;
maxHeap<heapNode> liveNodeMaxHeap;

double maxProfitBBKnapsack();
void addLiveNode(double, double, double, int, bbNode*, bool);
double profitBound(int);

double knapsack(double *theProfit, double *theWeight, int theNumberOfObjects,
                double theCapacity, int *bestPacking)
{// theProfit[1:theNumberOfObjects] is array of object profits
 // theWeight[1:theNumberOfObjects] is array of object weights
 // theCapacity is knapsack capacity
 //  bestPacking[1:theNumberOfObjects] is set to best knapsack filling.
 // Return profit of best filling.
   capacity = theCapacity;
   numberOfObjects = theNumberOfObjects;

   // define an element array for profit densities
   element *q  = new element [numberOfObjects];

   // set up densities in q[0:numberOfObjects-1] and
   // sum the weights and profits
   double weightSum = 0.0;         // will be sum of weights
   double profitSum = 0.0;         // will be sum of profits
   for (int i = 1; i <= numberOfObjects; i++)
   {
      q[i - 1] = element(i, theProfit[i] / theWeight[i]);
      profitSum += theProfit[i];
      weightSum += theWeight[i];
   }

   if (weightSum <= capacity)   // all objects fit
   {
      fill(bestPacking + 1, bestPacking + numberOfObjects + 1, 1);
      return profitSum;
   }

   // sort into increasing density order
   mergeSort(q, numberOfObjects);

   // initialize globals
   profit = new double [numberOfObjects + 1];
   weight = new double [numberOfObjects + 1];
   for (int i = 1; i <= numberOfObjects; i++)
   {// profits and weights in decreasing density order
      profit[i] = theProfit[q[numberOfObjects - i].id];
      weight[i] = theWeight[q[numberOfObjects - i].id];
   }
   weightOfCurrentPacking = 0.0;
   profitFromCurrentPacking = 0.0;
   bestPackingSoFar = new int [numberOfObjects + 1];

   // find best profit and construct packing
   double maxProfit = maxProfitBBKnapsack();
   for (int i = 1 ; i <= numberOfObjects; i++)
      bestPacking[q[numberOfObjects - i].id] = bestPackingSoFar[i];
   return maxProfit;
}

double maxProfitBBKnapsack()
{// Max-profit branch-and-bound search of solution space tree.
 // Set bestPackingSoFar[i] = 1 iff object i is in knapsack in best filling.
 // Return profit of best knapsack filling.
   // initialize for level 1 start
   bbNode* eNode = NULL;
   int eNodeLevel = 1;
   double maxProfitSoFar = 0.0;
   double maxPossibleProfitInSubtree = profitBound(1);

   // search subset space tree
   while (eNodeLevel != numberOfObjects + 1)
   {// not at leaf
      // check left child
      double weightOfLeftChild = weightOfCurrentPacking
                                 + weight[eNodeLevel];
      if (weightOfLeftChild <= capacity)
      {// feasible left child
         if (profitFromCurrentPacking + profit[eNodeLevel]
             > maxProfitSoFar)
            maxProfitSoFar = profitFromCurrentPacking 
                             + profit[eNodeLevel];
         addLiveNode(maxPossibleProfitInSubtree,
                     profitFromCurrentPacking + profit[eNodeLevel],
                     weightOfCurrentPacking + weight[eNodeLevel],
                     eNodeLevel + 1, eNode, true);
      }
      maxPossibleProfitInSubtree = profitBound(eNodeLevel + 1);

      // check right child
      if (maxPossibleProfitInSubtree >= maxProfitSoFar)
         // right child has prospects
         addLiveNode(maxPossibleProfitInSubtree,
                     profitFromCurrentPacking,
                     weightOfCurrentPacking,
                     eNodeLevel + 1, eNode, false);

      // get next E-node, heap cannot be empty
      heapNode nextENode = liveNodeMaxHeap.top();
      liveNodeMaxHeap.pop();
      eNode = nextENode.liveNode;
      weightOfCurrentPacking = nextENode.weight;
      profitFromCurrentPacking = nextENode.profit;
      maxPossibleProfitInSubtree = nextENode.upperProfit;
      eNodeLevel = nextENode.level;
   }

   // construct bestPackingSoFar[] by following path
   // from eNode to the root
   for (int j = numberOfObjects; j > 0; j--)
   {
      bestPackingSoFar[j] = (eNode->leftChild) ? 1 : 0;
      eNode = eNode->parent;
   }

   return profitFromCurrentPacking;
}

void addLiveNode(double upperProfit, double theProfit,
                 double theWeight, int theLevel, bbNode* theParent,
                 bool leftChild)
{// Add a new live node to the max heap.
 // Also add the new node to the solution space tree.
 // upperProfit = upper bound on profit for the live node.
 // theProfit = profit of new live node.
 // theWeight = weight of new live node.
 // theLevel = level of live node.
 // theParent = parent of new node.
 // leftChild is true iff new node is left child of theParent.
   // create the new node of the solution space tree
   bbNode* b = new bbNode(theParent, leftChild);

   // put corresponding heap node into max heap
   liveNodeMaxHeap.push(heapNode(b, upperProfit, theProfit,
                                 theWeight, theLevel));
}

double profitBound(int currentLevel)
{// Bounding function.
 // Return upper bound on value of best leaf in subtree.
   double remainingCapacity = capacity - weightOfCurrentPacking;
   double profitBound = profitFromCurrentPacking;

   // fill remaining capacity in order of profit density
   while (currentLevel <= numberOfObjects &&
          weight[currentLevel] <= remainingCapacity)
   {
      remainingCapacity -= weight[currentLevel];
      profitBound += profit[currentLevel];
      currentLevel++;
   }

   // take fraction of next object
   if (currentLevel <= numberOfObjects)
      profitBound += profit[currentLevel] / weight[currentLevel]
                     * remainingCapacity;
   return profitBound;
}

void main(void)
{
   double p[] = {0, 6, 3, 5, 4, 6};
   double w[] = {0, 2, 2, 6, 5, 4};
   int n = 5;
   int c = 10;
   int *bestx = new int [n + 1];
   cout << "Optimal value is " << knapsack(p, w, n, c, bestx) << endl;
   cout << "Packing vector is ";
   copy(bestx + 1, bestx + n + 1, ostream_iterator<int>(cout, "  "));
   cout << endl;
}
