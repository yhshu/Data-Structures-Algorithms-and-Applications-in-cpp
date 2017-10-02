// circularList list with header node

#ifndef circularListWithHeader_
#define circularListWithHeader_

#include<iostream>
#include<sstream>
#include<string>
#include "chainNode.h"
#include "myExceptions.h"

using namespace std;

template<class T>
class circularListWithHeader 
{
   public:
      // constructor
      circularListWithHeader();

      // some methods
      int size() const {return listSize;}
      int indexOf(const T& theElement) const;
      void insert(int theIndex, const T& theElement);
      void output(ostream& out) const;

   protected:
      void checkIndex(int theIndex) const;
            // throw illegalIndex if theIndex invalid
      chainNode<T>* headerNode;  // pointer to header node
      int listSize;              // number of elements in list
};

template<class T>
circularListWithHeader<T>::circularListWithHeader()
{// Constructor.
   headerNode = new chainNode<T>();
   headerNode->next = headerNode;
   listSize = 0;
}

template<class T>
void circularListWithHeader<T>::checkIndex(int theIndex) const
{// Verify that theIndex is between 0 and listSize - 1.
   if (theIndex < 0 || theIndex >= listSize)
   {ostringstream s;
    s << "index = " << theIndex << " size = " << listSize;
    throw illegalIndex(s.str());
   }

}

template<class T>
int circularListWithHeader<T>::indexOf(const T& theElement) const
{// Return index of first occurrence of theElement.
 // Return -1 if theElement not in list.

   // Put theElement in header node
   headerNode->element = theElement;

   // search the chain for theElement
   chainNode<T>* currentNode = headerNode->next;
   int index = 0;  // index of currentNode
   while (currentNode->element != theElement)
   {
      // move to next node
      currentNode = currentNode->next;
      index++;
   }

   // make sure we found matching element
   if (currentNode == headerNode)
      return -1;
   else
      return index;
}

template<class T>
void circularListWithHeader<T>::insert(int theIndex, const T& theElement)
{// Insert theElement so that its index is theIndex.
   if (theIndex < 0 || theIndex > listSize)
   {// invalid index
      ostringstream s;
      s << "index = " << theIndex << " size = " << listSize;
      throw illegalIndex(s.str());
   }

   // find predecessor of new element
   chainNode<T>* p = headerNode;
   for (int i = 0; i < theIndex; i++)
      p = p->next;
   
   // insert after p
   p->next = new chainNode<T>(theElement, p->next);
   
   listSize++;
}

template<class T>
void circularListWithHeader<T>::output(ostream& out) const
{// Put the list into the stream out.
   for (chainNode<T>* currentNode = headerNode->next;
                      currentNode != headerNode;
                      currentNode = currentNode->next)
      out << currentNode->element << "  ";
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const circularListWithHeader<T>& x)
   {x.output(out); return out;}

#endif
