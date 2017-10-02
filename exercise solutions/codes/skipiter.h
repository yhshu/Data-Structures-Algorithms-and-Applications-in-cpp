

#ifndef SkipListIterator_
#define SkipListIterator_

#include "skip.h"

template<class E, class K>
class SkipListIterator {
   public:
      E* Begin(const SkipList<E,K>& c)
            {location = c.head->link[0];
             tail = c.tail;  // save pointer to tail
             if (location != tail)
                return &location->data;
             return 0;}
      E* Next()
            {if (location == tail) return 0;
             location = location->link[0];
             if (location != tail)
                return &location->data;
             return 0;}
   private:
      SkipNode<E,K> *location,  // current location
                    *tail;      // pointer to tail
};
 
#endif
