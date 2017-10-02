#ifndef huffmanNode_
#define huffmanNode_

template<class T>
struct huffmanNode
{
   linkedBinaryTree<int> *tree;
   T weight;

   operator T () const {return weight;}
};

#endif
