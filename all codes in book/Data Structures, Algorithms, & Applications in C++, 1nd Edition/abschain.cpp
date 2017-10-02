// test chain derived from abstract list

#include <iostream.h>
#include "abschain.h"
#include "xcept.h"

void main(void)
{
   int x;
   try {
      Chain<int> L;
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
   catch (...) {
      cerr << "An exception has occurred" << endl;
      }
}
