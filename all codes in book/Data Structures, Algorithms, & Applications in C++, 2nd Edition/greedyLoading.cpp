// greedy container loading 

#include <iostream>
#include "container.h"
#include "heapSort.h"

using namespace std;

void containerLoading(container* c, int capacity,
                      int numberOfContainers, int* x)
{// Greedy algorithm for container loading.
 // Set x[i] = 1 iff container i, i >= 1 is loaded.
   // sort into increasing order of weight
   heapSort(c, numberOfContainers);
   
   int n = numberOfContainers;

   // initialize x
   for (int i = 1; i <= n; i++)
      x[i] = 0;
   
   // select containers in order of weight
   for (int i = 1; i <= n && c[i].weight <= capacity; i++)
   {// enough capacity for container c[i].id
      x[c[i].id] = 1;
      capacity -= c[i].weight;  // remaining capacity
   }
}

// test method 
void main(void)
{
   // initialize the containers
   const int n = 8;
   int w[] = {0, 60, 20, 40, 70, 30, 50, 10, 25};
   container c[n + 1];
   for (int i = 1; i <= n; i++)
   {
      c[i].id = i;
      c[i].weight = w[i];
   }
   int x[n + 1];

   // load the ship
   containerLoading(c, 150, n, x);

   // output loading vector
   cout << "Loading vector is ";
   copy(x + 1, x + n + 1, ostream_iterator<int>(cout, "  "));
   cout << endl;
}
