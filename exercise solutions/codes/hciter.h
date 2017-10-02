

// iterator for circular lists

#ifndef HCircularIterator_
#define HCircularIterator_


template<class T>
class HCircularIterator {
   public:
      T* Initialize(const HCircular<T>& c)
            {location = c.head->link;
             head = c.head;
             if (location == head) return 0;
             else return &location->data;
             }
      T* Next()
             {if (location->link == head)
                 // no more elements
                 return 0;
             location = location->link;
             return &location->data;
             }
   private:
      ChainNode<T> *location,  // current element
                   *head;      // head node
};
 
#endif
