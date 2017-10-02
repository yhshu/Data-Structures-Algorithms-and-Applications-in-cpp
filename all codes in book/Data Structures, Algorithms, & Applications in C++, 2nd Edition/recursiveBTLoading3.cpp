// loading containers onto two ships via backtracking
// code finds max loading of first ship as well as its weight
// recursive version 

#include <iostream>
#include <iterator>

using namespace std;

// global variables
int numberOfContainers;
int *weight;
int capacity;
int weightOfCurrentLoading;
int maxWeightSoFar;
int remainingWeight;
int *currentLoading;
int *bestLoadingSoFar;

void rLoad(int);

int maxLoading(int *theWeight, int theNumberOfContainers,
               int theCapacity, int *bestLoading)
{// theWeight[1:theNumberOfContainers] gives container weights
 // theCapacity is capacity of ship
 // bestLoading[1:theNumberOfContainers] is solution array
 // Return weight of max loading.
   // initialize global variables
   numberOfContainers = theNumberOfContainers;
   weight = theWeight;
   capacity = theCapacity;
   weightOfCurrentLoading = 0;
   maxWeightSoFar = 0;
   currentLoading = new int [numberOfContainers + 1];
   bestLoadingSoFar = bestLoading;

   // initialize remainingWeight to sum of all weights
   for (int i = 1; i <= numberOfContainers; i++)
      remainingWeight += weight[i];

   // compute weight of best loading
   rLoad(1);
   return maxWeightSoFar;
}

// recursive function to find best loading
void rLoad(int currentLevel)
{// search from a node at currentLevel
   if (currentLevel > numberOfContainers)
   {// at a leaf, save better solution
      for (int j = 1; j <= numberOfContainers; j++)
         bestLoadingSoFar[j] = currentLoading[j];
      maxWeightSoFar = weightOfCurrentLoading;
      return;
   }

   // not at a leaf, check subtrees
   remainingWeight -= weight[currentLevel];
   if (weightOfCurrentLoading + weight[currentLevel] <= capacity)
   {// try left subtree
      currentLoading[currentLevel] = 1;
      weightOfCurrentLoading += weight[currentLevel];
      rLoad(currentLevel + 1);
      weightOfCurrentLoading -= weight[currentLevel];
   }
   if (weightOfCurrentLoading + remainingWeight > maxWeightSoFar)
   {
      currentLoading[currentLevel] = 0; // try right subtree
      rLoad(currentLevel + 1);
   }
   remainingWeight += weight[currentLevel];
}


void main(void)
{
   int w[] = {0, 7, 2, 6, 5, 4};
   int c = 10;
   int n = 5;
   int *x = new int [n + 1];

   // compute and output best loading
   cout << "Value of max loading is " << maxLoading(w, n, c, x) << endl;
   cout << "x values are ";
   copy(x + 1, x + n + 1, ostream_iterator<int>(cout, "  "));
   cout << endl;
}
