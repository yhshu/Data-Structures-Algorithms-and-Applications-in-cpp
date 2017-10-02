
// union/find with weighting and path splitting

#include <iostream.h>

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
 // Split path from e to root.
   int current = e,  // current node
       p,            // parent of current
       gp;           // grandparent of p

   // see if there are pointers to change
   if (root[current]) return current;
   p = parent[current];
   if (root[p]) return p;
   gp = parent[p];

   // at least one pointer to change
   while(true) {
      parent[current] = gp;
      if (root[gp]) return gp;
      // move current, p, and gp one
      // level up the tree
      current = p;
      p = gp;
      gp = parent[p];
      }
}

void Union(int i, int j)
{// Combine trees with roots i and j.
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
   cout << "Find(1) = " << Find(1) << " Find(2) = " << Find(2) << endl;
   cout << "Find(3) = " << Find(3) << " Find(4) = " << Find(4) << endl;
   cout << "Find(5) = " << Find(5) << " Find(6) = " << Find(6) << endl;
}
