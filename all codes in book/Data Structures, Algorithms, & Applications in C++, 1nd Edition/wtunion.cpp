// union/find with weighting rule

#include <iostream.h>
#include <stdlib.h>

int *parent;
bool *root;

void Initialize(int n)
{// One element per set/class/tree.
  root = new bool[n+1];
  parent = new int[n+1];
  for (int e = 1; e <= n; e++) {
     parent[e] = 1;
     root[e] = true;}
}

int Find(int e)
{// Return root of tree containing e.
   while (!root[e])
      e = parent[e];  // move up one level
   return e;
}

void Union(int i, int j)
{// Combine trees with roots i and j.
 // Use weighting rule.
   if (parent[i] < parent[j]) {
      // i becomes subtree of j
      parent[j] += parent[i];
      root[i] = false;
      parent[i] = j; }
   else {// j becomes subtree of i
      parent[i] += parent[j];
      root[j] = false;
      parent[j] = i;}
}

void main(void)
{
   Initialize(10);
   Union(1,2);
   Union(3,4);
   Union(1,3);
   cout << '1' << ' ' << Find(1) << ' ' << '2' << ' ' << Find(2) << endl;
   cout << '3' << ' ' << Find(3) << ' ' << '4' << ' ' << Find(4) << endl;
   cout << '5' << ' ' << Find(5) << ' ' << '6' << ' ' << Find(6) << endl;
}
