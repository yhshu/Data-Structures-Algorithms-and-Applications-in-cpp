
// iterator for doubly-linked circular lists
// with a head node

#ifndef HDoubleCircularIterator_
#define HDoubleCircularIterator_


template<class T>
class HDoubleCircularIterator {
   public:
      T* Initialize(const HDoubleCircular<T>& c)
            {location = c.head->right;
             head = c.head;
             if (location == head) return 0;
             else return &location->data;
             }
      T* Next()
             {if (location->right == head)
                 // no more elements
                 return 0;
             location = location->right;
             return &location->data;
             }
   private:
      DoubleNode<T> *location,  // current element
                    *head;      // head node
};
 
#endif
