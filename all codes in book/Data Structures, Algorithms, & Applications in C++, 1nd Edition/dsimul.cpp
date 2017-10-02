// simulated pointer dual available space lists

#include <iostream.h>
#include "dsimul.h"

void main(void)
{
   int x;
   SimSpace<int> L(5);
   x = L.Allocate();
   cout << "Node allocated is " << x << endl;
   int y = L.Allocate();
   cout << "Node allocated is " << y << endl;
   L.Deallocate(x);
   y = L.Allocate();
   cout << "Node allocated is " << y << endl;
}
