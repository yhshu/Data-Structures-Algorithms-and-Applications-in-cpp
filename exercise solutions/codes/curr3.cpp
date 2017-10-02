

// test currency class

#include <iostream.h>
#include "curr3.h"

void main(void)
{
   Currency g, h, i, j;
   cin >> g;
   cin >> h;


   i = g - h;
   cout << g << " minus " << h << " = " 
        << (g - h) << endl;

   cout << "10% of " << g << " = "
        << (g % 10) << endl;

   cout << "3 times " << g << " = "
        << (g * 3) << endl;

   cout << "Half of " << g << " = "
        << (g / 2) << endl;
}
