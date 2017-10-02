// abstract class stack
// abstract data type specification for stack data structure
// all methods are pure virtual functions

#ifndef stack_
#define stack_

using namespace std;

template<class T>
class stack 
{
   public:
      virtual ~stack() {}
      virtual bool empty() const = 0;
                  // return true iff stack is empty
      virtual int size() const = 0;
                  // return number of elements in stack
      virtual T& top() = 0;
                  // return reference to the top element
      virtual void pop() = 0;
                  // remove the top element
      virtual void push(const T& theElement) = 0;
                  // insert theElement at the top of the stack
};
#endif

