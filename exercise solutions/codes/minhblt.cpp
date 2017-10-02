
// test min height balanced leftist tree class

#include <iostream.h>
#include "minhblt.h"

void main(void)
{
   MinHBLT<int> H, J;
   int a[6] = {0, 7, 9, 1, 8, 11};
   H.Initialize(a,5);
   cout << "One tree in postorder is" << endl;
   H.Output();
   int b[5] = {0, 2, 6, 4, 9};
   J.Initialize(b,4);
   cout << "Other tree in postorder is" << endl;
   J.Output();
   H.Meld(J);
   cout << "After melding, the tree in postorder is" << endl;
   H.Output();
   int w, x, y, z;
   H.DeleteMin(w).DeleteMin(x).DeleteMin(y).DeleteMin(z);
   cout << "After deleting four elements, the tree is" << endl;
   H.Output();
   cout << "The deleted elements, in order, are" << endl;
   cout << w << "  " << x << "  " << y << "  " << z << endl;
   H.Insert(10).Insert(20).Insert(5);
   cout << "Leftist tree in postorder" << endl;
   H.Output();
   H.Insert(15).Insert(30).Insert(2);
   cout << "Leftist tree in postorder" << endl;
   H.Output();
   cout << "The min element is " << H.Min() << endl;
   H.DeleteMin(x);
   cout << "Deleted min element " << x << endl;
   cout << "Leftist tree in postorder" << endl;
   H.Output();
   H.DeleteMin(x);
   cout << "Deleted min element " << x << endl;
   cout << "Leftist tree in postorder" << endl;
   H.Output();
   while (true) {// empty out
      try {H.DeleteMin(x);
           cout << "Deleted " << x << endl;}
      catch (OutOfBounds) {break;}
      }
}
