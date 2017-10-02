// vector implementation of a linear list
// derives from abstract class linearList just to make sure
// all methods of the ADT are implemented
// USES STL ALGORITHMS TO SIMPLIFY CODE
// iterator class for vectorList included

#ifndef vectorList_
#define vectorList_

#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<algorithm>
#include<iterator>
#include "linearList.h"
#include "myExceptions.h"

using namespace std;

template<class T>
class vectorList : public linearList<T> 
{
   public:
      // constructor, copy constructor and destructor
      vectorList(int initialCapacity = 10);
      vectorList(const vectorList<T>&);
      ~vectorList() {delete element;}

      // ADT methods
      bool empty() const {return element->empty();}
      int size() const {return (int) element->size();}
      T& get(int theIndex) const;
      int indexOf(const T& theElement) const;
      void erase(int theIndex);
      void insert(int theIndex, const T& theElement);
      void output(ostream& out) const;

      // additional method
      int capacity() const {return (int) element->capacity();}
      
      // iterators to start and end of list
      typedef typename vector<T>::iterator iterator;
      iterator begin() {return element->begin();}
      iterator end() {return element->end();}

   protected:  // additional members of vectorList
      void checkIndex(int theIndex) const;
      vector<T>* element;     // vector to hold list elements
};

template<class T>
vectorList<T>::vectorList(int initialCapacity)
{// Constructor.
   if (initialCapacity < 1)
   {ostringstream s;
    s << "Initial capacity = " << initialCapacity << " Must be > 0";
    throw illegalParameterValue(s.str());
   }

   element = new vector<T>;
            // create an empty vector with capacity 0
   element->reserve(initialCapacity);
            // increase vector capacity from 0 to initialCapacity
}

template<class T>
vectorList<T>::vectorList(const vectorList<T>& theList)
{// Copy constructor.
   element = new vector<T>(*theList.element);
}

template<class T>
void vectorList<T>::checkIndex(int theIndex) const
{// Verify that theIndex is between 0 and size() - 1.
   if (theIndex < 0 || theIndex >= size())
   {ostringstream s;
    s << "index = " << theIndex << " size = " << size();
    throw illegalIndex(s.str());
   }

}

template<class T>
T& vectorList<T>::get(int theIndex) const
{// Return element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
   checkIndex(theIndex);
   return (*element)[theIndex];
}

template<class T>
int vectorList<T>::indexOf(const T& theElement) const
{// Return index of first occurrence of theElement.
 // Return -1 if theElement not in list.

   // search for theElement
   int theIndex = (int) (find(element->begin(), element->end(),
                         theElement)
                         - element->begin());

   // check if theElement was found
   if (theIndex == size())
     // not found
     return -1;
   else return theIndex;
 }

template<class T>
void vectorList<T>::erase(int theIndex)
{// Delete the element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
   checkIndex(theIndex);
   element->erase(begin() + theIndex);
}

template<class T>
void vectorList<T>::insert(int theIndex, const T& theElement)
{// Insert theElement so that its index is theIndex.
   if (theIndex < 0 || theIndex > size())
   {// invalid index
      ostringstream s;
      s << "index = " << theIndex << " size = " << size();
      throw illegalIndex(s.str());
   }

   element->insert(element->begin() + theIndex, theElement);
           // may throw an uncaught exception if insufficient
           // memory to resize vector
}

template<class T>
void vectorList<T>::output(ostream& out) const
{// Put the list into the stream out.
   copy(element->begin(), element->end(), ostream_iterator<T>(cout, "  "));
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const vectorList<T>& x)
   {x.output(out); return out;}

#endif
