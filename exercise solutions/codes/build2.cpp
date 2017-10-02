

// build a binary tree from its postorder
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
void InOrder(BinaryTreeNode<T> *t)
{// Inorder traversal of *t.
   if (t) {
      InOrder(t->LeftChild);   // do left subtree
      Visit(t);                // visit tree root
      InOrder(t->RightChild);  // do right subtree
      }
}

template <class T>
void PostOrder(BinaryTreeNode<T> *t)
{// Postorder traversal of *t.
   if (t) {
      PostOrder(t->LeftChild);   // do left subtree
      PostOrder(t->RightChild);  // do right subtree
      Visit(t);                  // visit tree root
      }
}

BinaryTreeNode<int>* BuildFromPostAndIn
      (int InMap[], int StartIn, int EndIn,
       int PostList[], int &EndPost)
{// Return pointer to root of constructed binary
 // whose inorder list is
 // InList[StartIn:EndIn]
 // and whose postorder list is PostList[ ... EndPost].
 // InMap[i] is the location of PostList[i] in InList[].
 // That is, InList[InMap[PostList[i]]] = PostList[i].

   if (StartIn > EndIn) return 0;  // empty
  
   // create a node for the root and set its data field
   BinaryTreeNode<int> *root = new BinaryTreeNode<int>;
   int element = PostList[EndPost];
   // verify that element is in the
   // proper subtree
   int InLocation = InMap[EndPost--];
   if (InLocation < StartIn ||
       InLocation > EndIn) throw BadInput();
   root->data = element;

   // construct right subtree recursively
   root->RightChild = BuildFromPostAndIn(InMap,
                      InLocation+1, EndIn,
                      PostList, EndPost);

   // construct left subtree recursively
   root->LeftChild = BuildFromPostAndIn(InMap, StartIn,
                     InLocation-1, PostList, EndPost);

   return root;
}


void main(void)
{
   int n = 7;  // number of elements
   int InList[7] = {3, 5, 1, 0, 2, 6, 4};
   int PostList[7] = {5, 3, 1, 6, 4, 2, 0};
   int InMap[7];

//   12 element data set
//   int n = 12;  // number of elements
//   int InList[12] = {7, 3, 8, 11, 1, 4, 0, 9, 5, 2, 6, 10};
//   int PostList[12] = {7, 11, 8, 3, 4, 1, 9, 5, 10, 6, 2, 0};
//   int InMap[12];

// this data should throw an exception
//   int n = 12;  // number of elements
//   int InList[12] = {7, 3, 8, 11, 1, 4, 0, 9, 5, 2, 6, 10};
//   int PostList[12] = {7, 11, 9, 3, 4, 1, 8, 5, 10, 6, 2, 0};
//   int InMap[12];

   cout << "The given inorder list is ";
   for (int i = 0; i < n; i++)
      cout << InList[i] << "  ";
   cout << endl;

   cout << "and the given postorder list is ";
   for (i = 0; i < n; i++)
      cout << PostList[i] << "  ";
   cout << endl;

   // construct InMap
   // first construct inverse of InList
   int Inverse[100];
   for (i = 0; i < n; i++)
      Inverse[InList[i]] = i;
   // now construct InMap
   for (i = 0; i < n; i++)
      InMap[i] = Inverse[PostList[i]];

   cout << "The constructed mapping array is ";
   for (i = 0; i < n; i++)
      cout << InMap[i] << "  ";
   cout << endl;

   try {
      int EndPost = n-1;
      BinaryTreeNode<int> * t =
         BuildFromPostAndIn(InMap, 0, n-1,
                           PostList, EndPost);
      cout << "Construction of binary tree is complete"
           << endl;

      cout << "Inorder sequence is ";
      InOrder(t);
      cout << endl;
      cout << "Postorder sequence is ";
      PostOrder(t);
      cout << endl;
      }
   catch (BadInput)
      {cout << "There is no binary tree for this"
            << endl;
      }
}
