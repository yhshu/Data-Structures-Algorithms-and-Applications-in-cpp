// chain with bin sort included

#ifndef chain_
#define chain_

#include<iostream>
#include<sstream>
#include<string>
#include "linearList.h"
#include "chainNode.h"
#include "myExceptions.h"
#include "studentRecord2.h"

using namespace std;

template<class T>
class chain : public linearList<T> 
{
   public:
      // constructor, copy constructor and destructor
      chain(int initialCapacity = 10);
      chain(const chain<T>&);
      ~chain();

      // ADT methods
      bool empty() const {return listSize == 0;}
      int size() const {return listSize;}
      T& get(int theIndex) const;
      int indexOf(const T& theElement) const;
      void erase(int theIndex);
      void insert(int theIndex, const T& theElement);
      void output(ostream& out) const;

      // additional methods
      void binSort(int range);
      void binSort(int range, int(*value)(T& x));

   protected:
      void checkIndex(int theIndex) const;
            // throw illegalIndex if theIndex invalid
      chainNode<T>* firstNode;  // pointer to first node in chain
      int listSize;             // number of elements in list
};

template<class T>
chain<T>::chain(int initialCapacity)
{// Constructor.
   if (initialCapacity < 1)
   {ostringstream s;
    s << "Initial capacity = " << initialCapacity << " Must be > 0";
    throw illegalParameterValue(s.str());
   }
   firstNode = NULL;
   listSize = 0;
}

template<class T>
chain<T>::chain(const chain<T>& theList)
{// Copy constructor.
   listSize = theList.listSize;

   if (listSize == 0)
   {// theList is empty
      firstNode = NULL;
      return;
   }

   // non-empty list
   chainNode<T>* sourceNode = theList.firstNode;
                    // node in theList to copy from
   firstNode = new chainNode<T>(sourceNode->element);
                    // copy first element of theList
   sourceNode = sourceNode->next;
   chainNode<T>* targetNode = firstNode;
                    // current last node in *this
   while (sourceNode != NULL)
   {// copy remaining elements
      targetNode->next = new chainNode<T>(sourceNode->element);
      targetNode = targetNode->next;
      sourceNode = sourceNode->next;
   }
   targetNode->next = NULL; // end the chain
}

template<class T>
chain<T>::~chain()
{// Chain destructor. Delete all nodes in chain.
   chainNode<T> *nextNode;
   while (firstNode != NULL)
   {// delete firstNode
      nextNode = firstNode->next;
      delete firstNode;
      firstNode = nextNode;
   }
}

template<class T>
void chain<T>::checkIndex(int theIndex) const
{// Verify that theIndex is between 0 and listSize - 1.
   if (theIndex < 0 || theIndex >= listSize)
   {ostringstream s;
    s << "index = " << theIndex << " size = " << listSize;
    throw illegalIndex(s.str());
   }

}

template<class T>
T& chain<T>::get(int theIndex) const
{// Return element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
   checkIndex(theIndex);

   // move to desired node
   chainNode<T>* currentNode = firstNode;
   for (int i = 0; i < theIndex; i++)
      currentNode = currentNode->next;

   return currentNode->element;
}

template<class T>
int chain<T>::indexOf(const T& theElement) const
{// Return index of first occurrence of theElement.
 // Return -1 if theElement not in list.

   // search the chain for theElement
   chainNode<T>* currentNode = firstNode;
   int index = 0;  // index of currentNode
   while (currentNode != NULL && 
          currentNode->element != theElement)
   {
      // move to next node
      currentNode = currentNode->next;
      index++;
   }

   // make sure we found matching element
   if (currentNode == NULL)
      return -1;
   else
      return index;
}

template<class T>
void chain<T>::erase(int theIndex)
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
   }
   listSize--;
   delete deleteNode;
}

template<class T>
void chain<T>::insert(int theIndex, const T& theElement)
{// Insert theElement so that its index is theIndex.
   if (theIndex < 0 || theIndex > listSize)
   {// invalid index
      ostringstream s;
      s << "index = " << theIndex << " size = " << listSize;
      throw illegalIndex(s.str());
   }

   if (theIndex == 0)
      // insert at front
      firstNode = new chainNode<T>(theElement, firstNode);
   else
   {  // find predecessor of new element
      chainNode<T>* p = firstNode;
      for (int i = 0; i < theIndex - 1; i++)
         p = p->next;
   
      // insert after p
      p->next = new chainNode<T>(theElement, p->next);
   }
   listSize++;
}

template<class T>
void chain<T>::output(ostream& out) const
{// Put the list into the stream out.
   for (chainNode<T>* currentNode = firstNode;
                      currentNode != NULL;
                      currentNode = currentNode->next)
      out << currentNode->element << "  ";
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const chain<T>& x)
   {x.output(out); return out;}


template<class T>
void chain<T>::binSort(int range)
{// Sort the nodes in the chain.
   // create and initialize the bins
   chainNode<T> **bottom, **top;
   bottom = new chainNode<T>* [range + 1];
   top = new chainNode<T>* [range + 1];
   for (int b = 0; b <= range; b++)
      bottom[b] = NULL;
   
   // distribute to bins
   for (; firstNode != NULL; firstNode = firstNode->next)
   {// add firstNode to proper bin
      int theBin = firstNode->element; // type conversion to int
      if (bottom[theBin] == NULL) // bin is empty
        bottom[theBin] = top[theBin] = firstNode;
      else
      {// bin not empty
        top[theBin]->next = firstNode;
        top[theBin] = firstNode;
      }
   }
   
   // collect from bins into sorted chain
   chainNode<T> *y = NULL;
   for (int theBin = 0; theBin <= range; theBin++)
      if (bottom[theBin] != NULL)
      {// bin not empty
         if (y == NULL) // first nonempty bin
            firstNode = bottom[theBin];
         else // not first nonempty bin
            y->next = bottom[theBin];
         y = top[theBin];
      }  
   if (y != NULL)
      y->next = NULL;
   
   delete [] bottom;
   delete [] top;
}

template<class T>
void chain<T>::binSort(int range, int(*value)(T& x))
{// Sort the nodes in the chain. The sort key is value(theElement).
   // create and initialize the bins
   chainNode<T> **bottom, **top;
   bottom = new chainNode<T>* [range + 1];
   top = new chainNode<T>* [range + 1];
   for (int b = 0; b <= range; b++)
      bottom[b] = NULL;
   
   // distribute to bins
   for (; firstNode != NULL; firstNode = firstNode->next)
   {// add firstNode to proper bin
      int theBin = value(firstNode->element);
                         // type conversion to int
      if (bottom[theBin] == NULL) // bin is empty
        bottom[theBin] = top[theBin] = firstNode;
      else
      {// bin not empty
        top[theBin]->next = firstNode;
        top[theBin] = firstNode;
      }
   }
   
   // collect from bins into sorted chain
   chainNode<T> *y = NULL;
   for (int theBin = 0; theBin <= range; theBin++)
      if (bottom[theBin] != NULL)
      {// bin not empty
         if (y == NULL) // first nonempty bin
            firstNode = bottom[theBin];
         else // not first nonempty bin
            y->next = bottom[theBin];
         y = top[theBin];
      }  
   if (y != NULL)
      y->next = NULL;
   
   delete [] bottom;
   delete [] top;
}
#endif
