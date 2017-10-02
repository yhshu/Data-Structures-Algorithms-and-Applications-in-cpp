

// test indirect list selection sort

#include <iostream.h>
#include "indlist4.h"

void main(void)
{
   try {
      IndirectList<int> C, D, E, F, G;

      // try a sorted list
      C.Insert(0,2).Insert(1,6).Insert(2,7).Insert(3,8).Insert(4,9);
      cout << "List is " << C << endl;
      C.SelectionSort();
      cout << "The sorted list is " << C << endl;

      // try a decreasing list
      D.Insert(0,5).Insert(1,4).Insert(2,3).Insert(3,2).Insert(4,1);
      cout << "List is " << D << endl;
      D.SelectionSort();
      cout << "The sorted list is " << D << endl;

      // try a random list
      E.Insert(0,5).Insert(1,8).Insert(2,6).Insert(3,7);
      cout << "List is " << E << endl;
      E.SelectionSort();
      cout << "The sorted list is " << E << endl;

      // try an empty list
      cout << "List is " << F << endl;
      F.SelectionSort();
      cout << "The sorted list is " << F << endl;

      // try a list with one element
      G.Insert(0,1);
      cout << "List is " << G << endl;
      G.SelectionSort();
      cout << "The sorted list is " << G << endl;
      }
   catch (...) {
      cerr << "An exception has occurred" << endl;
      }
}
