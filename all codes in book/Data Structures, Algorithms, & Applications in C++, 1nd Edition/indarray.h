
#ifndef IndirectArray_
#define IndirectArray_
#include <iostream.h>

// header file indirect.h

template<class type>
class IndirectArray {
   public:
      IndirectArray(int MaxListSize = 10); // constructor
      ~IndirectArray(); // destructor
      int Length(); // number of elements in list
      int Find(int k, type& x); // return k'th element in x
      int Search(type x); // return position of x
      int Delete(int k, type& x); // delete k'th and return in x
      int Insert(int k, type x); // insert x just after k'th element
      // Find, Delete, Insert, and Search return 0 on failure
   private:
      int length, MaxSize, *table;
      type *element; // 1D array
};

template<class type>
IndirectArray<type>::IndirectArray(int MaxListSize)
{
   MaxSize = MaxListSize;
   element = new type[MaxSize];
   table = new int[MaxSize];
   length = 0;
}

template<class type>
IndirectArray<type>::~IndirectArray() {delete [] element; delete [] table;}

template<class type>
int IndirectArray<type>::Length()
{// Size of list.
   return length;
}

template<class type>
int IndirectArray<type>::Find(int k, type& x)
{// Find k'th element.
   if (k < 1 || k > length) return 0; // no k'th
   x = element[table[k - 1]];
   return 1;
}

template<class type>
int IndirectArray<type>::Search(type x)
{// Locate x.
   for (int i = 0; i < length; i++)
      if (element[table[i]] == x) return ++i;
   return 0;
}

template<class type>
int IndirectArray<type>::Delete(int k, type& x)
{// Delete k'th element.
   if (Find(k, x)) {// move elements k+1, ..., down
      for (int i = k; i < length; i++)
         table[i-1] = table[i];
      length--;
      return 1;}
   else return 0;
}

template<class type>
int IndirectArray<type>::Insert(int k, type x)
{// Insert x after k'th element.
   if (k < 0 || k > length || length == MaxSize) return 0;
   // move one up
   for (int i = length-1; i >= k; i--)
      table[i+1] = table[i];
   length++;
   element[k] = x;
   return 1;
}

#endif
