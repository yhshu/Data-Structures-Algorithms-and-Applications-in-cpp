// second version of FIFO branch-and-bound code for two ship loading
// code finds weight of best loading for first ship only

#include <iostream>
#include "arrayQueue.h"

using namespace std;

// global variables
int numberOfContainers;
int maxWeightSoFar;
arrayQueue<int> liveNodeQueue;


int maxLoading(int *weight, int theNumberOfContainers, int capacity)
{// FIFO branch-and-bound search of solution space.
 // weight[1:theNumberOfContainers] = container weights
 // capacity = ship capacity
 // Return weight of best loading.
   // initialize global variables
   numberOfContainers = theNumberOfContainers;
   maxWeightSoFar = 0;
   liveNodeQueue.push(-1);  // end-of-level marker

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
         // add to queue unless leaf
         if (eNodeLevel < numberOfContainers)
            liveNodeQueue.push(leftChildWeight);
      }

      // check right child
      if (eNodeWeight + remainingWeight > maxWeightSoFar
          && eNodeLevel < numberOfContainers)
          // right child may lead to better leaf
          liveNodeQueue.push(eNodeWeight);

      // get next E-node
      eNodeWeight = liveNodeQueue.front();
      liveNodeQueue.pop();
      if (eNodeWeight == -1)
      {// end of level
         if (liveNodeQueue.empty())         // no more live nodes
            return maxWeightSoFar;
         liveNodeQueue.push(-1);            // end-of-level marker
         // get next E-node
         eNodeWeight = liveNodeQueue.front();
         liveNodeQueue.pop();
         eNodeLevel++;
         remainingWeight -= weight[eNodeLevel];
      }
   }
}

void main(void)
{
   int w[] = {0, 2, 2, 6, 5, 5};
   int n = 5;
   int c = 16;
   cout << "Value of max loading is " << maxLoading(w, n, c) << endl;
}
