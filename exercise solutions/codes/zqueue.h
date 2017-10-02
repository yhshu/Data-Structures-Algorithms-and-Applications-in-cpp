
// header file cqueue.h
//linked queue derived from extended chain

#ifndef LinkedQueue_
#define LinkedQueue_

#include "echain.h"

template<class type>
class LinkedQueue : protected Chain<type>
{// FIFO objects
public:
   int IsEmpty()
      {return ((first) ? 0 : 1);}
   int IsFull();
   int First(type& x) {return Find(1,x);}
   int Last(type& x);
   int Add(const type& x) {return Append(x);}
   int Delete(type& x) {return Chain<type>::Delete(1,x);}
};

template<class type>
int LinkedQueue<type>::IsFull()
{
ChainNode<type> *i;
i = new ChainNode<type>;
if (i) {delete i; return 0;};
return 1;
}

template<class type>
int LinkedQueue<type>::Last(type& x)
{//set x to last element
if (IsEmpty()) return 0; //Last fails
x = last->data;
return 1;
}

#endif
