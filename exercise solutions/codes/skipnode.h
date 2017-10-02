#ifndef SkipNode_
#define SkipNode_

template <class E, class K>
class SkipList;

template <class E, class K>
class SkipListIterator;

template<class E, class K>
class SkipNode {
   friend SkipList<E,K>;
   friend SkipListIterator<E,K>;
   private:
      SkipNode(int size)
         {link = new SkipNode<E,K> *[size];}
      ~SkipNode() {delete [] link;}
      E data;
      SkipNode<E,K> **link;  // 1D array of pointers
};

#endif
