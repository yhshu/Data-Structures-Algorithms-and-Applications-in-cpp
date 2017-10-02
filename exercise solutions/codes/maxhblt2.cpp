#include <iostream.h>
#include "maxhblt2.h"

// declare static variables of MaxHBLT<int>
int MaxHBLT<int>::MinElement = 0;
HBLTNode<int> *MaxHBLT<int>::MinNode =
              new HBLTNode<int>(0,0,0);

void main(void)
{
   MaxHBLT<int> H, J;
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
   H.DeleteMax(w).DeleteMax(x).DeleteMax(y).DeleteMax(z);
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
   cout << "The max element is " << H.Max() << endl;
   H.DeleteMax(x);
   cout << "Deleted max element " << x << endl;
   cout << "Leftist tree in postorder" << endl;
   H.Output();
   H.DeleteMax(x);
   cout << "Deleted max element " << x << endl;
   cout << "Leftist tree in postorder" << endl;
   H.Output();
   while (true) {// empty out
      try {H.DeleteMax(x);
           cout << "Deleted " << x << endl;}
      catch (OutOfBounds) {break;}
      }
}
