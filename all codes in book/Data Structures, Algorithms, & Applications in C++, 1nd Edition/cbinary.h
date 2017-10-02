
// LevelOrder and the private recursive PreOrder,
// InOrder, and PostOrder methods have been changed
// from template functions to eType functions because
// Visual C++ is unable to reslove overloaded functions
// when these were template functions

#ifndef BinaryTree_
#define BinaryTree_
int _count;

#include<iostream.h>
#include "lqueue.h"
#include "btnode2.h"
#include "xcept.h"

template<class E, class K> class BSTree;
template<class E, class K> class DBSTree;

template<class T>
class BinaryTree {
   friend BSTree<T,int>;
   friend DBSTree<T,int>;
   public:
      BinaryTree() {root = 0;};
      ~BinaryTree(){}; 
      bool IsEmpty() const
        {return ((root) ? false : true);}
      bool Root(T& x) const;
      void MakeTree(const T& element,
           BinaryTree<T>& left, BinaryTree<T>& right);
      void BreakTree(T& element, BinaryTree<T>& left,
                    BinaryTree<T>& right);
      void PreOrder(void(*Visit)(BinaryTreeNode<T> *u))
           {PreOrder(Visit, root);}
      void InOrder(void(*Visit)(BinaryTreeNode<T> *u))
           {InOrder(Visit, root);}
      void PostOrder(void(*Visit)(BinaryTreeNode<T> *u))
           {PostOrder(Visit, root);}
      void LevelOrder(void(*Visit)(BinaryTreeNode<T> *u));
      void PreOutput() {PreOrder(Output, root); cout << endl;}
      void InOutput() {InOrder(Output, root); cout << endl;}
      void PostOutput() {PostOrder(Output, root); cout << endl;}
      void LevelOutput() {LevelOrder(Output); cout << endl;}
      void Delete() {PostOrder(Free, root); root = 0;}
      int Height() const {return Height(root);}
      int Size()
         {_count = 0; PreOrder(Add1, root); return _count;}
   private:
      BinaryTreeNode<T> *root;  // pointer to root
      void PreOrder(void(*Visit)
        (BinaryTreeNode<T> *u), BinaryTreeNode<T> *t);
      void InOrder(void(*Visit)
        (BinaryTreeNode<T> *u), BinaryTreeNode<T> *t);
      void PostOrder(void(*Visit)
        (BinaryTreeNode<T> *u), BinaryTreeNode<T> *t);
      static void Free(BinaryTreeNode<T> *t) {delete t;}
      static void Output(BinaryTreeNode<T> *t)
                  {cout << t->data << ' ';}
      static void Add1(BinaryTreeNode<T> *t) {_count++;}
      int Height(BinaryTreeNode<T> *t) const;
};

template<class T>
bool BinaryTree<T>::Root(T& x) const
{// Return root data in x.
 // Return false if no root.
   if (root) {x = root->data;
              return true;}
   else return false;  // no root
}

template<class T>
void BinaryTree<T>::MakeTree(const T& element,
          BinaryTree<T>& left, BinaryTree<T>& right)
{// Combine left, right, and element to make new tree.
 // left, right, and this must be different trees.
   // create combined tree
   root = new BinaryTreeNode<T>
              (element, left.root, right.root);

   // deny access from trees left and right
   left.root = right.root = 0;
}

template<class T>
void BinaryTree<T>::BreakTree(T& element,
       BinaryTree<T>& left, BinaryTree<T>& right)
{// left, right, and this must be different trees.
   // check if empty
   if (!root) throw BadInput(); // tree empty

   // break the tree
   element = root->data;
   left.root = root->LeftChild;
   right.root = root->RightChild;

   delete root;
   root = 0;
}

// template<class T>
// void BinaryTree<T>::PreOrder(
//               void(*Visit)(BinaryTreeNode<T> *u),
//                         BinaryTreeNode<T> *t)
void BinaryTree<eType>::PreOrder(
              void(*Visit)(BinaryTreeNode<eType> *u),
                        BinaryTreeNode<eType> *t)
{// Preorder traversal.
   if (t) {Visit(t);
   	   PreOrder(Visit, t->LeftChild);
   	   PreOrder(Visit, t->RightChild);
           }
}

// template <class T>
// void BinaryTree<T>::InOrder(
//            void(*Visit)(BinaryTreeNode<T> *u),
//                         BinaryTreeNode<T> *t)
void BinaryTree<eType>::InOrder(
           void(*Visit)(BinaryTreeNode<eType> *u),
                        BinaryTreeNode<eType> *t)
{// Inorder traversal.
   if (t) {InOrder(Visit, t->LeftChild);
   	   Visit(t);
   	   InOrder(Visit, t->RightChild);
           }
}

// template <class T>
// void BinaryTree<T>::PostOrder(
//            void(*Visit)(BinaryTreeNode<T> *u),
//                         BinaryTreeNode<T> *t)
void BinaryTree<eType>::PostOrder(
           void(*Visit)(BinaryTreeNode<eType> *u),
                        BinaryTreeNode<eType> *t)
{// Postorder traversal.
   if (t) {PostOrder(Visit, t->LeftChild);
           PostOrder(Visit, t->RightChild);
           Visit(t);
           }
}

// template <class T>
// void BinaryTree<T>::LevelOrder(
//           void(*Visit)(BinaryTreeNode<T> *u))
void BinaryTree<eType>::LevelOrder(
          void(*Visit)(BinaryTreeNode<eType> *u))
{// Level-order traversal.
   LinkedQueue<BinaryTreeNode<T>*> Q;
   BinaryTreeNode<T> *t;
   t = root;
   while (t) {
      Visit(t);
      if (t->LeftChild) Q.Add(t->LeftChild);
      if (t->RightChild) Q.Add(t->RightChild);
      try {Q.Delete(t);}
      catch (OutOfBounds) {return;}
      }
}

template <class T>
int BinaryTree<T>::Height(BinaryTreeNode<T> *t) const
{// Return height of tree *t.
   if (!t) return 0;               // empty tree
   int hl = Height(t->LeftChild);  // height of left
   int hr = Height(t->RightChild); // height of right
   if (hl > hr) return ++hl;
   else return ++hr;
}

#endif
