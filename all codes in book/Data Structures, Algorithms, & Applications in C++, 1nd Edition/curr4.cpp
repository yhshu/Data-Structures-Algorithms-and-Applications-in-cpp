// test currency class

#include <iostream.h>
#include "curr4.h"

void main(void)
{
   Currency g, h(plus, 3, 50), i, j;
   g.Set(minus, 2, 25);
   i.Set(-6.45);
   j = h + g;
   cout << j << endl;
   i += h;
   cout << i << endl;
   j = i + g + h;
   cout << j << endl;
   j = (i+=g) + h;
   cout << j << endl;
   cout << i << endl;
}
