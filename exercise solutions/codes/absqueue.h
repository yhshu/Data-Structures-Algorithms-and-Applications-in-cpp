

// abstract class AbstractQueue

#ifndef AbstractQueue_
#define AbstractQueue_


template<class T>
class AbstractQueue {
   public:
      virtual bool IsEmpty() const = 0;
      virtual bool IsFull() const = 0;
      virtual T First() const = 0; // return front element
      virtual T Last() const = 0;  // return last element
      virtual AbstractQueue<T>& Add(const T& x) = 0;
      virtual AbstractQueue<T>& Delete(T& x) = 0;
};

#endif
