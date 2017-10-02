// file dlist.h
// IndirectList as a derived class of LinearList

#ifndef DIndirectList_
#define DIndirectList_
#include "llist.h"
#include <iostream.h>

template<class T>
class IndirectList : protected LinearList<T *> {
   public:
      IndirectList(int MaxListSize = 10) :
          LinearList<T *> (MaxListSize) {}
      bool IsEmpty() const {return LinearList<T *>::IsEmpty();}
      int Length() const {return LinearList<T *>::Length();}
      bool Find(int k, T& x) const;
      int Search(const T& x) const;
      IndirectList<T>& Delete(int k, T& x);
      IndirectList<T>& Insert(int k, const T& x);
      void Output(ostream& out) const;
};

template<class T>
bool IndirectList<T>::Find(int k, T& x) const
{// Find k'th element.
   T *p;
   int i = LinearList<T *>::Find(k, p);
   if (i) x = *p;
   return i;
}

template<class T>
int IndirectList<T>::Search(const T& x) const
{// Locate x.
   for (int i = 0; i < length; i++)
      if (*element[i] == x) return ++i;
   return 0;
}

template<class T>
IndirectList<T>& IndirectList<T>::Delete(int k, T& x)
{// Delete k'th element.
   T *p;
   LinearList<T *>::Delete(k, p);
   x = *p;
   return *this;
}

template<class T>
IndirectList<T>& IndirectList<T>::Insert(int k, const T& x)
{// Insert x after k'th element.
   T *p = new T;
   *p = x;
   return LinearList<T *>::Insert(k, p);
}


template<class T>
void IndirectList<T>::Output(ostream& out) const
{
   for (int i=0; i < length; i++)
      out << *element[i] << ' ';
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const IndirectList<T>& x)
   {x.Output(out); return out;}

#endif
