


// arbitrary delete

#include <iostream.h>
#include "gcircle.h"


void main(void)
{
   int n = 15;
   Circular<int> X;
   
   // initialize list
   for (int i = 0; i < n; i++)
      X.Insert(0,i);
   cout << "The list is" << endl;
   cout << X << endl;
   
   int x;
   X.MoveForward(3);
   X.Delete(x);
   cout << x << " has been deleted" << endl;
   cout << "The list after the deletion is" << endl;
   cout << X << endl;

   X.MoveForward(1);
   X.Delete(x);
   cout << x << " has been deleted" << endl;
   cout << "The list after the deletion is" << endl;
   cout << X << endl;

   X.MoveForward(13);
   X.Delete(x);
   cout << x << " has been deleted" << endl;
   cout << "The list after the deletion is" << endl;
   cout << X << endl;

}
