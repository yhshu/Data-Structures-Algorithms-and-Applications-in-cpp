// unite/find with weighting rule

#include <iostream>
#include "unionFindNode.h"

using namespace std;

unionFindNode *node;

void initialize(int numberOfElements)
{// Initialize numberOfElements trees, 1 element per set/class/tree.
  node = new unionFindNode[numberOfElements+1];
}

int find(int theElement)
{// Return root of tree containing theElement.
   while (!node[theElement].root)
      theElement = node[theElement].parent;  // move up one level
   return theElement;
}

void unite(int rootA, int rootB)
{// Combine trees with different roots rootA and rootB.
 // Use the weighting rule.
   if (node[rootA].parent < node[rootB].parent)
   {// rootA becomes subtree of rootB
      node[rootB].parent += node[rootA].parent;
      node[rootA].root = false;
      node[rootA].parent = rootB;
   }
   else
   {// rootB becomes subtree of rootA
      node[rootA].parent += node[rootB].parent;
      node[rootB].root = false;
      node[rootB].parent = rootA;
   }
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
