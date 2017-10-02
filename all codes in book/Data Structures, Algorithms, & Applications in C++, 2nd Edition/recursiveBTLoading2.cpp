// refined recursive backtracking code for container loading
// onto two ships
// code finds weight of max loading for first ship only

#include <iostream>

using namespace std;


// global variables
int numberOfContainers;
int *weight;     // weight[1:numberOfContainers] is container weights
int capacity;
int weightOfCurrentLoading = 0;
int maxWeightSoFar = 0;
int remainingWeight;


void rLoad(int currentLevel)
{// search from a node at currentLevel
   if (currentLevel > numberOfContainers)
   {// at a leaf
      maxWeightSoFar = weightOfCurrentLoading;
      return;
   }

   // not at a leaf, check subtrees
   remainingWeight -= weight[currentLevel];
   if (weightOfCurrentLoading + weight[currentLevel] <= capacity)
   {// try left subtree
      weightOfCurrentLoading += weight[currentLevel];
      rLoad(currentLevel + 1);
      weightOfCurrentLoading -= weight[currentLevel];
   }
   if (weightOfCurrentLoading + remainingWeight > maxWeightSoFar)
      // try right subtree
      rLoad(currentLevel+1);
   remainingWeight += weight[currentLevel];
}


void main(void)
{
   int w[] = {0, 7, 2, 6, 5, 4};
   weight = w;
   numberOfContainers = 5;
   capacity = 10;

   // initialize remainingWeight to sum of all weights
   remainingWeight = 0;
   for (int i = 1; i <= numberOfContainers; i++)
      remainingWeight += weight[i];

   rLoad(1);
   cout << "Value of max loading is " << maxWeightSoFar << endl;
}
