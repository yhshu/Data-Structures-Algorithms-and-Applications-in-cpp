
// test circular class

#include <iostream.h>
#include "circular.h"

void main(void)
{
   try {
      Circular<int> L;
      cout << "Length = " << L.Length() << endl;
      cout << "IsEmpty = " << L.IsEmpty() << endl;
      L.Insert(0,2).Insert(1,5).Insert(2,7).Insert(3,8);
      L.Insert(1,3).Insert(0,1).Insert(4,6).Insert(7,9);
      cout << "List is " << L << endl;
      cout << "IsEmpty = " << L.IsEmpty() << endl;
      int z;
      L.Find(1,z);
      cout << "First element is " << z << endl;
      L.Find(8,z);
      cout << "Eighth element is " << z << endl;
      L.Find(4,z);
      cout << "Fourth element is " << z << endl;
      cout << "Length = " << L.Length() << endl;
      cout << "8 is in position " << L.Search(8) << endl;
      cout << "1 is in position " << L.Search(1) << endl;
      cout << "10 is in position " << L.Search(10) << endl;
      cout << "6 is in position " << L.Search(6) << endl;
      L.Delete(1,z);
      cout << "Deleted element from position 1 is " << z << endl;
      cout << "List is " << L << endl;
      L.Delete(7,z);
      cout << "Deleted element from position 7 is " << z << endl;
      cout << "List is " << L << endl;
      L.Delete(3,z);
      cout << "Deleted element from position 3 is " << z << endl;
      cout << "List is " << L << endl;
      int z1, z2, z3;
      L.Delete(5,z1).Delete(1,z2).Delete(3,z3);
      cout << "Deleted elements are " << z1
           << "  " << z2 << "  " << z3 << endl;
      cout << "List is " << L << endl;
      L.Delete(1,z1).Delete(1,z2);
      cout << "Deleted elements are " << z1
           << "  " << z2 << endl;
      cout << "List is " << L << endl;
      L.Insert(0,5);
      cout << "List is " << L << endl;
      }
   catch (...) {
      cerr << "An exception has occurred" << endl;
      }
}
