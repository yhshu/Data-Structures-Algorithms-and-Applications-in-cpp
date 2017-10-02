
#ifndef KeyedChain_
#define KeyedChain_
// file keychain.h
// chains with keys

#include "echain.h"

template<class T>
class KeyedChain : public Chain<T> {
   public:
      bool Delete(T& x); // delete x
      ChainNode<T> * First() const {return first;}
};

template<class T>
bool KeyedChain<T>::Delete(T& x)
{// Delete element matching x.
   ChainNode<T> *i = first, *p = 0;
   // search for match
   for (; i && i->data != x; i = i->link) p = i;
   if (!i) throw BadInput(); // no match
   // match found in node i
   x = i->data; // return matching element
   if (p) p->link = i->link; // i is not first node
   else first = i->link; // i is first node
   delete i;
   return *this;
}

#endif
