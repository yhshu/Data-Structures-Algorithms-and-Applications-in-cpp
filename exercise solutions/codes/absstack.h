
// abstract class AbstractStack

#ifndef AbstractStack_
#define AbstractStack_


template<class T>
class AbstractStack {
   public:
      virtual bool IsEmpty() const = 0;
      virtual bool IsFull() const = 0;
      virtual T Top() const = 0;
      virtual AbstractStack<T>& Add(const T& x) = 0;
      virtual AbstractStack<T>& Delete(T& x) = 0;
};

#endif
