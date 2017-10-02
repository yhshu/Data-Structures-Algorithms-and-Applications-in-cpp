

// build a binary tree from its preorder
// and inorder listings

#include <iostream.h>
#include "btnode1.h"
#include "xcept.h"

template <class T>
void Visit(BinaryTreeNode<T> *x)
{// Visit node *x, just output data field.
   cout << x->data << ' ';
}

template <class T>
void PreOrder(BinaryTreeNode<T> *t)
{// Preorder traversal of *t.
   if (t) {
      Visit(t);                 // visit tree root
      PreOrder(t->LeftChild);   // do left subtree
      PreOrder(t->RightChild);  // do right subtree
      }
}

template <class T>
void InOrder(BinaryTreeNode<T> *t)
{// Inorder traversal of *t.
   if (t) {
      InOrder(t->LeftChild);   // do left subtree
      Visit(t);                // visit tree root
      InOrder(t->RightChild);  // do right subtree
      }
}

BinaryTreeNode<int>* BuildFromPreAndIn
      (int InMap[], int StartIn, int EndIn,
       int PreList[], int &StartPre)
{// Return pointer to root of constructed binary
 // whose inorder list is
 // InList[StartIn:EndIn]
 // and whose preorder list is PreList[StartPost ...].
 // InMap[i] is the location of PreList[i] in InList[].
 // That is, InList[InMap[PreList[i]]] = PreList[i].

   if (StartIn > EndIn) return 0;  // empty
  
   // create a node for the root and set its data field
   BinaryTreeNode<int> *root = new BinaryTreeNode<int>;
   int element = PreList[StartPre];
   // verify that element is in the
   // proper subtree
   int InLocation = InMap[StartPre++];
   if (InLocation < StartIn ||
       InLocation > EndIn) throw BadInput();
   root->data = element;

   // construct left subtree recursively
   root->LeftChild = BuildFromPreAndIn(InMap, StartIn,
                     InLocation-1, PreList, StartPre);

   // construct right subtree recursively
   root->RightChild = BuildFromPreAndIn(InMap,
                      InLocation+1, EndIn,
                      PreList, StartPre);

   return root;
}


void main(void)
{
   int n = 7;  // number of elements
   int InList[7] = {3, 5, 1, 0, 2, 6, 4};
   int PreList[7] = {0, 1, 3, 5, 2, 4, 6};
   int InMap[7];

//   12 element data set
//   int n = 12;  // number of elements
//   int InList[12] = {7, 3, 8, 11, 1, 4, 0, 9, 5, 2, 6, 10};
//   int PreList[12] = {0, 1, 3, 7, 8, 11, 4, 2, 5, 9, 6, 10};
//   int InMap[12];

// this data should throw an exception
//   int n = 12;  // number of elements
//   int InList[12] = {7, 3, 8, 11, 1, 4, 0, 9, 5, 2, 6, 10};
//   int PreList[12] = {0, 9, 3, 7, 8, 11, 4, 2, 5, 1, 6, 10};
//   int InMap[12];

   cout << "The given inorder list is ";
   for (int i = 0; i < n; i++)
      cout << InList[i] << "  ";
   cout << endl;

   cout << "and the given preorder list is ";
   for (i = 0; i < n; i++)
      cout << PreList[i] << "  ";
   cout << endl;

   // construct InMap
   // first construct inverse of InList
   int Inverse[100];
   for (i = 0; i < n; i++)
      Inverse[InList[i]] = i;
   // now construct InMap
   for (i = 0; i < n; i++)
      InMap[i] = Inverse[PreList[i]];

   cout << "The constructed mapping array is ";
   for (i = 0; i < n; i++)
      cout << InMap[i] << "  ";
   cout << endl;

   try {
      int StartPre = 0;
      BinaryTreeNode<int> * t =
         BuildFromPreAndIn(InMap, 0, n-1,
                           PreList, StartPre);
      cout << "Construction of binary tree is complete"
           << endl;

      cout << "Inorder sequence is ";
      InOrder(t);
      cout << endl;
      cout << "Preorder sequence is ";
      PreOrder(t);
      cout << endl;
      }
   catch (BadInput)
      {cout << "There is no binary tree for this"
            << endl;
      }
}
