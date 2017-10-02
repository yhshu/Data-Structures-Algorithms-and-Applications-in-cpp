// max profit branch-and-bound loading
// finds best loading and its value

// will not compile with MaxLoading as a template function
// gives error: ambiguous call to overloaded function
// when invoked from main()
// MaxLoading has been changed to an integer function

#include <iostream.h>
#include "bbnode.h"
#include "maxheap.h"

template<class T>
void AddLiveNode(MaxHeap<HeapNode<T> > &H, bbnode *E,
                   T wt, bool ch, int lev)
{// Add a level lev live node with upper weight
 // wt to max heap H.  New node is a child of E.
 // ch is true iff new node is the left child.
   bbnode *b = new bbnode;
   b->parent = E;
   b->LChild = ch;
   HeapNode<T> N;
   N.uweight = wt;
   N.level = lev;
   N.ptr = b;
   H.Insert(N);
}

// template<class T>
// T MaxLoading(T w[], T c, int n, int bestx[])
int MaxLoading(int w[], int c, int n, int bestx[])
{// Return value of best loading.  Return best
 // loading in bestx.
 // Use max-profit branch and bound.
   // define a max heap for up to
   // 1000 live nodes
   // MaxHeap<HeapNode<T> > H(1000);
   MaxHeap<HeapNode<int> > H(1000);
   
   // define array of remaining weights
   // r[j] sum of weights w[j+1:n]
   // T *r = new T [n+1];
   int *r = new int [n+1];
   r[n] = 0;
   for (int j = n-1; j > 0; j--)
      r[j] = r[j+1] + w[j+1];

   // initialize for level 1 start
   int i = 1;          // level of E-node
   bbnode *E = 0;      // current E-node
   // int Ew = 0;           // weight of E-node
   int Ew = 0;           // weight of E-node

   // search subset space tree
   while (i != n+1) {// while not at leaf
      // check children of E-node
      if (Ew + w[i] <= c) {// feasible left child
         AddLiveNode(H, E, Ew+w[i]+r[i], true, i+1);}
      // right child
      AddLiveNode(H, E, Ew+r[i], false, i+1);

      // get next E-node
      // HeapNode<T> N;
      HeapNode<int> N;
      H.DeleteMax(N); // cannot be empty
      i = N.level;
      E = N.ptr;
      Ew = N.uweight - r[i-1];
      }

   // construct bestx[] by following path
   // from E-node E to the root
   for (j = n; j > 0; j--) {
      bestx[j] = E->LChild;  // bool to int
      E = E->parent;
      }

   return Ew;
}

void main(void)
{
   int w[6] = {0, 2, 2, 6, 5, 5};
   int x[6];
   int n = 5;
   int c = 16;
   cout << "Max loading is " << MaxLoading(w,c,n,x) << endl;
   cout << "Loading vector is" << endl;
   for (int i = 1; i <= n; i++)
      cout << x[i] << ' ';
   cout << endl;
}
