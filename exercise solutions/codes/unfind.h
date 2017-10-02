
// file wtunion.h
// union/find using weighting and collapsing rules

#ifndef UnionFind_
#define UnionFind_


class UnionFind {
   public:
       UnionFind(int Size = 10);
      ~UnionFind() {delete [] parent;
                    delete [] root;}
      void Union(int, int);
      int Find(int);
   private:
      int *parent;  // parent array
      bool *root;   // root[i] is true iff i is a root
};

UnionFind::UnionFind(int n)
{// One element per set/class/tree.
   root = new bool[n+1];
   parent = new int[n+1];

   for (int e = 1; e <= n; e++) {
      parent[e] = 1;
      root[e] = true;}
}

int UnionFind::Find(int e)
{// Return root of tree containing e.
 // Compact path from e to root.
   int j = e;
   // find root
   while (!root[j])
      j = parent[j];
   
   // compact
   int f = e;  // start at e
   while (f != j) {// f is not root
      int pf = parent[f];
      parent[f] = j;  // move f to level 2
      f = pf;}        // f moves to old parent 

   return j;
}

void UnionFind::Union(int i, int j)
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

#endif;
