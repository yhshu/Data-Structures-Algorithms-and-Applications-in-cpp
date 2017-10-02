
// height biased leftist tree implementation of a max priority queue
// derives from the ADT maxPriorityQueue
// also derives from linkedBinaryTree<pair<int,T> >
// first component of a pair is the s value and the second is the data

#ifndef maxHblt_
#define maxHblt_

#include "maxPriorityQueue.h"
#include "linkedBinaryTree.h"
#include "binaryTreeNode.h"
#include "myExceptions.h"
#include <sstream>

using namespace std;

template<class T>
class maxHblt : public maxPriorityQueue<T>,
                public linkedBinaryTree<pair<int,T> >
{
   public:
      bool empty() const {return treeSize == 0;}
      int size() const {return treeSize;}
      const T& top()
         {// return max element
            if (treeSize == 0)
               throw queueEmpty();
            return root->element.second;
         }
      void pop();
      void push(const T&);
      void initialize(T *, int);
      void meld(maxHblt<T>& theHblt)
         {// meld *this and theHblt
            meld(root, theHblt.root);
            treeSize += theHblt.treeSize;
            theHblt.root = NULL;
            theHblt.treeSize = 0;
         }
      void output() {postOrder(hbltOutput); cout << endl;}
   private:
      void meld(binaryTreeNode<pair<int,T> >* &,
                binaryTreeNode<pair<int,T> >* &);
      static void hbltOutput(binaryTreeNode<pair<int,T> > *t)
                  {cout << t->element.second << ' ';}
};

template<class T>
void maxHblt<T>::meld(binaryTreeNode<pair<int, T> >* &x,
                      binaryTreeNode<pair<int, T> >* &y)
{// Meld leftist trees with roots *x and *y.
 // Return pointer to new root in x.
   if (y == NULL)   // y is empty
      return;
   if (x == NULL)   // x is empty
      {x = y; return;}

   // neither is empty, swap x and y if necessary
   if (x->element.second < y->element.second)
      swap(x, y);

   // now x->element.second >= y->element.second

   meld(x->rightChild,y);

   // swap subtrees of x if necessary and set x->element.first
   if (x->leftChild == NULL)
   {// left subtree empty, swap the subtrees
         x->leftChild = x->rightChild;
         x->rightChild = NULL;
         x->element.first = 1;
   }
   else
   {// swap only if left subtree has smaller s value
      if (x->leftChild->element.first < x->rightChild->element.first)
         swap(x->leftChild, x->rightChild);
      // update s value of x
      x->element.first = x->rightChild->element.first + 1;
   }
}

template<class T>
void maxHblt<T>::push(const T& theElement)
{// Insert theElement into the leftist tree.
 // Create tree with one node.
   binaryTreeNode<pair<int,T> > *q =
      new binaryTreeNode<pair<int,T> > (pair<int,T>(1, theElement));

   // meld q and original tree
   meld(root,q);
   treeSize++;
}

template<class T>
void maxHblt<T>::pop()
{// Delete max element.
   if (root == NULL)
      throw queueEmpty();

   // tree not empty
   binaryTreeNode<pair<int,T> > *left = root->leftChild,
                               *right = root->rightChild;
   delete root;
   root = left;
   meld(root, right);
   treeSize--;
}

template<class T>
void maxHblt<T>::initialize(T* theElements, int theSize)
{// Initialize hblt with theElements[1:theSize].
   arrayQueue<binaryTreeNode<pair<int,T> >*> q(theSize);
   erase();  // make *this empty

   // initialize queue of trees
   for (int i = 1; i <= theSize; i++)
      // create trees with one node each
      q.push(new binaryTreeNode<pair<int,T> >
                 (pair<int,T>(1, theElements[i])));

   // repeatedly meld from queue
   for (i = 1; i <= theSize - 1; i++)
   {// pop and meld two trees from queue 
      binaryTreeNode<pair<int,T> > *b = q.front();
      q.pop();
      binaryTreeNode<pair<int,T> > *c = q.front();
      q.pop();
      meld(b,c);
      // put melded tree on queue
      q.push(b);
   }

   if (theSize > 0)
      root = q.front();
   treeSize = theSize;
}
#endif
