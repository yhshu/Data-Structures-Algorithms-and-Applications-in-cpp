// dynamic programming recursive knapsack

#include <iostream>
#include <math.h>

using namespace std;

// global variables
int *profit;
int *weight;
int numberOfObjects;

int f(int i, int theCapacity)
{// Return f(i,theCapacity).
   if (i == numberOfObjects)
      return (theCapacity < weight[numberOfObjects])
              ? 0 : profit[numberOfObjects];
   if (theCapacity < weight[i])
      return f(i + 1, theCapacity); 
   return max(f(i + 1, theCapacity),
               f(i + 1, theCapacity - weight[i]) + profit[i]);
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

   cout << "Optimal value is " << f(1, knapsackCapacity) << endl;
}
