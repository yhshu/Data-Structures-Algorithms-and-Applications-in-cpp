
// find k'th smallest element

#include <iostream.h>
#include "select2.h"

void main(void)
{
   int y[16] = {20, 30, 4, 2, 9, 7, 1, 2, 10, 3, 40, 22, 12, 14, 8, 100};
   int n = 15, x;
   for (int i = 1; i <= n; i++) {
      x = Select(y,n,i);
      cout << "The " << i << " element is " << x << endl;
     }
}
