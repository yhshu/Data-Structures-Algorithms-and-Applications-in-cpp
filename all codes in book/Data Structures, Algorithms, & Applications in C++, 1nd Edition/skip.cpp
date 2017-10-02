// test skip list class

#include <iostream.h>
#include "skip.h"

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

void main(void)
{
   SkipList<element, long> S(10001, 100, 0.5);
   element e;
   int i, n = 20;
   for (i = 1; i <= n; i++) {
      e.data = i; e.key = 2*i;
      S.Insert(e);}
   S.Output();
   for (i=1; i <= n+1; i++) {
      e.data = n+i; e.key = 2*i-1;
      try {S.Insert(e);}
      catch (BadInput)
       {cout << "Unable to insert duplicate " << e << endl;}
      catch (NoMem)
       {cout << "Not enough memory to insert " << e << endl;}
      }
   
   S.Output();
   for (i = 1; i <= n+1; i++) {
      long k = 2*i-1;
      try {S.Delete(k,e);
         cout << "Deleted " << e.key << "  " << e.data << endl;}
      catch (BadInput)
         {cout << "Delete of " << (2*i-1) << " failed" << endl;}
      }
   S.Output();
}
