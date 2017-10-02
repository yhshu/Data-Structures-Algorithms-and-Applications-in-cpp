// test skip list iterator

#include <iostream.h>
#include "skip.h"
#include "skipiter.h"

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
   cout << "The elements are:" << endl;
   S.Output();

   cout << "Output using iterator" << endl;
   SkipListIterator<element, long> p;
   element *q = p.Begin(S);
   while (q) {
     cout << *q << ' '; 
     q = p.Next();
     }
   cout << endl;
}
