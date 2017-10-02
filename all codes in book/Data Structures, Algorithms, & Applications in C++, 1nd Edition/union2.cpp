// union/find using chains and size info
// simulated pointers used

#include <iostream.h>
#include "swap.h"
#include "enode.h"
#include "xcept.h"

EquivNode *node; // array of nodes

void Initialize(int n)
{// Initialize n classes with one element each.
   node = new EquivNode [n + 1];
   
   for (int e = 1; e <= n; e++) {
      node[e].E = e;
      node[e].link = 0;
      node[e].size = 1;
      }
}

void Union(int i, int j)
{// Union the classes i and j.

   // make i smaller class
   if (node[i].size > node[j].size)
      Swap(i,j);

   //  change E values of smaller class
   int k;
   for (k = i; node[k].link; k = node[k].link)
      node[k].E = j;
   node[k].E = j; // last node in chain

   // insert chain i after first node in chain j
   // and update new chain size
   node[j].size += node[i].size;
   node[k].link = node[j].link;
   node[j].link = i;
}

int Find(int e)
{// Find the class that contains element i.
   return node[e].E;
}

void main(void)
{
   int n = 10;
   Initialize(n);
   Union(1,2);
   Union(3,4);
   Union(2,4);
   cout << '1' << ' ' << Find(1) << ' ' << '2' << ' ' << Find(2) << endl;
   cout << '3' << ' ' << Find(3) << ' ' << '4' << ' ' << Find(4) << endl;
   cout << '5' << ' ' << Find(5) << ' ' << '6' << ' ' << Find(6) << endl;
}
