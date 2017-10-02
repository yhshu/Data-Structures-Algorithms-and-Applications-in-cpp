// test chained hash table derived from
// SortedChainWithTail

#include <iostream.h>
#include "cchash.h"

class element {
   friend void main(void);
   public:
      operator long() const {return key;}
      element& operator =(long y)
      {key = y; return *this;}
   private:
      int data;
      long key;
   };

ChainHashTable<element, long> h(11);
element e;

void main(void)
{
   e.key = 80;
   h.Insert(e);
   e.key = 40;
   h.Insert(e);
   e.key = 65;
   h.Insert(e);
   e.key = 58;
   h.Insert(e);
   e.key = 24;
   h.Insert(e);
   e.key = 2;
   h.Insert(e);
   e.key = 13;
   h.Insert(e);
   e.key = 46;
   h.Insert(e);
   e.key = 16;
   h.Insert(e);
   e.key = 7;
   h.Insert(e);
   e.key = 21;
   h.Insert(e);
   h.Delete(2,e);
   h.Delete(16,e);
   h.Delete(24,e);
   h.Delete(80,e);
   h.Output();
}
