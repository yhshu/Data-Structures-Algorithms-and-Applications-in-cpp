
// 2-3 tree

#ifndef TwoThree_
#define TwoThree_

#include "node23.h"
#include "ret23.h"
#include "stack.h"
#include "xcept.h"
#include "swap.h"

template<class E, class K>
class TwoThree {
   public:
      TwoThree(E NullElement)
         {Null = NullElement;
          root = 0;
          }
      ~TwoThree() {Erase(root);}
      bool Search(const K& k, E& e) const;
      TwoThree<E,K>& Insert(const E& e);
      TwoThree<E,K>& Delete(const K& k, E& e)
         {if (Delete(k, e, root)) {
             // root has become deficient
             Node23<E,K> *t = root;
             root = root->LChild;
             delete t;
             }
          return *this;
          }
      void Ascend() {InOutput(root);
                     cout << endl;}
      void PostOut() {PostOutput(root);
                      cout << endl;}
   private:
      Node23<E,K> *root;  // root node
      E Null;             // denotes null element
      void Erase(Node23<E,K> *t);
      ReturnPair23<E,K> Insert(Node23<E,K> *p, const E& e);
      bool FixLeftChild(Node23<E,K> *p);
      bool FixMiddleChild(Node23<E,K> *p);
      bool FixRightChild(Node23<E,K> *p);
      bool DeleteLargest(Node23<E,K> *p, E& e);
      bool Delete(const K& k, E& e, Node23<E,K> *p);
      void InOutput(Node23<E,K> *t);
      void PostOutput(Node23<E,K> *t);
};

template<class E, class K>
void TwoThree<E,K>::Erase(Node23<E,K> *t)
{// Delete all nodes in 2-3 tree with root t.
 // Use a postorder traversal.
   if (t) {// t has a left and middle subtree
           Erase(t->LChild);
           Erase(t->MChild);

           // erase right subtree if it exists
           if (t->RData != Null) Erase(t->RChild);

           delete t;
           }
}

template<class E, class K>
bool TwoThree<E,K>::Search(const K& k, E &e) const
{// Search for element that matches k.
 // Put matching element in e.
 // Return false if no matching element.

   // pointer p starts at the root and moves through
   // the tree looking for an element with key k
   Node23<E,K> *p = root;
   while (p) // examine p->data
      if (k < p->LData) p = p->LChild;
      else if (p->RData == Null)  // p is a 2-node
              if (k == p->LData) {// found match
                                  e = p->LData;
                                  return true;
                                  }
              else // k > p->LData
                 p = p->MChild;
           else  // p is a 3-node
              if (k > p->LData && k < p->RData)
                 p = p->MChild;
              else if (k > p->RData)
                      p = p->RChild;
                   else {// k matches one of the elements
                         if (k == p->LData)
                            e = p->LData;
                         else e = p->RData;
                         return true;
                         }

   // no match was found
   return false;
}

template<class E, class K>
TwoThree<E,K>& TwoThree<E,K>::Insert(const E& e)
{// Insert e if not duplicate.
 // Throw BadInput exception if e is either Null or a duplicate.
   if (e == Null)  // cannot insert null element
      throw BadInput();

   // insert recursively
   ReturnPair23<E,K> r = Insert(root, e);

   if (r.element != Null) {// root has split
      // create new root, this is a 2-node
      Node23<E,K> *NewRoot = new Node23<E,K>;
      NewRoot->LChild = root;
      NewRoot->MChild = r.NodePtr;
      NewRoot->LData = r.element;
      NewRoot->RData = Null;
      root = NewRoot;
      }

   return *this;
}

template<class E, class K>
ReturnPair23<E,K> TwoThree<E,K>::
                  Insert(Node23<E,K> *p, const E& e)
{// Insert e into the 2-3 tree with root p.
 // Throw BadInput exception if e is a duplicate.
 // Return the pair (element, pointer) to be inserted in
 // parent of p in case node p splits.  Return a pair
 // with element = Null in case p does not split.
   ReturnPair23<E,K> r;
   if (p) // p is not empty
      if (p->RData == Null) // p is a 2-node
         if (e < p->LData) {// insert in p->LChild
            r = Insert(p->LChild, e);
            if (r.element != Null) {// p->LChild did split
               // insert r into p as LData and MChild
               p->RData = p->LData;
               p->RChild = p->MChild;
               p->LData = r.element;
               p->MChild = r.NodePtr;
               // p does not split
               r.element = Null;
               }
            return r;
            }
         else if (e > p->LData) {// insert in p->MChild
                 r = Insert(p->MChild, e);
                 if (r.element != Null) {// p->MChild did split
                    // insert r into p as RData and RChild
                    p->RData = r.element;
                    p->RChild = r.NodePtr;
                    // p does not split
                    r.element = Null;
                    }
                 return r;
                 }
              else  // e = p->LData, duplicate
                    throw BadInput();
      else // p is a 3-node
         if (e < p->LData) {// insert in p->LChild
            r = Insert(p->LChild, e);
            if (r.element != Null) {// p->LChild did split
               // now p will split
               // create a new 2-node q for p->RData
               Node23<E,K> *q = new Node23<E,K>;
               q->LData = p->RData;
               q->MChild = p->RChild;
               q->LChild = p->MChild;
               q->RData = Null;

               // p becomes a 2-node with LData = r.element
               // and the pair (p->LData, q) is to be
               // inserted in the parent of p
               p->RData = Null;
               Swap(p->LData, r.element);
               p->MChild = r.NodePtr;
               r.NodePtr = q;
               }
            return r;
            }
         else if (e > p->RData) {// insert in p->RChild
                 r = Insert(p->RChild, e);
                 if (r.element != Null) {// p->RChild did split
                    // now p will split
                    // create a new 2-node q for r.element
                    Node23<E,K> *q = new Node23<E,K>;
                    q->LData = r.element;
                    q->MChild = r.NodePtr;
                    q->LChild = p->RChild;
                    q->RData = Null;
     
                    // p becomes a 2-node
                    // and the pair (p->MData, q) is to be
                    // inserted in the parent of p
                    r.element = p->RData;
                    r.NodePtr = q;
                    p->RData = Null;  // p is now a 2-node
                    }
                 return r;
                 }
              else if (e > p->LData && e < p->RData) {
                      // insert in p->MChild
                      r = Insert(p->MChild, e);
                      if (r.element != Null) {// p->MChild did split
                         // now p will split
                         // create a new 2-node q for p->RData
                         Node23<E,K> *q = new Node23<E,K>;
                         q->LData = p->RData;
                         q->MChild = p->RChild;
                         q->LChild = r.NodePtr;
                         q->RData = Null;
          
                         // p becomes a 2-node
                         // and the pair (r.element, q) is to be
                         // inserted in the parent of p
                         p->RData = Null;  // p is now a 2-node
                         r.NodePtr = q;
                         }
                      return r;
                      }
			        else  // duplicate
                         throw BadInput();
   else {// p is empty
         // create a pair to insert in parent of p
         r.element = e;
         r.NodePtr = 0;
         return r;
         }
   return r;
}
         

template<class E, class K>
bool TwoThree<E,K>::FixLeftChild(Node23<E,K> *p)
{// The left child of p has become
 // deficient.  Fix deficiency.  Return true iff
 // p becomes deficient as a result of the fix.

   Node23<E,K> *lp = p->LChild, // left child of p
               *mp = p->MChild; // middle child of p

   // the left child of p must have been
   // a 2-node before the deletion
   if (mp->RData == Null) {
      // middle child of p is a 2-node; combine lp,
      // p->LData, and mp; lp becomes a 3-node
      lp->LData = p->LData;
      lp->RData = mp->LData;
      lp->MChild = mp->LChild;
      lp->RChild = mp->MChild;
      delete mp;
      if (p->RData == Null)  // p was a 2-node
         // p becomes deficient
         return true;
      else  {// p was a 3-node
             // p becomes a 2-node
             p->LData = p->RData;
             p->RData = Null;
             p->MChild = p->RChild;
             return false;
             }
      }
   else {
      // middle child of p is a 3-node, borrow from it
      lp->LData = p->LData;
      lp->MChild = mp->LChild;
      p->LData = mp->LData;
      mp->LChild = mp->MChild;
      mp->MChild = mp->RChild;
      mp->LData = mp->RData;
      mp->RData = Null;  // mp is now a 2-node

      // p is not deficient
      return false;
      }
}

template<class E, class K>
bool TwoThree<E,K>::FixMiddleChild(Node23<E,K> *p)
{// The middle child of p has become
 // deficient.  Fix deficiency.  Return true iff
 // p becomes deficient as a result of the fix.

   Node23<E,K> *lp = p->LChild, // left child of p
               *mp = p->MChild; // midle child of p

   // p->MChild must have been
   // a 2-node before the deletion
   if (lp->RData == Null) {
      // left child of p is a 2-node; combine lp,
      // p->LData and mp; lp becomes a 3-node
      lp->RData = p->LData;
      lp->RChild = mp->LChild;
      delete mp;

      if (p->RData == Null)  // p was a 2-node
         // p becomes deficient
         return true;
      else  {// p was a 3-node
             // p becomes a 2-node
             p->LData = p->RData;
             p->RData = Null;
             p->MChild = p->RChild;
             return false;
             }
      }
   else {
      // left child of p is a 3-node, borrow from it
      mp->LData = p->LData;
      mp->MChild = mp->LChild;
      mp->LChild = lp->RChild;
      p->LData = lp->RData;
      lp->RData = Null;  // left child is now a 2-node

      // p is not deficient
      return false;
      }
}

template<class E, class K>
bool TwoThree<E,K>::FixRightChild(Node23<E,K> *p)
{// The right child of p has become
 // deficient.  Fix deficiency.  Return true iff
 // p becomes deficient as a result of the fix.

   Node23<E,K> *rp = p->RChild, // right child of p
               *mp = p->MChild; // midle child of p

   // p is a 3-node
   // p->RChild must have been
   // a 2-node before the deletion
   if (mp->RData == Null) {
      // middle child of p is a 2-node; combine mp,
      // p->RData and rp; mp becomes a 3-node
      mp->RData = p->RData;
      mp->RChild = rp->LChild;
      delete rp;
      p->RData = Null;
      }
   else {
      // middle child of p is a 3-node, borrow from it
      rp->LData = p->RData;
      rp->MChild = rp->LChild;
      rp->LChild = mp->RChild;
      p->RData = mp->RData;
      mp->RData = Null;  // middle child is now a 2-node
      }

   return false;
}

template<class E, class K>
bool TwoThree<E,K>::DeleteLargest(Node23<E,K> *p, E& e)
{// Delete the largest element in the subtree with root p.
 // Put this element in e.  Return true iff p becomes deficient.
   if (p->LChild) // p is not a leaf
      if (p->RData == Null)  // p is a 2-node
         if (DeleteLargest(p->MChild, e))
            return FixMiddleChild(p);
         else return false;
      else  // p is a 3-node
         if (DeleteLargest(p->RChild, e))
            return FixRightChild(p);
         else return false;
   else  // p is a leaf
      if (p->RData == Null)  {// p is a 2-node
         e = p->LData;
         return true;  // p has become deficient
         }
      else {// p is a 3-node
            e = p->RData;
            p->RData = Null;
            return false;  // p is not deficient
            }
}

template<class E, class K>
bool TwoThree<E,K>::Delete(const K& k, E& e, Node23<E,K> *p)
{// Delete element with key k from the 2-3 tree
 // with root p.  Put deleted element in e.
 // Throw BadInput exception if there is no element
 // with key k.
 // Return true iff p is deficient (i.e., has no element)
 // following the deletion.
   if (!p)  // empty subtree
      throw BadInput();

   if (k < p->LData) // delete from left subtree
      if (Delete(k, e, p->LChild))
         // p->LChild has become deficient
         return FixLeftChild(p);
      else return false;  // p is not deficient
   else if (k == p->LData) {// p->LData is element to delete
           e = p->LData;
           if (p->LChild) // p is not a leaf
              // delete largest element in p->LChild
              // and place in p->LData
              if (DeleteLargest(p->LChild, p->LData))
                 // p->LChild has become deficient
                 return FixLeftChild(p);
              else return false;  // p is not deficient
           else if (p->RData == Null)
                   // deletion from a 2-node leaf
                   return true;
                else {// deletion from a 3-node leaf
                      p->LData = p->RData;
                      p->RData = Null;
                      return false;
                      }
           }
        else if (p->RData == Null)  // p is a 2-node
                if (Delete(k, e, p->MChild))
                   // p->MChild has become deficient
                   return FixMiddleChild(p);
                else return false;  // p is not deficient
             else  // p is a 3-node
                if (k > p->RData)
                   if (Delete(k, e, p->RChild))
                      // p->RChild has become deficient
                      return FixRightChild(p);
                   else return false;  // p is not deficient
                else if (k < p->RData)
                        if (Delete(k, e, p->MChild))
                           return FixMiddleChild(p);
                        else return false;
                     else {// p->RData is element to delete
                           e = p->RData;
                           if (p->LChild) // p is not a leaf
                              // delete largest element in p->MChild
                              // and place in p->RData
                              if (DeleteLargest(p->MChild, p->RData))
                                 // p->MChild has become deficient
                                 return FixMiddleChild(p);
                              else return false;  // p is not deficient
                           else {// deletion from a 3-node leaf
                                 p->RData = Null;
                                 return false;
                                 }
                           }
}

template<class E, class K>
void TwoThree<E,K>::InOutput(Node23<E,K> *t)
{// Output in ascending order.
 // Use an inorder traversal.
   if (t) {InOutput(t->LChild);
           cout << t->LData << " ";
           InOutput(t->MChild);
           if (t->RData != Null) {
              cout << t->RData << " ";
              InOutput(t->RChild);
              }
          }
}

template<class E, class K>
void TwoThree<E,K>::PostOutput(Node23<E,K> *t)
{// Output in postorder.
   if (t) {PostOutput(t->LChild);
           PostOutput(t->MChild);
           cout << t->LData << " ";
           if (t->RData != Null) {
              PostOutput(t->RChild);
              cout << t->RData << " ";
              }
          }
}

#endif
