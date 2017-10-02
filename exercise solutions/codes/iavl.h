
// indexed AVL tree

#ifndef IndexedAVLtree_
#define IndexedAVLtree_

#include "avlnode2.h" 
#include "xcept.h" 
#include "stack.h" 

template<class E, class K>
class IndexedAVLtree {
   public:
      IndexedAVLtree() {root = 0;}
      ~IndexedAVLtree() {Erase(root);}
      bool Search(const K& k, E& e) const;
      bool IndexedSearch(int k, E& e) const;
      IndexedAVLtree<E,K>& Insert(const E& e);
      IndexedAVLtree<E,K>& Delete(const K& k, E& e);
      IndexedAVLtree<E,K>& IndexedDelete(int k, E& e);
      void Ascend() {InOutput(root);
                     cout << endl;}
      void PostOut() {PostOutput(root);
                      cout << endl;}
   protected:
      IAVLNode<E,K> *root;  // root node
      void Reset(int r, const K& k);
      void Erase(IAVLNode<E,K> *t);
      void InOutput(IAVLNode<E,K> *t);
      void PostOutput(IAVLNode<E,K> *t);
      void FixBF(IAVLNode<E,K> *,
                 IAVLNode<E,K>*, const E&);
      void RRrotate(IAVLNode<E,K> *,
                    IAVLNode<E,K>*, IAVLNode<E,K> *);
      void LLrotate(IAVLNode<E,K> *,
                    IAVLNode<E,K>*, IAVLNode<E,K> *);
      void RLrotate(IAVLNode<E,K> *,
                    IAVLNode<E,K>*, IAVLNode<E,K> *);
      void LRrotate(IAVLNode<E,K> *,
                    IAVLNode<E,K>*, IAVLNode<E,K> *);
};


template<class E, class K>
void IndexedAVLtree<E,K>::Erase(IAVLNode<E,K> *t)
{// Delete all nodes in AVL tree with root t.
 // Use a postorder traversal.
   if (t) {Erase(t->LeftChild);
           Erase(t->RightChild);
           delete t;
          }
}

template<class E, class K>
void IndexedAVLtree<E,K>::FixBF(IAVLNode<E,K> *q,
                    IAVLNode<E,K> *r, const E &e)
{// Balance factors from q to r were originally 0.
 // They need to be changed to +1 or -1.
 // Use e to find path from q to r.

   while (q != r)
      if (e < q->data) {
         // height of left subtree has increased
         q->bf = 1;
         q = q->LeftChild;}
      else {
         // height of right subtree has increased
         q->bf = -1;
         q = q->RightChild;}
}

template<class E, class K>
void IndexedAVLtree<E,K>::
     LLrotate(IAVLNode<E,K> *PA,
              IAVLNode<E,K> *A, IAVLNode<E,K> *B)
{// LL rotation around A.  PA is parent of A
 // and B left child of A.

   // restructure subtree at A
   A->LeftChild = B->RightChild;
   B->RightChild = A;
   A->LeftSize -= B->LeftSize;
   if (PA) // A is not the root
           if (A == PA->LeftChild)
              PA->LeftChild = B;
           else PA->RightChild = B;
   else root = B;

   // set balance factors
   A->bf = B->bf = 0;
}

template<class E, class K>
void IndexedAVLtree<E,K>::
     RRrotate(IAVLNode<E,K> *PA,
              IAVLNode<E,K> *A, IAVLNode<E,K> *B)
{// RR rotation around A.  PA is parent of A
 // and B right child of A.

   // restructure subtree at A
   A->RightChild = B->LeftChild;
   B->LeftChild = A;
   B->LeftSize += A->LeftSize;
   if (PA) // A is not the root
           if (A == PA->LeftChild)
              PA->LeftChild = B;
           else PA->RightChild = B;
   else root = B;

   // set balance factors
   A->bf = B->bf = 0;
}

template<class E, class K>
void IndexedAVLtree<E,K>::
     LRrotate(IAVLNode<E,K> *PA,
              IAVLNode<E,K> *A, IAVLNode<E,K> *B)
{// LR rotation around A.  PA is parent of A
 // and B left child of A.

   IAVLNode<E,K> *C = B->RightChild;

   // restructure subtree at A
   A->LeftChild = C->RightChild;
   B->RightChild = C->LeftChild;
   C->LeftChild = B;
   C->RightChild = A;
   A->LeftSize -= B->LeftSize + C->LeftSize;
   C->LeftSize += B->LeftSize;
   if (PA) // A is not the root
           if (A == PA->LeftChild)
              PA->LeftChild = C;
           else PA->RightChild = C;
   else root = C;

   // set balance factors
   int b = C->bf;
   if (b == 1) {B->bf = 0;
                A->bf = -1;}
   else if (b) {B->bf = 1;
                A->bf = 0;}
        else // b = 0
           B->bf = A->bf = 0;
   C->bf = 0;

}

template<class E, class K>
void IndexedAVLtree<E,K>::
     RLrotate(IAVLNode<E,K> *PA,
              IAVLNode<E,K> *A, IAVLNode<E,K> *B)
{// RL rotation around A.  PA is parent of A
 // and B left child of A.

   IAVLNode<E,K> *C = B->LeftChild;

   // restructure subtree at A
   A->RightChild = C->LeftChild;
   B->LeftChild = C->RightChild;
   C->LeftChild = A;
   C->RightChild = B;
   B->LeftSize -= C->LeftSize;
   C->LeftSize += A->LeftSize;
   if (PA) // A is not the root
           if (A == PA->LeftChild)
              PA->LeftChild = C;
           else PA->RightChild = C;
   else root = C;

   // set balance factors
   int b = C->bf;
   if (b == 1) {B->bf = -1;
                A->bf = 0;}
   else if (b) {B->bf = 0;
                A->bf = 1;}
        else // b = 0
           B->bf = A->bf = 0;
   C->bf = 0;

}

template<class E, class K>
bool IndexedAVLtree<E,K>::
     Search(const K& k, E &e) const
{// Search for element that matches k.

   // pointer p starts at the root and moves through
   // the tree looking for an element with key k
   IAVLNode<E,K> *p = root;
   while (p) // examine p->data
      if (k < p->data) p = p->LeftChild;
      else if (k > p->data) p = p->RightChild;
           else {// found element
                 e = p->data;
                 return true;}
   return false;
}


template<class E, class K>
bool IndexedAVLtree<E,K>::
     IndexedSearch(int k, E& e) const
{// Put the k'th element in e.
 // Return false iff there is no k'th element
   IAVLNode<E,K> *p = root;
   while (p)
      if (k < p->LeftSize) p = p->LeftChild;
      else if (k > p->LeftSize) {
   	      k -= p->LeftSize;
              p = p->RightChild;}
           else {e = p->data;
                return true;}
   return false;
}

template<class E, class K>
IndexedAVLtree<E,K>& IndexedAVLtree<E,K>::
                     Insert(const E& e)
{// Insert e if not duplicate.
   IAVLNode<E,K> *p = root,  // search pointer
                 *pp = 0,    // parent of p
                 *A = 0,     // node with bf != 0
                 *PA;        // parent of A
   // find place to insert
   // also record most recent node with bf != 0
   // in A and its parent in PA
   K k = e;   // extract key
   while (p) {// examine p->data
      if (p->bf) {// new candidate for A node
        A = p;
        PA = pp;}
      pp = p;
      // move p to a child
      if (k < p->data) {
         // insert will be in left subtree of p
         p->LeftSize++;
         p = p->LeftChild;}
      else if (k > p->data) p = p->RightChild;
           else {Reset(-1,k);       // reset LeftSize
                 throw BadInput();} //duplicate
      }

   // get a node for e and attach to pp
   IAVLNode<E,K> *r = new IAVLNode<E,K> (e);
   if (root) {// tree not empty
      if (e < pp->data) pp->LeftChild = r;
      else pp->RightChild = r;}
   else {// insertion into empty tree
         root = r;
         return *this;}

   // see if we must rebalance or simply change
   // balance factors
   if (A) // possible rebalancing needed
          if (A->bf < 0) // bf = -1 before insertion
             if (e < A->data) {// insertion in left subtree
                // height of left subtree has increased by 1
                // new bf of A is 0, no rebalancing
                A->bf = 0;
                // fix bf on path from A to r
                FixBF(A->LeftChild,r,e);}
             else {// insertion in right subtree
                // bf of A is -2, rebalance
                IAVLNode<E,K> *B = A->RightChild;
                if (e > B->data) {// RR case
                   FixBF(B->RightChild,r,e);
                   RRrotate(PA,A,B);}
                else {// RL case
                   FixBF(B->LeftChild,r,e);
                   RLrotate(PA,A,B);}
                }
          else // bf = +1 before insertion
             if (e > A->data) {// insertion in right subtree
                // height of right subtree has increased by 1
                // new bf of A is 0, no rebalancing
                A->bf = 0;
                // fix bf on path from A to r
                FixBF(A->RightChild,r,e);}
             else {// insertion in left subtree
                // bf of A is +2, rebalance
                IAVLNode<E,K> *B = A->LeftChild;
                if (e < B->data) {// LL case
                   FixBF(B->LeftChild,r,e);
                   LLrotate(PA,A,B);}
                else {// LR case
                   FixBF(B->RightChild,r,e);
                   LRrotate(PA,A,B);}
                }
   else // A is NULL, no rebalancing
      FixBF(root,r,e);

   return *this;
}

template<class E, class K>
void IndexedAVLtree<E,K>::
     Reset(int r, const K& k)
{// Add r to LeftSize on path to k.
   IAVLNode<E,K> *p = root;
   while (p)
      if (k < p->data) {
         p->LeftSize += r;
         p = p->LeftChild;}
      else if (k > p->data) p = p->RightChild;
           else return;
}

template<class E, class K>
IndexedAVLtree<E,K>& IndexedAVLtree<E,K>::
                     Delete(const K& k, E& e)
{// Delete element with key k and put it in e.
 // Throw BadInput exception if there is no element
 // with key k.

   // define a stack to hold path taken from root
   // to physically deleted node
   // we will not run out of stack space unless
   // the number of elements is much more than 2^60
   Stack<IAVLNode<E,K>*> S(100);

   // set p to point to node with key k
   IAVLNode<E,K> *p = root; // search pointer
   while (p && p->data != k){// move to a child of p
      S.Add(p);
      if (k < p->data) {
         p->LeftSize--;
         p = p->LeftChild;}
      else p = p->RightChild;
      }
   if (!p) {Reset(1, k);
            throw BadInput();} // not found

   e = p->data;  // save element to delete

   // restructure tree
   // handle case when p has two children
   if (p->LeftChild && p->RightChild) {// two children
      // convert to zero or one child case
      // find largest element in left subtree of p
      S.Add(p);
      IAVLNode<E,K> *s = p->LeftChild;
      while (s->RightChild) {// move to larger element
         S.Add(s);
         s = s->RightChild;}

      // move largest from s to p
      p->data = s->data;
      p->LeftSize--;
      p = s;}

   // p has at most one child
   // save child pointer in c
   IAVLNode<E,K> *c;
   if (p->LeftChild) c = p->LeftChild;
   else c = p->RightChild;

   // delete p
   if (p == root) root = c;
   else {// is p a left or right child?
         if (p == S.Top()->LeftChild)
              S.Top()->LeftChild = c;
         else S.Top()->RightChild = c;}
   E f = p->data; // f may not equal e
   delete p;

   // rebalance tree and correct balance factors
   // use stack to retrace path to root
   // set q to parent of deleted node
   IAVLNode<E,K> *q;
   try {S.Delete(q);}
   catch (OutOfBounds)
      {return *this;} // root was deleted

   while (q)
      if (f <= q->data) {
         // deleted from left subtree of q
         // height of left subtree reduced by 1
         q->bf--;
         if (q->bf == -1) // height of q is unchanged
                          // nothing more to do
                          return *this;
         if (q->bf == -2) {// q is unbalanced
            // classify imbalance and rotate
            IAVLNode<E,K> *B = q->RightChild,
                          *PA;  // q is A node
                                // PA is parent of A
            try {S.Delete(PA);}
            catch (OutOfBounds)
               {PA = 0;}       // A is root
            
            switch (B->bf) {
               case 0:    // L0 imbalance
                  RRrotate(PA,q,B);
                  B->bf = 1;
                  q->bf = -1;  // q is A node
                  return *this;
               case 1:    // L1 imbalance
                  RLrotate(PA,q,B);
                  break;  // must continue on path to root
               case -1:   // L-1 imbalance
                  RRrotate(PA,q,B);
               }
            q = PA;
            }
         else {// q->bf is 0
            try {S.Delete(q);}
            catch (OutOfBounds)
               {return *this;}
            }
        }
      else {// f > q->data
         // deleted from right subtree of q
         // height of right subtree reduced by 1
         q->bf++;
         if (q->bf == 1) // height of q is unchanged
                          // nothing more to do
                          return *this;
         if (q->bf == 2) {// q is unbalanced
            // classify imbalance and rotate
            IAVLNode<E,K> *B = q->LeftChild,
                          *PA;  // q is A node
                                // PA is parent of A
            try {S.Delete(PA);}
            catch (OutOfBounds)
               {PA = 0;}       // A is root
            
            switch (B->bf) {
               case 0:    // R0 imbalance
                  LLrotate(PA,q,B);
                  B->bf = -1;
                  q->bf = 1;  // q is A node
                  return *this;
               case 1:    // R1 imbalance
                  LLrotate(PA,q,B);
                  break;  // must continue on path to root
               case -1:   // R-1 imbalance
                  LRrotate(PA,q,B);
               }
            q = PA;
            }
         else {// q->bf is 0
            try {S.Delete(q);}
            catch (OutOfBounds)
               {return *this;}
            }
        }

   return *this;
}


template<class E, class K>
IndexedAVLtree<E,K>& IndexedAVLtree<E,K>::
                     IndexedDelete(int k, E& e)
{// Delete k'th and put it in e.
 // Throw BadInput exception if there is no k'th element.

   // define a stack to hold path taken from root
   // to physically deleted node
   // we will not run out of stack space unless
   // the number of elements is much more than 2^60
   Stack<IAVLNode<E,K>*> S(100);

   // set p to point to node with k'th element
   IAVLNode<E,K> *p = root; // search pointer
   while (p && p->LeftSize != k) {
      S.Add(p);
      if (k < p->LeftSize) {
         p->LeftSize--;
         p = p->LeftChild;}
      else {k -= p->LeftSize;
            p = p->RightChild;}
      }
   if (!p) {// no element to delete, reset LeftSize
            p = root;
            while (p)
               if (k < p->LeftSize) {
                  p->LeftSize--;
                  p = p->LeftChild;}
               else {k -= p->LeftSize;
                     p = p->RightChild;}

             throw BadInput();
             }

   e = p->data;  // save element to delete

   // restructure tree
   // handle case when p has two children
   if (p->LeftChild && p->RightChild) {// two children
      // convert to zero or one child case
      // find largest element in left subtree of p
      S.Add(p);
      IAVLNode<E,K> *s = p->LeftChild;
      while (s->RightChild) {// move to larger element
         S.Add(s);
         s = s->RightChild;}

      // move largest from s to p
      p->data = s->data;
      p->LeftSize--;
      p = s;}

   // p has at most one child
   // save child pointer in c
   IAVLNode<E,K> *c;
   if (p->LeftChild) c = p->LeftChild;
   else c = p->RightChild;

   // delete p
   if (p == root) root = c;
   else {// is p a left or right child?
         if (p == S.Top()->LeftChild)
              S.Top()->LeftChild = c;
         else S.Top()->RightChild = c;}
   E f = p->data; // f may not equal e
   delete p;

   // rebalance tree and correct balance factors
   // use stack to retrace path to root
   // set q to parent of deleted node
   IAVLNode<E,K> *q;
   try {S.Delete(q);}
   catch (OutOfBounds)
      {return *this;} // root was deleted

   while (q)
      if (f <= q->data) {
         // deleted from left subtree of q
         // height of left subtree reduced by 1
         q->bf--;
         if (q->bf == -1) // height of q is unchanged
                          // nothing more to do
                          return *this;
         if (q->bf == -2) {// q is unbalanced
            // classify imbalance and rotate
            IAVLNode<E,K> *B = q->RightChild,
                          *PA;  // q is A node
                                // PA is parent of A
            try {S.Delete(PA);}
            catch (OutOfBounds)
               {PA = 0;}       // A is root
            
            switch (B->bf) {
               case 0:    // L0 imbalance
                  RRrotate(PA,q,B);
                  B->bf = 1;
                  q->bf = -1;  // q is A node
                  return *this;
               case 1:    // L1 imbalance
                  RLrotate(PA,q,B);
                  break;  // must continue on path to root
               case -1:   // L-1 imbalance
                  RRrotate(PA,q,B);
               }
            q = PA;
            }
         else {// q->bf is 0
            try {S.Delete(q);}
            catch (OutOfBounds)
               {return *this;}
            }
        }
      else {// f > q->data
         // deleted from right subtree of q
         // height of right subtree reduced by 1
         q->bf++;
         if (q->bf == 1) // height of q is unchanged
                          // nothing more to do
                          return *this;
         if (q->bf == 2) {// q is unbalanced
            // classify imbalance and rotate
            IAVLNode<E,K> *B = q->LeftChild,
                          *PA;  // q is A node
                                // PA is parent of A
            try {S.Delete(PA);}
            catch (OutOfBounds)
               {PA = 0;}       // A is root
            
            switch (B->bf) {
               case 0:    // R0 imbalance
                  LLrotate(PA,q,B);
                  B->bf = -1;
                  q->bf = 1;  // q is A node
                  return *this;
               case 1:    // R1 imbalance
                  LLrotate(PA,q,B);
                  break;  // must continue on path to root
               case -1:   // R-1 imbalance
                  LRrotate(PA,q,B);
               }
            q = PA;
            }
         else {// q->bf is 0
            try {S.Delete(q);}
            catch (OutOfBounds)
               {return *this;}
            }
        }

   return *this;
}

template<class E, class K>
void IndexedAVLtree<E,K>::
     InOutput(IAVLNode<E,K> *t)
{// Output in ascending order.
 // Use an inorder traversal.
   if (t) {InOutput(t->LeftChild);
           cout << t->data << " ";
           InOutput(t->RightChild);
          }
}

template<class E, class K>
void IndexedAVLtree<E,K>::
     PostOutput(IAVLNode<E,K> *t)
{// Output in postorder.
   if (t) {PostOutput(t->LeftChild);
           PostOutput(t->RightChild);
           cout << t->data << " ";
          }
}

#endif;
