// iterative code for container loading by backtracking

#include <iostream>
#include <iterator>

using namespace std;


int maxLoading(int *weight, int numberOfContainers, int capacity,
               int *bestLoading)
{// weight[1:numberOfContainers] are container weights
 // capacity ship capacity
 // bestLoading[1:numberOfContainers] is solution array
 // Return weight of max loading.
   // initialize for root
   int currentLevel = 1;
   int *currentLoading = new int [numberOfContainers + 1];
          // currentLoading[1:i-1] is path to current node
   int maxWeightSoFar = 0;
   int weightOfCurrentLoading = 0;
   int remainingWeight = 0;
   for (int j = 1; j <= numberOfContainers; j++)
      remainingWeight += weight[j];

   // search the tree
   while (true)
   {// move down and left as far as possible
      while (currentLevel <= numberOfContainers &&
             weightOfCurrentLoading + weight[currentLevel] <= capacity)
      {// move to left child
         remainingWeight -= weight[currentLevel];
         weightOfCurrentLoading += weight[currentLevel];
         currentLoading[currentLevel] = 1;
         currentLevel++;
      }

      if (currentLevel > numberOfContainers)
      {// leaf reached
         for (int j = 1; j <= numberOfContainers; j++)
            bestLoading[j] = currentLoading[j];
         maxWeightSoFar = weightOfCurrentLoading;
      }
      else
      {// move to right child
         remainingWeight -= weight[currentLevel];
         currentLoading[currentLevel] = 0;
         currentLevel++;
      }

      // back up if necessary
      while (weightOfCurrentLoading + remainingWeight <= maxWeightSoFar)
      {// this subtree does not have a better leaf, back up
         currentLevel--;
         while (currentLevel > 0 && currentLoading[currentLevel] == 0)
         {// back up from a right child
            remainingWeight += weight[currentLevel];
            currentLevel--;
         }

         if (currentLevel == 0)
            return maxWeightSoFar;

         // move to right subtree
         currentLoading[currentLevel] = 0;
         weightOfCurrentLoading -= weight[currentLevel];
         currentLevel++;
      }
   }
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
