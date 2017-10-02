// test indirect list

#include <iostream.h>
#include "indlist.h"

void main(void)
{
   int x;
   IndirectList<int> L(5);
   cout << "Length = " << L.Length() << endl;
   cout << "IsEmpty = " << L.IsEmpty() << endl;
   L.Insert(0,2).Insert(1,6);
   cout << "List is " << L << endl;
   cout << "IsEmpty = " << L.IsEmpty() << endl;
   L.Find(1,x);
   cout << "First element is " << x << endl;
   cout << "Length = " << L.Length() << endl;
   L.Delete(1,x);
   cout << "Deleted element is " << x << endl;
   cout << "List is " << L << endl;
}
