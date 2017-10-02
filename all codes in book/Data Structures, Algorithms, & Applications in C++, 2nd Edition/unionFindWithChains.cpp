// union/find using chains and size info
// integer pointers used

#include <iostream>
#include "equivNode.h"

using namespace std;

equivNode *node; // array of nodes
int n;           // number of elements

void initialize(int numberOfElements)
{// Initialize numberOfElements classes with one element each.
   n = numberOfElements;
   node = new equivNode [n + 1];
   
   for (int e = 1; e <= n; e++)
   {
      node[e].equivClass = e;
      node[e].next = 0;
      node[e].size = 1;
   }
}

void unite(int classA, int classB)
{// Unite the classes classA and classB.
 // Assume classA != classB
 // classA and classB are first elements in their chains

   // make classA smaller class
   if (node[classA].size > node[classB].size)
      swap(classA, classB);

   //  change equivClass values of smaller class
   int k;
   for (k = classA; node[k].next != 0; k = node[k].next)
      node[k].equivClass = classB;
   node[k].equivClass = classB; // last node in chain

   // insert chain classA after first node in chain classB
   // and update new chain size
   node[classB].size += node[classA].size;
   node[k].next = node[classB].next;
   node[classB].next = classA;
}

int find(int theElement)
{// Find the class that contains theElement.
   return node[theElement].equivClass;
}

int main(void)
{
   initialize(10);
   unite(1,2);
   unite(3,4);
   unite(2,4);
   for (int i = 1; i < 7; i++)
      cout << "Element " << i << " is in equivalence class "
           << find(i) << endl;
}
