#ifndef SortedChainNode_
#define SortedChainNode_

template <class E, class K>
class SortedChain;

template <class E, class K>
class SortedChainWithTail;

template <class T, class K>
class SortedChainIterator;

template <class E, class K>
class SortedChainNode {
   friend SortedChain<E,K>;
   friend SortedChainWithTail<E,K>;
   friend SortedChainIterator<E, K>;
   private:
      E data;
      SortedChainNode<E,K> *link;
};

#endif
