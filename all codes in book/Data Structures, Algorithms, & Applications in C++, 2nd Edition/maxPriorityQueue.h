// abstract class max priority queue
// all methods are pure virtual functions

#ifndef maxPriorityQueue_
#define maxPriorityQueue_

using namespace std;

template<class T>
class maxPriorityQueue 
{
   public:
      virtual ~maxPriorityQueue() {}
      virtual bool empty() const = 0;
                  // return true iff queue is empty
      virtual int size() const = 0;
                  // return number of elements in queue
      virtual const T& top() = 0;
                  // return reference to the max element
      virtual void pop() = 0;
                  // remove the top element
      virtual void push(const T& theElement) = 0;
                  // add theElement to the queue
};
#endif

