// linked implementation of an extended linear list
// derives from abstract class extendedLinearList just to make sure
// all methods of the ADT are implemented
// unidirectional iterator for extendedChain included

#ifndef extendedChain_
#define extendedChain_

#include <iostream>
#include <sstream>
#include <string>
#include "extendedLinearList.h"
#include "chainWithIterator.h"
#include "myExceptions.h"

using namespace std;

template<class T>
class extendedChain : public extendedLinearList<T>, public chain<T> 
{
   public:
      // constructor and copy constructor
      extendedChain(int initialCapacity = 10) :
         chain<T>(initialCapacity) {}
      extendedChain(const extendedChain<T>& c) :
         chain<T>(c) {}

      // ADT methods
      bool empty() const {return listSize == 0;}
      int size() const {return listSize;}
      T& get(int theIndex) const
         {return chain<T>::get(theIndex);}
      int indexOf(const T& theElement) const
         {return chain<T>::indexOf(theElement);}
      void erase(int theIndex);
      void insert(int theIndex, const T& theElement);
      void clear()
         {// Delete all nodes in chain.
            while (firstNode != NULL)
            {// delete firstNode
               chainNode<T>* nextNode = firstNode->next;
               delete firstNode;
               firstNode = nextNode;
            }
            listSize = 0;
         }
      void push_back(const T& theElement);
      void output(ostream& out) const
         {chain<T>::output(out);}

      // additional method
      void zero()
         {firstNode = NULL; listSize = 0;}
      
   protected:
      chainNode<T>* lastNode;  // pointer to last node in chain
};


template<class T>
void extendedChain<T>::erase(int theIndex)
{// Delete the element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
   checkIndex(theIndex);

   // valid index, locate node with element to delete
   chainNode<T>* deleteNode;
   if (theIndex == 0)
   {// remove first node from chain
      deleteNode = firstNode;
      firstNode = firstNode->next;
   }
   else 
   {  // use p to get to predecessor of desired node
      chainNode<T>* p = firstNode;
      for (int i = 0; i < theIndex - 1; i++)
         p = p->next;
   
      deleteNode = p->next;
      p->next = p->next->next; // remove deleteNode from chain
      if (deleteNode == lastNode)
         lastNode = p;
   }
   listSize--;
   delete deleteNode;
}

template<class T>
void extendedChain<T>::insert(int theIndex, const T& theElement)
{// Insert theElement so that its index is theIndex.
   if (theIndex < 0 || theIndex > listSize)
   {// invalid index
      ostringstream s;
      s << "index = " << theIndex << " size = " << listSize;
      throw illegalIndex(s.str());
   }

   if (theIndex == 0)
      {// insert at front
         firstNode = new chainNode<T>(theElement, firstNode);
         if (listSize == 0)
            lastNode = firstNode;
      }
   else
   {  // find predecessor of new element
      chainNode<T>* p = firstNode;
      for (int i = 0; i < theIndex - 1; i++)
         p = p->next;
   
      // insert after p
      p->next = new chainNode<T>(theElement, p->next);
      if (listSize == theIndex)
         lastNode = p->next;
   }
   listSize++;
}

template<class T>
void extendedChain<T>::push_back(const T& theElement)
{// Insert theElement at the end of the chain.
   chainNode<T>* newNode = new chainNode<T>(theElement, NULL);
   if (firstNode == NULL)
      // chain is empty
      firstNode = lastNode = newNode;
   else
   {  // attach next to lastNode
      lastNode->next = newNode;
      lastNode = newNode;
   }
   listSize++;
}


#endif
