
#include<iostream.h>
#include<stdlib.h>
#include "bskip.h"

class element {
public:
   int data;
   long key;
   operator long() const {return key;}
   element& operator =(long y)
   {key = y; return *this;}
   };


SkipList<element, long> S(10001, 100, 0.5);
element e;

void main(void)
{
int i, n = 20;
for (i = 1; i <= n; i++) {
   e.data = i; e.key = 2*i;
   S.Insert(e);
   }
S.Output();
S.DeleteMin(e);
cout << "Min element deleted is " << e << endl;
S.DeleteMin(e);
cout << "Min element deleted is " << e << endl;
S.DeleteMax(e);
cout << "Max element deleted is " << e << endl;
S.DeleteMax(e);
cout << "Max element deleted is " << e << endl;
S.Output();
}
