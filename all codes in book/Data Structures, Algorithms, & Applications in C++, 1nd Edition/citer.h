
// file citer.h

#ifndef ChainIterator_
#define ChainIterator_

#include "chain.h"

template<class T>
class ChainIterator {
   public:
      T* Initialize(const Chain<T>& c)
            {location = c.first;
             if (location) return &location->data;
             return 0;}
      T* Next()
            {if (!location) return 0;
             location = location->link;
             if (location) return &location->data;
             return 0;}
   private:
      ChainNode<T> *location;
};
 
#endif
