

// test simulated chain rank sort

#include <iostream.h>
#include "schain6.h"

SimSpace<int> SimChain<int>::S;

void main(void)
{
   try {
      SimChain<int> C, D, E, F, G;

      // try a sorted chain
      C.Insert(0,2).Insert(1,6).Insert(2,7).Insert(3,8).Insert(4,9);
      cout << "List is " << C << endl;
      C.RankSort();
      cout << "The sorted list is " << C << endl;

      // try a decreasing list
      D.Insert(0,5).Insert(1,4).Insert(2,3).Insert(3,2).Insert(4,1);
      cout << "List is " << D << endl;
      D.RankSort();
      cout << "The sorted list is " << D << endl;

      // try a random list
      E.Insert(0,5).Insert(1,8).Insert(2,6).Insert(3,7);
      cout << "List is " << E << endl;
      E.RankSort();
      cout << "The sorted list is " << E << endl;

      // try an empty list
      cout << "List is " << F << endl;
      F.RankSort();
      cout << "The sorted list is " << F << endl;

      // try a list with one element
      G.Insert(0,1);
      cout << "List is " << G << endl;
      G.RankSort();
      cout << "The sorted list is " << G << endl;
      }
   catch (...) {
      cerr << "An exception has occurred" << endl;
      }
}
