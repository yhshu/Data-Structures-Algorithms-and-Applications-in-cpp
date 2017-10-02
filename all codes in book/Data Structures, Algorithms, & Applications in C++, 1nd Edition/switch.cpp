// switch box routing

#include <iostream.h>
#include "stack.h"

bool CheckBox(int net[], int n)
{// Determine whether the switch box is routable.
   Stack<int> *s = new Stack<int> (n);

   // scan nets clockwise
   for (int i = 0; i < n; i++) {
      // examine net[i]
      if (!s->IsEmpty()) {// check with top net
         if (net[i] == net[s->Top()]) {
            // net[i] routable, delete from stack
            int x;
            s->Delete(x);}
         else s->Add(i);}
      else s->Add(i);
      }

   // any unrouted nets left?
   if (s->IsEmpty()) {// no nets remain
      delete s;
      cout << "Switch box is routable" << endl;
      return true;}

   delete s;
   cout << "Switch box is not routable" << endl;
   return false;
}

void main(void)
{
   int *net, n;
   cout << "Type number of pins in switch box " << endl;
   cin >> n;
   try {net = new int [n];
        cout << "Type net numbers for pins 1 through " << n << endl;
        for (int i = 0; i<n; i++) cin >> net[i];
        CheckBox(net, n);}
   catch (NoMem)
      {cout << "Insufficient memory" << endl;}
}
