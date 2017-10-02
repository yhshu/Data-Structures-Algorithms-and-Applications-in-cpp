// iterative dynamic programming knapsack

#include <iostream>
#include <iterator>
#include <math.h>
#include "make2dArrayNoCatch.h"

using namespace std;


void knapsack(int *profit, int *weight, int numberOfObjects,
              int knapsackCapacity, int **f)
{// Iterative method to solve dynamic programming recurrence.
 // Computes f[1][knapsackCapacity] and f[i][y],
 // 2 <= i <= numberOfObjects, 0 <= y <= knapsackCapacity.
 // profit[1:numberOfObjects] gives object profits.
 // weight[1:numberOfObjects] gives object weights.

   // initialize f[numberOfObjects][]
   int yMax = min(weight[numberOfObjects] - 1, knapsackCapacity);
   for (int y = 0; y <= yMax; y++)
      f[numberOfObjects][y] = 0;
   for (int y = weight[numberOfObjects]; y <= knapsackCapacity; y++)
      f[numberOfObjects][y] = profit[numberOfObjects];
   
   // compute f[i][y], 1 < i < numberOfObjects
   for (int i = numberOfObjects - 1; i > 1; i--)
   {
      yMax = min(weight[i] - 1, knapsackCapacity);
      for (int y = 0; y <= yMax; y++)
         f[i][y] = f[i + 1][y];
      for (int y = weight[i]; y <= knapsackCapacity; y++)
         f[i][y] = max(f[i + 1][y], f[i + 1][y - weight[i]] + profit[i]);
   }

   // compute f[1][knapsackCapacity]
   f[1][knapsackCapacity] = f[2][knapsackCapacity];
   if (knapsackCapacity >= weight[1])
      f[1][knapsackCapacity] = max(f[1][knapsackCapacity],
                f[2][knapsackCapacity-weight[1]] + profit[1]);
}

void traceback(int **f, int *weight, int numberOfObjects,
                        int knapsackCapacity, int *x)
{// Compute solution vector x.
   for (int i = 1; i < numberOfObjects; i++)
      if (f[i][knapsackCapacity] == f[i+1][knapsackCapacity])
         // do not include object i
         x[i] = 0;
      else
      {// include object i
         x[i] = 1;
         knapsackCapacity -= weight[i];
      }
   x[numberOfObjects] = (f[numberOfObjects][knapsackCapacity] > 0)
                        ? 1 : 0;
}

void main(void)
{
   cout << "Enter number of objects and knapsack capacity" << endl;
   int numberOfObjects, knapsackCapacity;
   cin >> numberOfObjects >> knapsackCapacity;
   int* profit = new int [numberOfObjects + 1];
   int* weight = new int [numberOfObjects + 1];

   for (int i = 1; i <= numberOfObjects; i++)
   {
      cout << "Enter profit and weight of object " << i << endl;
      cin >> profit[i] >> weight[i];
   }

   int** f;
   make2dArray(f, numberOfObjects + 1, knapsackCapacity + 1);


   knapsack(profit, weight, numberOfObjects, knapsackCapacity, f);

   cout << "Optimal value is " << f[1][knapsackCapacity] << endl;
   cout << "Rest of table is" << endl;
   for (int i = 2; i <= numberOfObjects; i++)
   {
      copy(f[i], f[i] + knapsackCapacity + 1, ostream_iterator<int>(cout, "  "));
      cout << endl;
   }

   int *x = new int[numberOfObjects + 1];
   traceback(f, weight, numberOfObjects, knapsackCapacity, x);

   cout << endl;
   copy(x + 1, x + numberOfObjects + 1, ostream_iterator<int>(cout, "  "));
   cout << endl;
}
