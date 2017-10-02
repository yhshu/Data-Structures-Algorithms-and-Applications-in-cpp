
#include<iostream.h>
#include "ihash.h"
class element {
   public:
      int data;
      int key;
      operator int() const {return key;}
};


IdealHashTable<element> h(100,5);
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
   h.Output();
   e.key = 2;
   try {h.Insert(e);}
   catch (NoMem) {
      cout << "This insert should fail " 
           << endl;
      }
   h.Delete(80,e);
   cout << e << " deleted" << endl;
   h.Output();
   h.Search(24,e);
   cout << "Found " << e << endl;
   e.key = 13;
   h.Insert(e);
   h.Output();
}
