
#ifndef KeyedChain_
#define KeyedChain_
// file keychain.h

#include "echain.h"

template<class type>
class KeyedChain : public Chain<type>
{
public:
   int Delete(type& x); // delete x
   ChainNode<type> * First() {return first;}
};

template<class type>
int KeyedChain<type>::Delete(type& x)
{
ChainNode<type> *i = first, *p = 0;
for (; i && i->data != x; p = i, i = i->link);
if (i) {
        if (p) p->link = i->link;
        else first = i->link;
        delete i;
        return 1;}
return 0;
}
#endif
