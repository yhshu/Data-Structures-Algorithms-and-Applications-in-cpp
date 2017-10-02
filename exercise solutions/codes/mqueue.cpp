
#include <iostream.h>
#include "mqueue.h"

void main(void)
{
   Queue<int> Q(3);
   int x;
   try {Q.Add(1).Add(2).Add(3).Add(4);
        cout << "No queue add failed" << endl;}
   catch (NoMem)
      {cout << "A queue add failed" << endl;}
   cout << "Queue is now 123" << endl;
   Q.Delete(x);
   cout << "Deleted " << x << endl;
   cout << Q.First() << " is at front" << endl;
   cout << Q.Last() << " is at end" << endl;
   try {
      Q.Delete(x);
      cout << "Deleted " << x << endl;
      Q.Delete(x);
      cout << "Deleted " << x << endl;
      Q.Delete(x);
      cout << "Deleted " << x << endl;
      cout << "No queue delete failed " << endl;
      }
   catch (OutOfBounds)
      {cout << "A delete has failed" << endl;}
}
