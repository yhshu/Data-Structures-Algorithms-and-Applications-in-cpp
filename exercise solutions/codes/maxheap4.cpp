
#include <iostream.h>
#include "maxheap4.h"

void main(void)
{
   MaxHeap<int> H(15);
   int x;
   H.Insert(10).Insert(20).Insert(5).Insert(3);
   H.Insert(30).Insert(15).Insert(6).Insert(4);
   H.Insert(9).Insert(11).Insert(1).Insert(50);
   cout << "Elements in array order" << endl;
   H.Output();
   H.DeleteMax(x);
   cout << "Deleted max element " << x << endl;
   cout << "Elements in array order" << endl;
   H.Output();
   H.DeleteMax(x);
   cout << "Deleted max element " << x << endl;
   cout << "Elements in array order" << endl;
   H.Output();
   H.DeleteMax(x);
   cout << "Deleted max element " << x << endl;
   cout << "Elements in array order" << endl;
   H.Output();
   H.DeleteMax(x);
   cout << "Deleted max element " << x << endl;
   cout << "Elements in array order" << endl;
   H.Output();
}
