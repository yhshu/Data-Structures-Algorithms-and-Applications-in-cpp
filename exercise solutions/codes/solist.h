
// formula-based sorted linear list
#ifndef SortedList_
#define SortedList_
#include <stdlib.h>
#include <iostream.h>
#include "xcept.h"

template<class E, class K>
class SortedList {
   public:
      SortedList(int MaxListSize = 10); // constructor
      ~SortedList() {delete [] element;} // destructor
      bool IsEmpty() const {return length == 0;}
      int Length() const {return length;}
      bool Search(const K& k, E& e) const;
      SortedList<E,K>& Delete(const K& k, E& e);
      SortedList<E,K>& Insert(const E& e);
      SortedList<E,K>& DistinctInsert(const E& e);
      void Output(ostream& out) const;
   private:
      int length;
      int MaxSize;
      E *element; // dynamic 1D array
};

template<class E, class K>
SortedList<E,K>::SortedList(int MaxListSize)
{// Constructor for formula-based sorted list.
   MaxSize = MaxListSize;
   element = new E [MaxSize];
   length = 0;
}

template<class E, class K>
bool SortedList<E,K>::Search(const K& k, E& e) const
{// Put element that matches k in e.
 // Return false if no match.
   // examine elements from left to right
   int i = 0;
   while (i < length && k > element[i])
      i++;

   // verify match
   if (i >= length || k != element[i]) return false;

   // there is a match
   e = element[i];
   return true;
 }

template<class E, class K>
SortedList<E,K>& SortedList<E,K>::
                 Delete(const K& k, E& e)
{// Delete element that matches k.
 // Return deleted element in e.
 // Throw BadInput exception if no match.

   // search for matching element
   int i = 0;
   while (i < length && k > element[i])
      i++;

   // verify match
   if (i >= length || k != element[i])
      throw BadInput();  // no match

   // put matching element in e and delete
   e = element[i];
   for (int j = i + 1; j < length; j++)
      // shift element left by one
      element[j-1] = element[j];
   length--;  // new list length

   return *this;
}

template<class E, class K>
SortedList<E,K>& SortedList<E,K>::
                 Insert(const E& e)
{// Insert e.  Throw NoMem exception if no space.
   if (length == MaxSize) throw NoMem();

   // find proper place to insert
   // when done, insert to left of element[i]
   int i = 0;
   while (i < length && e > element[i])
      i++;

   // move element[i:length - 1] one spot right
   for (int j = length-1; j >= i; j--)
      element[j+1] = element[j];

   // insert e
   element[i] = e;
   length++;

   return *this;
}

template<class E, class K>
SortedList<E,K>& SortedList<E,K>::
                 DistinctInsert(const E& e)
{// Insert e only if no matching element present.
 // Throw BadInput exception if duplicate.
 // Throw NoMem exception if no space.

   // find proper place to insert
   // when done, insert to left of element[i]
   int i = 0;
   while (i < length && e > element[i])
      i++;
   
   // check if duplicate
   if (i < length && e == element[i])
      throw BadInput();  // duplicate

   // make sure we have space for new element
   if (length == MaxSize) throw NoMem();

   // move element[i:length - 1] one spot right
   for (int j = length-1; j >= i; j--)
      element[j+1] = element[j];

   // insert e
   element[i] = e;
   length++;

   return *this;
}

template<class E, class K>
void SortedList<E,K>::Output(ostream& out) const
{// Put the list into the stream out.
   for (int i = 0; i < length; i++)
      out << element[i] << "  ";
}

// overload <<
template <class E, class K>
ostream& operator<<(ostream& out,
         const SortedList<E,K>& x)
   {x.Output(out); return out;}

#endif
