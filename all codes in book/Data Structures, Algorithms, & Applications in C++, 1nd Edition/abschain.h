
#ifndef Chain_
#define Chain_
// file abschain.h
#include<iostream.h>
#include "cnode.h"
#include "abslist.h"
#include "xcept.h"

template <class T> class ChainIterator;

template<class T>
class Chain : AbstractList<T> {
   friend  ChainIterator<T>;
   public:
      Chain() {first = 0;}
      ~Chain();
      bool IsEmpty() const {return first == 0;}
      int Length() const; 
      bool Find(int k, T& x) const; 
      int Search(const T& x) const; 
      AbstractList<T>& Delete(int k, T& x); 
      AbstractList<T>& Insert(int k, const T& x);
      void Output(ostream& out) const;
   private:
      ChainNode<T> *first;
};

template<class T>
Chain<T>::~Chain()
{// Destroy.
   ChainNode<T> *i;
   while (first)
      {i = first->link; delete first; first = i;}
}

template<class T>
int Chain<T>::Length() const
{// size of list
   ChainNode<T> *i = first;
   int len = 0;
   while (i) {len++; i = i->link;}
   return len;
   }

template<class T>
bool Chain<T>::Find(int k, T& x) const
{// Find k'th element.
   if (k < 1) return false;
   ChainNode<T> *i = first;
   int j = 1;
   while (j < k && i) {j++; i = i->link;}
   if (i) {x = i->data; return true;}
   return false; // no k'th element
}

template<class T>
int Chain<T>::Search(const T& x) const
{// Locate x.
   ChainNode<T> *i = first;
   int j = 1;
   while (i && i->data != x) {j++; i = i->link;}
   if (i) return j;
   return 0;
}

template<class T>
AbstractList<T>& Chain<T>::Delete(int k, T& x)
{// Delete k'th element.
   if (k < 1 || !first) throw OutOfBounds(); // no k'th
   
   ChainNode<T> *i = first;
   if (k > 1) {// not first element
     int j = 1;
     while (j < k - 1 && i) {j++; i = i->link;}
     if (!i || !i->link) throw OutOfBounds(); // no k'th
     ChainNode<T> *y = i->link; // k'th
     i->link = y->link; i = y;
     }
   else // delete first element
        first = first->link;
   x = i->data; delete i;
   return *this;
}

template<class T>
AbstractList<T>& Chain<T>::Insert(int k, const T& x)
{// Insert x after k'th element.
   if (k < 0) throw OutOfBounds();
   ChainNode<T> *i = first;
   int j = 1;
   while (j < k && i) {j++; i = i->link;}
   if (k > 0 && !i) throw OutOfBounds(); // no k'th
   // insert
   ChainNode<T> *y;
   y = new ChainNode<T>;
   y->data = x;
   if (k) {y->link = i->link; i->link = y;}
   else {y->link = first; first = y;}
   return *this;
}

template<class T>
void Chain<T>::Output(ostream& out) const
{// Insert the chain elements into the stream out.
   ChainNode<T> *i;
   for (i = first; i; i = i->link) out << i->data << "  ";
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const Chain<T>& x)
   {x.Output(out); return out;}

#endif
