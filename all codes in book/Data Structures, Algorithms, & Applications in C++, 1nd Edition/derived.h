// file derived.h
// IndirectList as a derived class of LinearList

#ifndef DIndirectList_
#define DIndirectList_
#include "llist.h"

template<class type>
class IndirectList : protected LinearList<type *> {
   public:
      IndirectList(int MaxListSize = 10) :
          LinearList<type *> (MaxListSize) {}
      int Length() {return LinearList<type *>::Length();}
      int Find(int k, type& x);
      int Search(type x);
      int Delete(int k, type& x);
      int Insert(int k, type x);
      // Find, Delete, Insert, and Search return 0 on failure
      void Print();
};

// find k'th element
template<class type>
int IndirectList<type>::Find(int k, type& x)
{
   type *p;
   int i = LinearList<type *>::Find(k, p);
   if (i) x = *p;
   return i;
}

// locate x
template<class type>
int IndirectList<type>::Search(type x)
{
   for (int i = 0; i < length; i++)
      if (*element[i] == x) return ++i;
   return 0;
}

// delete k'th element
template<class type>
int IndirectList<type>::Delete(int k, type& x)
{
   type *p;
   int i = LinearList<type *>::Delete(k, p);
   if (i) x = *p;
   return i;
}

// insert x after k'th element
template<class type>
int IndirectList<type>::Insert(int k, type x)
{
   type *p = new type;
   if (!p) {cerr << "Out Of Memory" << endl;
            exit(1);}
   *p = x;
   return LinearList<type *>::Insert(k, p);
}


template<class type>
void IndirectList<type>::Print()
{
   for (int i=0; i < length; i++) cout << *element[i];
   cout << endl;
}

#endif
