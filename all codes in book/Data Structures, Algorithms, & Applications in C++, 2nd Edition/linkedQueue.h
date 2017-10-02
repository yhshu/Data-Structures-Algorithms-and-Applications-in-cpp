
// linked implementation of a queue
// derives from the ADT queue

#ifndef linkedQueue_
#define linkedQueue_

#include "queue.h"
#include "chainNode.h"
#include "myExceptions.h"
#include <sstream>

using namespace std;

template<class T>
class linkedQueue : public queue<T>
{
   public:
      linkedQueue(int initialCapacity = 10)
            {queueFront = NULL; queueSize = 0;}
      ~linkedQueue();
      bool empty() const 
           {return queueSize == 0;}
      int size() const
          {return queueSize;}
      T& front()
         {
            if (queueSize == 0)
               throw queueEmpty();
            return queueFront->element;
         }
      T& back()
         {
            if (queueSize == 0)
               throw queueEmpty();
            return queueBack->element;
         }
      void pop();
      void push(const T&);
   private:
      chainNode<T>* queueFront;  // pointer to queue front
      chainNode<T>* queueBack;   // pointer to queue back
      int queueSize;             // number of elements in queue
};

template<class T>
linkedQueue<T>::~linkedQueue()
{// Destructor.
   while (queueFront != NULL)
   {// delete front node
      chainNode<T>* nextNode = queueFront->next;
      delete queueFront;
      queueFront = nextNode;
   }
}

template<class T>
void linkedQueue<T>::pop()
{// Delete front element.
   if (queueFront == NULL)
      throw queueEmpty();

   chainNode<T>* nextNode = queueFront->next;
   delete queueFront;
   queueFront = nextNode;
   queueSize--;
}


template<class T>
void linkedQueue<T>::push(const T& theElement)
{// Add theElement to back of queue.

   // create node for new element
   chainNode<T>* newNode = new chainNode<T>(theElement, NULL);

   // add new node to back of queue
   if (queueSize == 0)
      queueFront = newNode;       // queue empty
   else 
      queueBack->next = newNode;  // queue not empty
   queueBack = newNode;

   queueSize++;
}
#endif
