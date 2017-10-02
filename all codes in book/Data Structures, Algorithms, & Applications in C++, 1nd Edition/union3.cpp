// union/find using trees
// simple version

#include <iostream.h>

int *parent;

void Initialize(int n)
{// One element per set/class/tree.
   parent = new int[n+1];
   for (int e = 1; e <= n; e++)
      parent[e] = 0;
}

int Find(int e)
{// Return root of tree containing e.
   while (parent[e])
      e = parent[e];  // move up one level
   return e;
}

void Union(int i, int j)
{// Combine trees with roots i and j.
   parent[j] = i;
}

void main(void)
{
   Initialize(10);
   Union(1,2);
   Union(3,4);
   Union(1,3);
   cout << "Find(1) = " << Find(1) << " Find(2) = " << Find(2) << endl;
   cout << "Find(3) = " << Find(3) << " Find(4) = " << Find(4) << endl;
   cout << "Find(5) = " << Find(5) << " Find(6) = " << Find(6) << endl;
}
