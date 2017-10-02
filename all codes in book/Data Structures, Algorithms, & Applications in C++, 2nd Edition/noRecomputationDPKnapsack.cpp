// dynamic programming recursive knapsack without recomputation

#include <iostream>
#include <math.h>
#include "make2dArrayNoCatch.h"

using namespace std;

// global variables
int *profit;
int *weight;
int numberOfObjects;
int **fArray;  // array of f values

int f(int i, int theCapacity)
{// Return f(i,theCapacity). Do not recpute an f value.
   // check if already computed
   if (fArray[i][theCapacity] >= 0)
      return fArray[i][theCapacity];

   // not yet computed
   if (i == numberOfObjects)
   {// use Equation 19.1
      // compute and save f(i,theCapacity)
      fArray[i][theCapacity] = (theCapacity < weight[numberOfObjects])
                                ? 0 : profit[numberOfObjects];
      return fArray[i][theCapacity];
   }
   // use Equation 19.2
   if (theCapacity < weight[i])
      // object i does not fit
      fArray[i][theCapacity] = f(i + 1, theCapacity); 
   else
      // object i fits, try both possibilities
      fArray[i][theCapacity] = max(f(i + 1, theCapacity),
                   f(i + 1, theCapacity - weight[i]) + profit[i]);

   return fArray[i][theCapacity];
}

void main(void)
{
   cout << "Enter number of objects and knapsack capacity" << endl;
   int knapsackCapacity;
   cin >> numberOfObjects >> knapsackCapacity;
   profit = new int [numberOfObjects + 1];
   weight = new int [numberOfObjects + 1];

   for (int i = 1; i <= numberOfObjects; i++)
   {
      cout << "Enter profit and weight of object " << i << endl;
      cin >> profit[i] >> weight[i];
   }

   make2dArray(fArray, numberOfObjects + 1, knapsackCapacity + 1);
   for (int i = 1; i <= numberOfObjects; i++)
      for (int j = 0; j <= knapsackCapacity; j++)
         fArray[i][j] = -1;

   cout << "Optimal value is " << f(1, knapsackCapacity) << endl;
}
