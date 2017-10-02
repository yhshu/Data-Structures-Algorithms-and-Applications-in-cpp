// first recursive backtracking code to load containers onto 2 ships
// code finds weight of max loading for first ship only

#include <iostream>

using namespace std;

// global variables
int numberOfContainers;
int *weight;    // weight[1:numberOfContainers] gives the container weights
int capacity;
int weightOfCurrentLoading = 0;
int maxWeightSoFar = 0;

void rLoad(int currentLevel)
{// search from a node at currentLevel
   if (currentLevel > numberOfContainers)
   {// at a leaf
      if (weightOfCurrentLoading > maxWeightSoFar)
         maxWeightSoFar = weightOfCurrentLoading;
      return;
   }
   // not at a leaf, check subtrees
   if (weightOfCurrentLoading + weight[currentLevel] <= capacity)
   {// try left subtree; i.e., x[currentLevel] = 1
      weightOfCurrentLoading += weight[currentLevel];
      rLoad(currentLevel + 1);
      weightOfCurrentLoading -= weight[currentLevel];
   }
   rLoad(currentLevel + 1);  // try right subtree
}

void main(void)
{
   int w[] = {0, 7, 2, 6, 5, 4};
   weight = w;
   numberOfContainers = 5;
   capacity = 10;
   rLoad(1);
   cout << "Value of max loading is " << maxWeightSoFar << endl;
}
