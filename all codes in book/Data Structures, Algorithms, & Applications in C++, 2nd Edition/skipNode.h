// node type used in skip lists
// node with a next and element field; element is a pair<const K, E>
// next is a 1D array of pointers

#ifndef skipNode_
#define skipNode_

template <class K, class E>
struct skipNode 
{
   typedef pair<const K, E> pairType;
   pairType element;
   skipNode<K,E> **next;   // 1D array of pointers

   skipNode(const pairType& thePair, int size)
            :element(thePair){next = new skipNode<K,E>* [size];}
};

#endif
