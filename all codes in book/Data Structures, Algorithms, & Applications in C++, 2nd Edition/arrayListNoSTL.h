// array implementation of a linear list
// derives from abstract class linearList just to make sure
// all methods of the ADT are implemented
// code does not use STL algorithms

#ifndef arrayListNoSTL_
#define arrayListNoSTL_

#include<iostream>
#include<sstream>
#include<string>
#include "linearList.h"
#include "myExceptions.h"
#include "changeLength1D.h"

using namespace std;

template<class T>
class arrayListNoSTL : public linearList<T> 
{
   public:
      // constructor, copy constructor and destructor
      arrayListNoSTL(int initialCapacity = 10);
      arrayListNoSTL(const arrayListNoSTL<T>&);
      ~arrayListNoSTL() {delete [] element;}

      // ADT methods
      bool empty() const {return listSize == 0;}
      int size() const {return listSize;}
      T& get(int theIndex) const;
      int indexOf(const T& theElement) const;
      void erase(int theIndex);
      void insert(int theIndex, const T& theElement);
      void output(ostream& out) const;

      // additional method
      int capacity() const {return arrayLength;}

   protected:
      void checkIndex(int theIndex) const;
            // throw illegalIndex if theIndex invalid
      T* element;            // 1D array to hold list elements
      int arrayLength;       // capacity of the 1D array
      int listSize;          // number of elements in list
};

template<class T>
arrayListNoSTL<T>::arrayListNoSTL(int initialCapacity)
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
arrayListNoSTL<T>::arrayListNoSTL(const arrayListNoSTL<T>& theList)
{// Copy constructor.
   arrayLength = theList.arrayLength;
   listSize = theList.listSize;
   element = new T[arrayLength];

   // copy the list elements
   for (int i = 0; i < listSize; i++)
      element[i] = theList.element[i];
}

template<class T>
void arrayListNoSTL<T>::checkIndex(int theIndex) const
{// Verify that theIndex is between 0 and listSize - 1.
   if (theIndex < 0 || theIndex >= listSize)
   {ostringstream s;
    s << "index = " << theIndex << " size = " << listSize;
    throw illegalIndex(s.str());
   }

}

template<class T>
T& arrayListNoSTL<T>::get(int theIndex) const
{// Return element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
   checkIndex(theIndex);
   return element[theIndex];
}

template<class T>
int arrayListNoSTL<T>::indexOf(const T& theElement) const
{// Return index of first occurrence of theElement.
 // Return -1 if theElement not in list.

   // search for theElement
   for (int i = 0; i < listSize; i++)
      if (element[i] == theElement) return i;

   // theElement not found
   return -1;
 }

template<class T>
void arrayListNoSTL<T>::erase(int theIndex)
{// Delete the element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
    checkIndex(theIndex);

    // valid index, shift elements with higher index
    for (int i = theIndex + 1; i < listSize; i++)
       element[i-1] = element[i];

    element[--listSize].~T();  // destructor for T
}

template<class T>
void arrayListNoSTL<T>::insert(int theIndex, const T& theElement)
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
   for (int i = listSize-1; i >= theIndex; i--)
      element[i + 1] = element[i];

   element[theIndex] = theElement;

   listSize++;
}

template<class T>
void arrayListNoSTL<T>::output(ostream& out) const
{// Put the list into the stream out.
   for (int i = 0; i < listSize; i++)
      out << element[i] << "  ";
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const arrayListNoSTL<T>& x)
   {x.output(out); return out;}

#endif
