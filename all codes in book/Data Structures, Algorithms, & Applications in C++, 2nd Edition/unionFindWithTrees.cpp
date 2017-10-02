// unite/find using trees
// simple version

#include <iostream>

using namespace std;

int *parent;

void initialize(int numberOfElements)
{// Initialize numberOfElements trees, 1 element per set/class/tree.
   parent = new int[numberOfElements + 1];
   for (int e = 1; e <= numberOfElements; e++)
      parent[e] = 0;
}

int find(int theElement)
{// Return root of tree that contains theElement.
   while (parent[theElement] != 0)
      theElement = parent[theElement];  // move up one level
   return theElement;
}

void unite(int rootA, int rootB)
{// Combine trees with different roots rootA and rootB.
   parent[rootB] = rootA;
}

void main(void)
{
   initialize(10);
   unite(1,2);
   unite(3,4);
   unite(1,3);
   cout << "find(1) = " << find(1) << " find(2) = " << find(2) << endl;
   cout << "find(3) = " << find(3) << " find(4) = " << find(4) << endl;
   cout << "find(5) = " << find(5) << " find(6) = " << find(6) << endl;
}
