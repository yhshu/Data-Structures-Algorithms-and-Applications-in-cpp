

// test linked selection sort
#include <iostream.h>
#include "ochain.h"

void main(void)
{
   try {
      Chain<int> C, D, E, F, G;

      // try a sorted chain
      C.Insert(0,2).Insert(1,6).Insert(2,7).Insert(3,8).Insert(4,9);
      cout << "Chain is " << C << endl;
      C.SelectionSort();
      cout << "The sorted chain is " << C << endl;

      // try a decreasing chain
      D.Insert(0,5).Insert(1,4).Insert(2,3).Insert(3,2).Insert(4,1);
      cout << "Chain is " << D << endl;
      D.SelectionSort();
      cout << "The sorted chain is " << D << endl;

      // try a random chain
      E.Insert(0,5).Insert(1,8).Insert(2,6).Insert(3,7);
      E.Insert(4,1).Insert(2,3).Insert(0,9).Insert(0,4);
      cout << "Chain is " << E << endl;
      E.SelectionSort();
      cout << "The sorted chain is " << E << endl;

      // try an empty chain
      cout << "Chain is " << F << endl;
      F.SelectionSort();
      cout << "The sorted chain is " << F << endl;

      // try a chain with one element
      G.Insert(0,1);
      cout << "Chain is " << G << endl;
      G.SelectionSort();
      cout << "The sorted chain is " << G << endl;
      }
   catch (...) {
      cerr << "An exception has occurred" << endl;
      }
}
