#include<iostream.h>
#include "deque.h"
void main(void)
{
   Deque<int> Q(3);
   Q.AddLeft(2).AddLeft(1).AddRight(3);
   cout << "The deque from front to rear is"
        << endl
        << Q << endl;
   int x;
   Q.DeleteRight(x);
   cout << x << " deleted from rear" << endl;
   Q.AddLeft(4).DeleteRight(x);
   cout << Q.Left() << " added to front and "
        << x << " deleted from rear" << endl;
   Q.DeleteLeft(x);
   cout << x << " deleted from front" << endl;
   Q.DeleteLeft(x);
   cout << x << " deleted from front" << endl;
   cout << "The deque from front to rear is"
        << endl
        << Q << endl;
   
}
