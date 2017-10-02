

// iterator for doubly-linked circular lists

#ifndef DoubleCircularIterator_
#define DoubleCircularIterator_


template<class T>
class DoubleCircularIterator {
   public:
      T* Initialize(const DoubleCircular<T>& c)
            {location = c.last;
             last = c.last;
             if (!location) return 0;
             location = last->right;
             return &location->data;
             }
      T* Next()
             {if (location == last)
                 // no more elements
                 return 0;
             location = location->right;
             return &location->data;
             }
   private:
      DoubleNode<T> *location,  // current element
                    *last;      // last element in list
};
 
#endif
