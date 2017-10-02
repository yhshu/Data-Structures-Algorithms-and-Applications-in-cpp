// simple unite/find using 1D array

#include <iostream>
#include "myExceptions.h"

using namespace std;

int *equivClass,   // equivalence class array
    n;             // number of elements

void initialize(int numberOfElements)
{// Initialize numberOfElements classes with one element each.
   n = numberOfElements;
   equivClass = new int [n + 1];
   for (int e = 1; e <= n; e++)
      equivClass[e] = e;
}

void unite(int classA, int classB)
{// Unite the classes classA and classB.
 // Assume classA != classB
   for (int k = 1; k <= n; k++)
      if (equivClass[k] == classB)
         equivClass[k] = classA;
}

int find(int theElement)
{// Find the class that contains theElement.
   return equivClass[theElement];
}

int main(void)
{
   initialize(10);
   unite(1,2);
   unite(3,4);
   unite(1,3);
   for (int i = 1; i < 7; i++)
      cout << "Element " << i << " is in equivalence class "
           << find(i) << endl;
}
