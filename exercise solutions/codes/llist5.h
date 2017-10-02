

// linear list with function to split a list included
// use Equation 3.2

#ifndef LinearList_
#define LinearList_
#include <stdlib.h>
#include <iostream.h>
#include "xcept.h"

template<class T>
class LinearList {
   public:
      LinearList(int MaxListSize = 10); // constructor
      ~LinearList() {delete [] element;} // destructor
      bool IsEmpty() const {return length == 0;}
      int Length() const {return length;}
      bool Find(int k, T& x) const;
         // return the k'th element of list in x
      int Search(const T& x) const;
         // return position of x
      LinearList<T>& Delete(int k, T& x);
         // delete k'th element and return in x
      LinearList<T>& Insert(int k, const T& x);
         // insert x just after k'th element
      LinearList<T>& Split(
            LinearList<T>& A, LinearList<T>& B);
      void Output(ostream& out) const;
   private:
      int length;
      int MaxSize;
      T *element; // dynamic 1D array
};

template<class T>
LinearList<T>::LinearList(int MaxListSize)
{// Constructor for formula-based linear list.
   MaxSize = MaxListSize;
   element = new T[MaxSize+1];
   length = 0;
}

template<class T>
bool LinearList<T>::Find(int k, T& x) const
{// Set x to the k'th element of the list.
 // Return false if no k'th; true otherwise.
   if (k < 1 || k > length) return false; // no k'th
   x = element[k];
   return true;
}

template<class T>
int LinearList<T>::Search(const T& x) const
{// Locate x.  Return position of x if found.
 // Return 0 if x not in list.
   for (int i = 1; i <= length; i++)
      if (element[i] == x) return i;
   return 0;
 }

template<class T>
LinearList<T>& LinearList<T>::Delete(int k, T& x)
{// Set x to the k'th element and delete it.
 // Throw OutOfBounds exception if no k'th element.
   if (Find(k, x)) {// move elements k+1, ..., down
      for (int i = k+1; i <= length; i++)
         element[i-1] = element[i];
      length--;
      return *this;
      }
   else throw OutOfBounds();
}

template<class T>
LinearList<T>& LinearList<T>::Insert(int k, const T& x)
{// Insert x after the k'th element.
 // Throw OutOfBounds exception if no k'th element.
 // Throw NoMem exception if list is already full.
   if (k < 0 || k > length) throw OutOfBounds();
   if (length == MaxSize) throw NoMem();
   // move one up
   for (int i = length; i > k; i--)
      element[i+1] = element[i];
   element[k+1] = x;
   length++;
   return *this;
}

template<class T>
void LinearList<T>::Output(ostream& out) const
{// Put the list into the stream out.
   for (int i = 1; i <= length; i++)
      out << element[i] << "  ";
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const LinearList<T>& x)
   {x.Output(out); return out;}

template <class T>
LinearList<T>& LinearList<T>::Split(
    LinearList<T>& A, LinearList<T>& B)
{// Split *this into lists A and B
   B.length = length / 2;
   A.length = length - B.length;
   if (A.length > A.MaxSize || B.length > B.MaxSize)
       throw NoMem(); // inadequate space for result
   
   int ct = 1;  // cursor for *this
   int cab = 1; // cursor for A and B
   while (cab <= B.length) {
      A.element[cab] = element[ct++];
      B.element[cab++] = element[ct++];
      }
   
   // is an element left?
   if (A.length > B.length)
      A.element[cab] = element[ct];
   
   return *this;
}

#endif
