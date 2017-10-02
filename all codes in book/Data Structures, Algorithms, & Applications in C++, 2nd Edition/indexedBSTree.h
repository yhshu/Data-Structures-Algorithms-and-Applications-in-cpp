// abstract class indexedBSTree
// abstract data type specification for indexed binary search trees
// all methods are pure virtual functions
// K is key type and E is value type

#ifndef indexedBSTree_
#define indexedBSTree_

#include "bsTree.h"

using namespace std;

template<class K, class E>
class indexedBSTree : public bsTree<K,E>
{
   public:
      virtual pair<const K, E>* get(int) const = 0;
                  // return pointer to pair with given index
      virtual void delete(int) = 0;
                  // delete pair with given index
};
#endif

