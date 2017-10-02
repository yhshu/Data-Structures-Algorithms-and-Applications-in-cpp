// test currency class

#include <iostream.h>
#include "curr2.h"

void main(void)
{
   Currency g, h(plus, 3, 50), i, j;
   g.Set(minus, 2, 25);
   i.Set(-6.45);
   j = h.Add(g);
   j.Output(); cout << endl;
   i.Increment(h);
   i.Output(); cout << endl;
   j = i.Add(g).Add(h);
   j.Output(); cout << endl;
   j = i.Increment(g).Add(h);
   j.Output(); cout << endl;
   i.Output(); cout << endl;
}
