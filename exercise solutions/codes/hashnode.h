
#ifndef HashNode_
#define HashNode_

template <class E, class K> class ChainHashTable;
template <class E, class K> class ChainHashWithTail;

template <class E, class K>
class HashNode {
   friend ChainHashTable<E,K>;
   friend ChainHashWithTail<E,K>;
   private:
      E data;
      HashNode<E,K> *link;
};

#endif
