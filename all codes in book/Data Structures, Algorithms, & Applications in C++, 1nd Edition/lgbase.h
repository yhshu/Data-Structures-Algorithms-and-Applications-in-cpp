// file lgraph.h
#ifndef LinkedGraph_
#define LinkedGraph_

#include "lbase.h"

class LinkedGraph : public LinkedBase<int> {
   public:
      LinkedGraph(int Vertices = 10)
        : LinkedBase<int> (Vertices) {}
      int Add(int i, int j);
      int AddNoCheck(int i, int j);
      int Delete(int i, int j);
      int Degree(int i);
};

int LinkedGraph::Add(int i, int j)
{// Add edge (i,j).
   if (i < 1 || i > n || i == j || Exist(i, j)) return 0;
   return AddNoCheck(i, j);
}

int LinkedGraph::AddNoCheck(int i, int j)
{// Add edge (i,j).  Perform no checks.
   if (!h[i].Insert(0,j)) return 0;
   if (!h[j].Insert(0,i)) return 0;
   e++;
   return 1;
}

int LinkedGraph::Delete(int i, int j)
{// Delete edge (i,j).
   if (i < 1 || i > n) return 0;
   h[i].Delete(j);
   h[j].Delete(i);
   e--;
   return 1;
}

int LinkedGraph::Degree(int i)
{// Return degree of vertex i.
   if (i < 1 || i > n) return 0;
   return h[i].Length();
}

#endif
