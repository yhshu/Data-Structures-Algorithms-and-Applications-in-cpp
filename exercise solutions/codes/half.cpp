// Test LinearList<T>::Half

#include <iostream.h>
#include "clist.h"

void main()
{
   // initialize two lists
   int n = 10, m = 5;
   LinearList<int> A(20), B(20);
   for (int i = 0; i < n; i++)
      A.Insert(0, 2*(n - i));
   for (i = 0; i < m; i++)
      B.Insert(0, 2*(n - i) + 1);

   cout << "List A is" << endl;
   cout << A << endl;

   cout << "A.Half() is" << endl;
   cout << A.Half() << endl;

   cout << "List B is" << endl;
   cout << B << endl;

   cout << "B.Half() is" << endl;
   cout << B.Half() << endl;

}
