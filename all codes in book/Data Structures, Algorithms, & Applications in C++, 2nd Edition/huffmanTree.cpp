// Huffman tree

#include <iostream>
#include "minHeap.h"
#include "linkedBinaryTree.h"
#include "huffmanNode.h"

using namespace std;

template <class T>
linkedBinaryTree<int>* huffmanTree(T weight[], int n)
{// Generate Huffman tree with weights weight[1:n], n >= 1.
   // create an array of single node trees
   huffmanNode<T> *hNode = new huffmanNode<T> [n + 1];
   linkedBinaryTree<int> emptyTree;
   for (int i = 1; i <= n; i++)
   {
      hNode[i].weight = weight[i];
      hNode[i].tree = new linkedBinaryTree<int>;
      hNode[i].tree->makeTree(i, emptyTree, emptyTree);
   }

   // make node array into a min heap
   minHeap<huffmanNode<T> > heap(1);
   heap.initialize(hNode, n);

   // repeatedly combine trees from min heap
   // until only one tree remains
   huffmanNode<T> w, x, y;
   linkedBinaryTree<int> *z;
   for (i = 1; i < n; i++)
   {
      // remove two lightest trees from the min heap
      x = heap.top(); heap.pop();
      y = heap.top(); heap.pop();

      // combine into a single tree
      z = new linkedBinaryTree<int>;
      z->makeTree(0, *x.tree, *y.tree);
      w.weight = x.weight + y.weight;
      w.tree = z;
      heap.push(w);
      delete x.tree;
      delete y.tree;
   }

   // destructor for min heap deletes hNode
   return heap.top().tree;
}

int main(void)
{
   int a[11];
   int n = 10;
   for (int i = 1; i <= n; i++)
      a[i] = 2 * i;
   linkedBinaryTree<int> *x = huffmanTree(a, n);
   x->postOrderOutput();
   return 0;
}
