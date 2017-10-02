// test hash table with linear open addressing

#include <iostream.h>
#include "hash.h"

class element {
   friend void main(void);
   public:
      operator long() const {return key;}
   private:
      int data;
      long key;
};

void main(void)
{
   HashTable<element, long> h(11);
   element e;
   e.key = 80;
   h.Insert(e);
   e.key = 40;
   h.Insert(e);
   e.key = 65;
   h.Insert(e);
   h.Output();
   e.key = 58;
   h.Insert(e);
   e.key = 24;
   h.Insert(e);
   cout << ' ' << endl;
   h.Output();
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
   cout << ' ' << endl;
   h.Output();
   e.key = 99;
   try {h.Insert(e);}
   catch (NoMem)
      {cout  << " No memory for 99" << endl;}
}
