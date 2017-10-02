

#include <iostream.h>
#include "minheap4.h"

void main(void)
{
   MinHeap<int> H(4);
   H.Insert(10).Insert(20).Insert(5).Insert(30);
   cout << "Elements in array order" << endl;
   H.Output();
   H.ChangeMin(2);
   cout << "Min element replaced by 2" << endl;
   cout << "Elements in array order" << endl;
   H.Output();
   H.ChangeMin(15);
   cout << "Min element replaced by 15" << endl;
   cout << "Elements in array order" << endl;
   H.Output();
   H.ChangeMin(40);
   cout << "Min element replaced by 40" << endl;
   cout << "Elements in array order" << endl;
   H.Output();
   H.ChangeMin(25);
   cout << "Min element replaced by 1" << endl;
   cout << "Elements in array order" << endl;
   H.Output();
}
