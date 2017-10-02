#ifndef SortedChainNode_
#define SortedChainNode_

template <class E, class K> class SortedChain;

template <class E, class K>
class SortedChainNode {
   friend SortedChain<E,K>;
   private:
      E data;
      SortedChainNode<E,K> *link;
};

#endif
