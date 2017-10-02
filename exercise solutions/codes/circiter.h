
// iterator for circular lists

#ifndef CircularIterator_
#define CircularIterator_


template<class T>
class CircularIterator {
   public:
      T* Initialize(const Circular<T>& c)
            {location = c.last;
             last = c.last;
             if (!location) return 0;
             location = last->link;
             return &location->data;
             }
      T* Next()
             {if (location == last)
                 // no more elements
                 return 0;
             location = location->link;
             return &location->data;
             }
   private:
      ChainNode<T> *location,  // current element
                   *last;      // last element in list
};
 
#endif
