// extended array implementation of a linear list
// This is arrayListWithIterator.h with methods to reset
// and clear linear lists and to set the value at an index added

#ifndef arrayList_
#define arrayList_

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include "linearList.h"
#include "myExceptions.h"
#include "changeLength1D.h"

using namespace std;

template<class T>
class arrayList : public linearList<T> 
{
   public:
      // constructor, copy constructor and destructor
      arrayList(int initialCapacity = 10);
      arrayList(const arrayList<T>&);
      ~arrayList() {delete [] element;}

      // ADT methods
      bool empty() const {return listSize == 0;}
      int size() const {return listSize;}
      T& get(int theIndex) const;
      int indexOf(const T& theElement) const;
      void erase(int theIndex);
      void insert(int theIndex, const T& theElement);
      void output(ostream& out) const;

      // additional methods
      int capacity() const {return arrayLength;}
      void reSet(int);
      void set(int, const T&);
      void clear() {listSize = 0;}
      
      // iterators to start and end of list
      class iterator;
      iterator begin() {return iterator(element);}
      iterator end() {return iterator(element + listSize);}

      // iterator for arrayList
      class iterator 
      {
         public:
            // typedefs required by C++ for a bidirectional iterator
            typedef bidirectional_iterator_tag iterator_category;
            typedef T value_type;
            typedef ptrdiff_t difference_type;
            typedef T* pointer;
            typedef T& reference;

            // constructor
            iterator(T* thePosition = 0) {position = thePosition;}

            // dereferencing operators
            T& operator*() const {return *position;}
            T* operator->() const {return &*position;}

            // increment
            iterator& operator++()   // preincrement
                      {++position; return *this;}
            iterator operator++(int) // postincrement
            	      {iterator old = *this;
            	       ++position;
            	       return old;
            	      }

            // decrement
            iterator& operator--()   // predecrement
                      {--position; return *this;}
            iterator operator--(int) // postdecrement
            	      {iterator old = *this;
            	       --position;
            	       return old;
            	      }

            // equality testing
            bool operator!=(const iterator right) const
                  {return position != right.position;}
            bool operator==(const iterator right) const
                  {return position == right.position;}
         protected:
            T* position;
      };  // end of iterator class

   protected:  // additional members of arrayList
      void checkIndex(int theIndex) const;
            // throw illegalIndex if theIndex invalid
      T* element;            // 1D array to hold list elements
      int arrayLength;       // capacity of the 1D array
      int listSize;          // number of elements in list
};

template<class T>
arrayList<T>::arrayList(int initialCapacity)
{// Constructor.
   if (initialCapacity < 1)
   {ostringstream s;
    s << "Initial capacity = " << initialCapacity << " Must be > 0";
    throw illegalParameterValue(s.str());
   }
   arrayLength = initialCapacity;
   element = new T[arrayLength];
   listSize = 0;
}

template<class T>
arrayList<T>::arrayList(const arrayList<T>& theList)
{// Copy constructor.
   arrayLength = theList.arrayLength;
   listSize = theList.listSize;
   element = new T[arrayLength];
   copy(theList.element, theList.element + listSize, element);
}

template<class T>
void arrayList<T>::reSet(int theSize)
{// Set list size to theSize and ensure that element array
 // is large enough for this many elements.
   if (theSize < 0)
   {ostringstream s;
    s << "Requested size = " << theSize << " Must be >= 0";
    throw illegalParameterValue(s.str());
   }

   if (theSize > arrayLength)
   {// need a larger array
      delete element;
      element = new T[theSize];
      arrayLength = listSize;
   }
   listSize = theSize;
}

template<class T>
void arrayList<T>::checkIndex(int theIndex) const
{// Verify that theIndex is between 0 and listSize - 1.
   if (theIndex < 0 || theIndex >= listSize)
   {ostringstream s;
    s << "index = " << theIndex << " size = " << listSize;
    throw illegalIndex(s.str());
   }
}

template<class T>
T& arrayList<T>::get(int theIndex) const
{// Return element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
   checkIndex(theIndex);
   return element[theIndex];
}

template<class T>
void arrayList<T>::set(int theIndex, const T& newValue)
{// Set element whose index is theIndex to newValue.
 // Throw illegalIndex exception if no such element.
   checkIndex(theIndex);
   element[theIndex] = newValue;
}

template<class T>
int arrayList<T>::indexOf(const T& theElement) const
{// Return index of first occurrence of theElement.
 // Return -1 if theElement not in list.

   // search for theElement
   int theIndex = (int) (find(element, element + listSize, theElement)
                         - element);

   // check if theElement was found
   if (theIndex == listSize)
     // not found
     return -1;
   else return theIndex;
 }

template<class T>
void arrayList<T>::erase(int theIndex)
{// Delete the element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
   checkIndex(theIndex);

   // valid index, shift elements with higher index
   copy(element + theIndex + 1, element + listSize,
                                element + theIndex);

   element[--listSize].~T(); // invoke destructor
}

template<class T>
void arrayList<T>::insert(int theIndex, const T& theElement)
{// Insert theElement so that its index is theIndex.
   if (theIndex < 0 || theIndex > listSize)
   {// invalid index
      ostringstream s;
      s << "index = " << theIndex << " size = " << listSize;
      throw illegalIndex(s.str());
   }

   // valid index, make sure we have space
   if (listSize == arrayLength)
      {// no space, double capacity
         changeLength1D(element, arrayLength, 2 * arrayLength);
         arrayLength *= 2;
      }

   // shift elements right one position
   copy_backward(element + theIndex, element + listSize,
                 element + listSize + 1);

   element[theIndex] = theElement;

   listSize++;
}

template<class T>
void arrayList<T>::output(ostream& out) const
{// Put the list into the stream out.
   copy(element, element + listSize, ostream_iterator<T>(cout, "  "));
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const arrayList<T>& x)
   {x.output(out); return out;}

#endif
