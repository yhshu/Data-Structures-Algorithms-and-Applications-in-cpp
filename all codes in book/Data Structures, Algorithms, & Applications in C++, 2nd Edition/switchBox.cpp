// switch box routing

#include <iostream>
#include "arrayStack.h"

using namespace std;

bool checkBox(int net[], int n)
{// Determine whether the switch box is routable.
 // net[0..n-1] is array of pin to net assignments.
 // n is number of pins.

   arrayStack<int>* s = new arrayStack<int>(n);

   // scan nets clockwise
   for (int i = 0; i < n; i++)
      // process pin i
      if (!s->empty())
         // check with top net
         if (net[i] == net[s->top()])
            // net[i] is routable, delete from stack
            s->pop();
         else s->push(i);
      else s->push(i);

   // any unrouted nets left?
   if (s->empty())
   {// no nets remain
       cout << "Switch box is routable" << endl;
       return true;
    }

   cout << "Switch box is not routable" << endl;
   return false;
}

void main()
{
   // input the number of pins and their net assignment
   cout << "Type number of pins in switch box" << endl;
   int n;
   cin >> n;

   // create net assignment array
   int* net = new int[n];

   // input the net assignments
   cout << "Type net numbers for pins 1 through "  << n << endl;
   for (int i = 0; i < n; i++)
      cin >> net[i];

   // see if the switch box is routable
   checkBox(net, n);
}
