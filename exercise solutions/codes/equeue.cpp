

#include<iostream.h>
#include "equeue.h"
void main(void)
{
   try {
      LinkedQueue<int> Q;
      cin >> Q;
      cout << "Queue size is "
           << Q.Size() << endl;
      cout << Q << endl;
      }
   catch (...) {
      cerr << "An exception has occurred"
           << endl;
      }
}
