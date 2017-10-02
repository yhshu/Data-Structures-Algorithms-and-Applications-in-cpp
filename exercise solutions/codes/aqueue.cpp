

#include<iostream.h>
#include "aqueue.h"
void main(void)
{
   try {
      Queue<int> Q(9);
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
