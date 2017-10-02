// test the class circularListWithHeader
#include<iostream>
#include "circularListWithHeader.h"

using namespace std;

int main()
{
   // test constructor
   circularListWithHeader<int> y, z;

   // test size
   cout << "Initial size of y and z = "
        << y.size() << ", "
        << z.size() << endl;

   // test insert
   y.insert(0, 2);
   y.insert(1, 6);
   y.insert(0, 1);
   y.insert(2, 4);
   y.insert(3, 5);
   y.insert(2, 3);
   cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
   cout << "Size of y = " << y.size() << endl;
   y.output(cout);
   cout << endl << "Testing overloaded <<" << endl;
   cout << y << endl;

   // test indexOf
   int index = y.indexOf(4);
   if (index < 0) cout << "4 not found" << endl;
   else cout << "The index of 4 is " << index << endl;

   index = y.indexOf(7);
   if (index < 0) cout << "7 not found" << endl;
   else cout << "The index of 7 is " << index << endl;

   return 0;
}
