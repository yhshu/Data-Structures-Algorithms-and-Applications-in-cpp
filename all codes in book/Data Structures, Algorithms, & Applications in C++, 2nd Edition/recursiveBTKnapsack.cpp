// backtracking solution for knapsack problem

#include <iostream>
#include "mergeSort.h"

using namespace std;


struct element
{
   // data members
   int id;   // object identifier
   double profitDensity;

   // constructors
   element() {};

   element(int theID, double theProfitDensity)
   {
      id = theID;
      profitDensity = theProfitDensity;
   }

   // type conversion to enable arithmetic and other operations
   operator double() {return profitDensity;}
};


// global variables
double capacity;
int numberOfObjects;
double *weight;   // weight[1:numberOfObjects] --> object weights
double *profit;
double weightOfCurrentPacking;
double profitFromCurrentPacking;
double maxProfitSoFar;

void rKnap(int);
double profitBound(int);

double knapsack(double *theProfit, double *theWeight,
                int theNumberOfObjects, double theCapacity)
{// theProfit[1:theNumberOfObjects] is array of object profits
 // theWeight[1:theNumberOfObjects] is array of object weights
 // theCapacity is knapsack capacity
 // Return profit of best filling.
   // set global variables
   capacity = theCapacity;
   numberOfObjects = theNumberOfObjects;
   weightOfCurrentPacking = 0.0;
   profitFromCurrentPacking = 0.0;
   maxProfitSoFar = 0.0;

   // define an element array for profit densities
   element *q  = new element [numberOfObjects];

   // set up densities in q[0:n-1]
   for (int i = 1; i <= numberOfObjects; i++)
      q[i - 1] = element(i, theProfit[i] / theWeight[i]);

   // sort into increasing density order
   mergeSort(q, numberOfObjects);

   // initialize remaining globals
   profit = new double [numberOfObjects + 1];
   weight = new double [numberOfObjects + 1];
   for (int i = 1; i <= numberOfObjects; i++)
   {// profits and weights in decreasing density order
      profit[i] = theProfit[q[numberOfObjects - i].id];
      weight[i] = theWeight[q[numberOfObjects - i].id];
   }

   rKnap(1);  // compute max profit
   return maxProfitSoFar;
}
   
// recursive function to find value of best filling
void rKnap(int currentLevel)
{// search from a node at currentLevel
   if (currentLevel > numberOfObjects)
   {// at a leaf
      maxProfitSoFar = profitFromCurrentPacking;
      return;
   }

   // not at a leaf, check subtrees
   if (weightOfCurrentPacking + weight[currentLevel] <= capacity)
   {// try left subtree
      weightOfCurrentPacking += weight[currentLevel];
      profitFromCurrentPacking += profit[currentLevel];
      rKnap(currentLevel + 1);
      weightOfCurrentPacking -= weight[currentLevel];
      profitFromCurrentPacking -= profit[currentLevel];
   }
   if (profitBound(currentLevel + 1) > maxProfitSoFar)
      rKnap(currentLevel + 1);   // try right subtree
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
   cout << "Optimal value is " << knapsack(p, w, n, c) << endl;
}
