// Huffman tree

#include <iostream.h>
#include "minheap.h"
#include "binary.h"
#include "huffman.h"

template <class T>
BinaryTree<int> HuffmanTree(T a[], int n)
{// Generate Huffman tree with weights a[1:n].
   // create an array of single node trees
   Huffman<T> *w = new Huffman<T> [n+1];
   BinaryTree<int> z, zero;
   for (int i = 1; i <= n; i++) {
      z.MakeTree(i, zero, zero);
      w[i].weight = a[i];
      w[i].tree = z;
      }

   // make array into a min heap
   MinHeap<Huffman<T> > H(1);
   H.Initialize(w,n,n);

   // repeatedly combine trees from heap
   Huffman<T> x, y;
   for (i = 1; i < n; i++) {
      H.DeleteMin(x);
      H.DeleteMin(y);
      z.MakeTree(0, x.tree, y.tree);
      x.weight += y.weight; x.tree = z;
      H.Insert(x);
      }

   H.DeleteMin(x); // final tree
   H.Deactivate();
   delete [] w;
   return x.tree;
}

void main(void)
{
   int a[11];
   int n = 10;
   BinaryTree<int> x;
   for (int i = 1; i <= n; i++)
      a[i] = 2*i;
   x = HuffmanTree(a,n);
   x.PostOutput();
}
